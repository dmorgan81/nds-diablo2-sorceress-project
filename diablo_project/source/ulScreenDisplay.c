#include "ulScreenDisplay.h"
#include "uldata.h"



void myulInitData (bool again)
{

#include "spritesdata.txt" //all data in txt file to avoid overload of the c file

    if (!again)//if its the first time we load images
    {
        //au cas ou
        int i;
        for (i=0; i<MAX_SPRITES ; i++)
        {
            sprites[i].used=0;
            sprites[i].sprite=-1;
            sprites[i].prio=-1;
            sprites[i].color=RGB15(31, 31, 31);
            sprites[i].cycles=0;
        }
    }
    //la map
    mapTiles = ulLoadImageFilePNG((void*)map_png, (int)map_png_size, UL_IN_VRAM, UL_PF_PAL4);
    Mymap = ulCreateMap(mapTiles,/*Tileset*/map,8,8,/*Tiles size*/60,45,/*Map size*/UL_MF_U16);//Map format
    map_col=tilescollision_map;
    ulSetAutoDepth(0);

}




int myulCreateSprite (u8 data,int x,int y, s8 prio)
{
    int i=0, nb=-1;
    for (i=0; i<MAX_SPRITES ; i++)
    {
        if (sprites[i].used == 0)
        {
            nb=i;
            i=MAX_SPRITES;
        }
        else nb=-1;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if ( nb > -1)
    {
        sprites[nb].used=1;
        sprites[nb].sprite=data;
        sprites[nb].x=x;
        sprites[nb].y=y;
        sprites[nb].column=0;
        sprites[nb].startframe=0;
        sprites[nb].endframe=spritedatabase[data].nbframe;
        sprites[nb].framerate=spritedatabase[data].framerate;
        sprites[nb].abcoeff=spritedatabase[data].abcoeff;
        sprites[nb].animStage=0;
        sprites[nb].frameNumber=0;
        sprites[nb].color=RGB15(31, 31, 31);
        sprites[nb].cycles=spritedatabase[data].cycles;
        myulSetSpritePrio( nb, prio);
    }
    else
    {
        PA_OutputText(1,15,17,"SPRITES LIMIT REACHED");
    }
    return nb;
}













inline void myulDeleteSprite (int nb)
{
    if (nb>-1)
    {
        sprites[nb].used=0;
        sprites[nb].flippedh=0;
        sprites[nb].flippedv=0;
        //sprites[nb].angle=0;
        sprites[nb].sprite=-1;
    }
}
inline void myulImageFlip (int /*sprite*/nb,bool fliph,bool flipv)
{
    sprites[nb].flippedh=fliph;
    sprites[nb].flippedv=flipv;

}

inline void myulImageColumn (int /*sprite*/nb,int column)
{
    sprites[nb].column=column;
}
/*
inline void myulImageAngle(int nb,int angle,int x,int y)//change
{
    sprites[nb].angle=angle; sprites[nb].midx=x; sprites[nb].midy=y;
}
*/
inline int GetSpriteY (int nb)
{
    return sprites[nb].y;
}

inline int GetSpriteX (int nb)
{
    return sprites[nb].x;
}

inline void SetSpriteY (int nb,int y)
{
    sprites[nb].y=y;
}

inline void SetSpriteX (int nb,int x)
{
    sprites[nb].x=x;
}

inline void SetSpriteColor (int nb,u16 color)
{
    sprites[nb].color=color;
}

inline void SetSpriteXY (int nb,int x,int y)
{
    sprites[nb].x=x;
    sprites[nb].y=y;
}

inline void myulAnimBegin (int spritenb)
{
    sprites[spritenb].frameNumber=0;
    sprites[spritenb].animStage=0;
}

inline void myulStartAnim (int spritenb, u8 sframe, u8 endframe, u8 framerate,int cycles)
{
    sprites[spritenb].startframe=sframe;
    sprites[spritenb].endframe=endframe;
    sprites[spritenb].framerate=framerate;
    sprites[spritenb].frameNumber=0;
    sprites[spritenb].animStage=0;
    sprites[spritenb].cycles=cycles;
}


inline void myulSetAnim (int spritenb, u8 sframe, u8 endframe, u8 framerate,int cycles)
{
    sprites[spritenb].startframe=sframe;
    sprites[spritenb].endframe=endframe;
    sprites[spritenb].framerate=framerate;
    sprites[spritenb].cycles=0;
}

inline void myulDefaultAnimRestart (int spritenb)
{
    sprites[spritenb].startframe=0;
    sprites[spritenb].endframe=spritedatabase[sprites[spritenb].sprite].nbframe;
    sprites[spritenb].framerate=spritedatabase[sprites[spritenb].sprite].framerate;
    sprites[spritenb].frameNumber=0;
    sprites[spritenb].animStage=0;
    sprites[spritenb].cycles=0;
}

inline void myulDefaultAnim (int spritenb)
{
    sprites[spritenb].startframe=0;
    sprites[spritenb].endframe=spritedatabase[sprites[spritenb].sprite].nbframe;
    sprites[spritenb].framerate=spritedatabase[sprites[spritenb].sprite].framerate;
    sprites[spritenb].cycles=0;
}

inline void myulSetSpritePrio( int sprite, int prio)
{
    sprites[sprite].prio = prio;
}

inline void SetSpriteAblending (int sprite,int value)
{
    sprites[sprite].abcoeff = value;
}






void myulScreenDraws(void)
{
    ulStartDrawing2D();

    ulSetDepth(0);
    //Fond sur l'écran du bas
    glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_ID(0));
#ifndef Test
    ulDrawMap(Mymap);
#endif
#ifdef Test
    ulDrawGradientRect(0, 0, 256, 192, RGB15(0, 0, 24), RGB15(0, 0, 0), RGB15(0, 0, 0), RGB15(0, 0, 24));
#endif
    UL_IMAGE *spriteimage;
    int i;
    //myulUpdatePrio();
    int sprite=-1;
    int nb=0;
    for (i=0; i<MAX_SPRITES ; i++)
    {

        sprite =i;// Prio_first[i];

        //if(sprites[sprite].used && sprite!=-1)


        while (sprite != -1)
        {
            if(sprites[sprite].used)
            {
                nb++;
                if(sprites[sprite].framerate!=0)
                {
                    sprites[sprite].frameNumber++;
                    if (sprites[sprite].frameNumber % sprites[sprite].framerate  == 0)
                    {
                        if (!sprites[sprite].cycles) //loop
                        {
                            sprites[sprite].animStage = (sprites[sprite].animStage + 1) % (sprites[sprite].endframe-sprites[sprite].startframe) ;
                        }
                        else if (sprites[sprite].cycles<1)
                        {
                            sprites[sprite].animStage = (sprites[sprite].animStage + 1) % (sprites[sprite].endframe-sprites[sprite].startframe) ;
                            sprites[sprite].cycles-=1;
                        }
                        else if (sprites[sprite].animStage+1==sprites[sprite].endframe)//can only be the last cycle so dont have to check it
                        {
                            //sprites[sprite].animStage = 0;// why calculate the modulo if we already know it will be 0?
                            sprites[sprite].framerate = 0;// no more animation, last frame is reached
                        }
                        else
                        {
                            sprites[sprite].animStage = (sprites[sprite].animStage + 1) % (sprites[sprite].endframe-sprites[sprite].startframe) ;
                        }
                    }
                }
                spriteimage=spritedatabase[sprites[sprite].sprite].image;

                spriteimage->x=sprites[sprite].x;
                spriteimage->y=sprites[sprite].y;
//                if(sprites[sprite].angle)spriteimage->angle=(-sprites[sprite].angle)<<6;//change
//                	spriteimage->centerX = sprites[sprite].midx;
//	spriteimage->centerY = sprites[sprite].midy;
                //Tile to display
                ulSetImageTileSize (
                    spriteimage,
                    spritedatabase[sprites[sprite].sprite].sizex*sprites[sprite].column,																			//image, starting x
                    spritedatabase[sprites[sprite].sprite].sizey*(sprites[sprite].animStage+sprites[sprite].startframe),	//starting y : size*(frame+startframe)
                    spritedatabase[sprites[sprite].sprite].sizex,																// size x
                    spritedatabase[sprites[sprite].sprite].sizey);															// size y

                ulMirrorImageH( spriteimage, sprites[sprite].flippedh);
                ulMirrorImageV( spriteimage, sprites[sprite].flippedv);
                ulSetDepth(sprites[sprite].prio);
                glPolyFmt(POLY_ALPHA(sprites[sprite].abcoeff) | POLY_CULL_NONE | POLY_ID(sprites[sprite].prio));
                ulSetImageTint(spriteimage,sprites[sprite].color);
                ulDrawImage(spriteimage);
                imagesused[sprites[sprite].sprite]=1;

            }
            sprite =-1;// Prio_next[sprite];

        }

    }
    ulEndDrawing();
    ulEndFrame();

}




