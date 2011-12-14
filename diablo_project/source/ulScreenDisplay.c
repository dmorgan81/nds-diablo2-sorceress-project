#include "ulScreenDisplay.h"
#include "uldata.h"
int curMaxSprite;//same trick as in objects.c


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




int myulCreateSprite (u8 data,int x,int y, int prio)
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
        myulmyulSetSpritePrio( nb, prio);
        if (nb>curMaxSprite)curMaxSprite=nb;
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
        sprites[nb].color=0x7fff;
        sprites[nb].sprite=-1;
        if (nb==curMaxSprite)curMaxSprite--;
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
inline int myulGetSpriteY (int nb)
{
    return sprites[nb].y;
}

inline int myulGetSpriteX (int nb)
{
    return sprites[nb].x;
}

inline int myulGetSpriteAnim (int nb)
{
    return sprites[nb].animStage;
}
inline void myulSetSpriteY (int nb,int y)
{
    sprites[nb].y=y;
}

inline void myulSetSpriteX (int nb,int x)
{
    sprites[nb].x=x;
}

inline void myulSetSpriteColor (int nb,u16 color)
{
    sprites[nb].color=color;
}

inline void myulSetSpriteXY (int nb,int x,int y)
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

inline void myulmyulSetSpritePrio( int sprite, int prio)
{
    sprites[sprite].prio = prio;
}

inline void myulSetSpriteAblending (int sprite,int value)
{
    sprites[sprite].abcoeff = value;
}

inline void myulSetCycles (int sprite,int cycles)
{
    sprites[sprite].cycles=cycles;
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
    int nb=0;
    for (i=0; i<=curMaxSprite ; i++)
    {
        if(sprites[i].used)
        {
            nb++;
            if(sprites[i].framerate)
            {
                sprites[i].frameNumber++;
                if (sprites[i].frameNumber % sprites[i].framerate  == 0)
                {
                    if (!sprites[i].cycles) //loop
                    {
                        sprites[i].animStage = (sprites[i].animStage + 1) % (sprites[i].endframe-sprites[i].startframe) ;
                    }
                    else if (sprites[i].cycles>1)
                    {
                        sprites[i].animStage = (sprites[i].animStage + 1) % (sprites[i].endframe-sprites[i].startframe) ;
                        sprites[i].cycles-=1;
                    }
                    else if (sprites[i].animStage+1==sprites[i].endframe)//can only be the last cycle so dont have to check it
                    {
                        sprites[i].framerate = 0;// no more animation, last frame is reached
                    }
                    else //keep doing animation while it doesnt reach last frame
                    {
                        sprites[i].animStage = (sprites[i].animStage + 1) % (sprites[i].endframe-sprites[i].startframe) ;
                    }
                }
            }
            spriteimage=spritedatabase[sprites[i].sprite].image;

            spriteimage->x=sprites[i].x;
            spriteimage->y=sprites[i].y;
//                if(sprites[i].angle)spriteimage->angle=(-sprites[i].angle)<<6;//change
//                	spriteimage->centerX = sprites[i].midx;
//	spriteimage->centerY = sprites[i].midy;
            //Tile to display
            ulSetImageTileSize (
                spriteimage,
                spritedatabase[sprites[i].sprite].sizex*sprites[i].column,																			//image, starting x
                spritedatabase[sprites[i].sprite].sizey*(sprites[i].animStage+sprites[i].startframe),	//starting y : size*(frame+startframe)
                spritedatabase[sprites[i].sprite].sizex,																// size x
                spritedatabase[sprites[i].sprite].sizey);															// size y

            ulMirrorImageH( spriteimage, sprites[i].flippedh);
            ulMirrorImageV( spriteimage, sprites[i].flippedv);
            ulSetDepth(sprites[i].prio);
            glPolyFmt(POLY_ALPHA(sprites[i].abcoeff) | POLY_CULL_NONE | POLY_ID(sprites[i].prio));
            ulSetImageTint(spriteimage,sprites[i].color);
            ulDrawImage(spriteimage);
            imagesused[sprites[i].sprite]=1;

        }
    }
    ulEndDrawing();
    ulEndFrame();

}

void myulDrawSpritesNoAnim ()
{
    int i;
    ulSetDepth(0);
    ulDrawMap(Mymap);
    for (i=0; i<=curMaxSprite ; i++)
    {
        if(sprites[i].used)
        {
            UL_IMAGE *spriteimage;
            spriteimage=spritedatabase[sprites[i].sprite].image;
            spriteimage->x=sprites[i].x;
            spriteimage->y=sprites[i].y;
            ulSetImageTileSize (
                spriteimage,
                spritedatabase[sprites[i].sprite].sizex*sprites[i].column,																			//image, starting x
                spritedatabase[sprites[i].sprite].sizey*(sprites[i].animStage+sprites[i].startframe),	//starting y : size*(frame+startframe)
                spritedatabase[sprites[i].sprite].sizex,																// size x
                spritedatabase[sprites[i].sprite].sizey);															// size y
            ulMirrorImageH( spriteimage, sprites[i].flippedh);
            ulMirrorImageV( spriteimage, sprites[i].flippedv);
            ulSetDepth(sprites[i].prio);
            glPolyFmt(POLY_ALPHA(sprites[i].abcoeff) | POLY_CULL_NONE | POLY_ID(sprites[i].prio));

            ulDrawImage(spriteimage);
        }
    }
}


