#include "ulScreenDisplay.h"
#include "uldata.h"



void myulInitData (bool again)
{

///sorceress
    ulSetTransparentColor(RGB15(31, 0, 31));
    {
        spritedatabase[0].image = ulLoadImageFilePNG((void*)sorc_png, (int)sorc_png_size, UL_IN_RAM, UL_PF_PAL4);
    }
    spritedatabase[0].nbframe=5;
    spritedatabase[0].framerate=9;
    spritedatabase[0].sizex=32;
    spritedatabase[0].sizey=64;
    spritedatabase[0].abcoeff=31;


///Tyrael - body
    ulSetTransparentColor(RGB15(31, 0, 31));
    {
        spritedatabase[1].image = ulLoadImageFilePNG((void*)tyr_body_png, (int)tyr_body_png_size, UL_IN_RAM, UL_PF_PAL4);
    }
    spritedatabase[1].nbframe=1;
    spritedatabase[1].framerate=30;//8;
    spritedatabase[1].sizex=24;
    spritedatabase[1].sizey=50;
    spritedatabase[1].abcoeff=31;
///Tyrael - wings
    ulSetTransparentColor(RGB15(31, 0, 31));
    {
        spritedatabase[2].image = ulLoadImageFilePNG((void*)tyr_wings_png, (int)tyr_wings_png_size, UL_IN_RAM, UL_PF_PAL4);
    }
    spritedatabase[2].nbframe=3;
    spritedatabase[2].framerate=15;//8;
    spritedatabase[2].sizex=96;
    spritedatabase[2].sizey=70;
    spritedatabase[2].abcoeff=22;
///Firebolt
    ulSetTransparentColor(RGB15(31, 0, 31));
    {
        spritedatabase[3].image = ulLoadImageFilePNG((void*)firebolt_png, (int)firebolt_png_size, UL_IN_RAM, UL_PF_PAL4);
    }
    spritedatabase[3].nbframe=2;
    spritedatabase[3].framerate=8;//8;
    spritedatabase[3].sizex=32;
    spritedatabase[3].sizey=16;
    spritedatabase[3].abcoeff=31;

///icebolt
    ulSetTransparentColor(RGB15(31, 0, 31));
    {
        spritedatabase[4].image = ulLoadImageFilePNG((void*)icebolt_png, (int)icebolt_png_size, UL_IN_RAM, UL_PF_PAL4);
    }
    spritedatabase[4].nbframe=2;
    spritedatabase[4].framerate=8;//8;
    spritedatabase[4].sizex=32;
    spritedatabase[4].sizey=16;
    spritedatabase[4].abcoeff=24;
    ulSetTransparentColor(RGB15(31, 0, 31));
///iceorb
    ulSetTransparentColor(RGB15(31, 0, 31));
    {
        spritedatabase[5].image = ulLoadImageFilePNG((void*)iceorb_png, (int)iceorb_png_size, UL_IN_RAM, UL_PF_PAL4);
    }
    spritedatabase[5].nbframe=2;
    spritedatabase[5].framerate=8;//8;
    spritedatabase[5].sizex=16;
    spritedatabase[5].sizey=16;
    spritedatabase[5].abcoeff=20;

///zombie
    ulSetTransparentColor(RGB15(31, 0, 31));
    {
        spritedatabase[6].image = ulLoadImageFilePNG((void*)zombie_png, (int)zombie_png_size, UL_IN_RAM, UL_PF_PAL4);
    }
    spritedatabase[6].nbframe=2;
    spritedatabase[6].framerate=8;//8;
    spritedatabase[6].sizex=14;
    spritedatabase[6].sizey=33;
    spritedatabase[6].abcoeff=31;

///firebig
    ulSetTransparentColor(RGB15(31, 0, 31));
    {
        spritedatabase[7].image = ulLoadImageFilePNG((void*)firebig_png, (int)firebig_png_size, UL_IN_RAM, UL_PF_PAL4);
    }
    spritedatabase[7].nbframe=10;
    spritedatabase[7].framerate=8;//8;
    spritedatabase[7].sizex=32;
    spritedatabase[7].sizey=67;
    spritedatabase[7].abcoeff=20;
///firesmall
    ulSetTransparentColor(RGB15(31, 0, 31));
    {
        spritedatabase[8].image = ulLoadImageFilePNG((void*)firesmall_png, (int)firesmall_png_size, UL_IN_RAM, UL_PF_PAL4);
    }
    spritedatabase[8].nbframe=5;
    spritedatabase[8].framerate=8;//8;
    spritedatabase[8].sizex=24;
    spritedatabase[8].sizey=30;
    spritedatabase[8].abcoeff=25;
///hydra
    ulSetTransparentColor(RGB15(31, 0, 31));
    {
        spritedatabase[9].image = ulLoadImageFilePNG((void*)hydra_png, (int)hydra_png_size, UL_IN_RAM, UL_PF_PAL4);
    }
    spritedatabase[9].nbframe=4;
    spritedatabase[9].framerate=8;//8;
    spritedatabase[9].sizex=40;
    spritedatabase[9].sizey=37;
    spritedatabase[9].abcoeff=31;


///tree
    ulSetTransparentColor(RGB15(31, 0, 31));
    {
        spritedatabase[10].image = ulLoadImageFilePNG((void*)tree_png, (int)tree_png_size, UL_IN_RAM, UL_PF_PAL4);
    }
    spritedatabase[10].nbframe=0;
    spritedatabase[10].framerate=8;//8;
    spritedatabase[10].sizex=50;
    spritedatabase[10].sizey=107;
    spritedatabase[10].abcoeff=31;

///fence
    ulSetTransparentColor(RGB15(31, 0, 31));
    {
        spritedatabase[11].image = ulLoadImageFilePNG((void*)fence_png, (int)fence_png_size, UL_IN_RAM, UL_PF_PAL4);
    }
    spritedatabase[11].nbframe=0;
    spritedatabase[11].framerate=8;//8;
    spritedatabase[11].sizex=16;
    spritedatabase[11].sizey=85;
    spritedatabase[11].abcoeff=31;

///Fallen
    ulSetTransparentColor(RGB15(31, 0, 31));
    {
        spritedatabase[12].image = ulLoadImageFilePNG((void*)fallen_png, (int)fallen_png_size, UL_IN_RAM, UL_PF_PAL4);
    }
    spritedatabase[12].nbframe=5;
    spritedatabase[12].framerate=8;//8;
    spritedatabase[12].sizex=32;
    spritedatabase[12].sizey=32;
    spritedatabase[12].abcoeff=31;

///small fire at wp
    ulSetTransparentColor(RGB15(31, 0, 31));
    {
        spritedatabase[13].image = ulLoadImageFilePNG((void*)wpfire_png, (int)wpfire_png_size, UL_IN_RAM, UL_PF_PAL4);
    }
    spritedatabase[13].nbframe=8;
    spritedatabase[13].framerate=8;//8;
    spritedatabase[13].sizex=10;
    spritedatabase[13].sizey=18;
    spritedatabase[13].abcoeff=31;

///chargedbolt
    ulSetTransparentColor(RGB15(31, 0, 31));
    {
        spritedatabase[14].image = ulLoadImageFilePNG((void*)chargedbolt_png, (int)chargedbolt_png_size, UL_IN_RAM, UL_PF_PAL4);
    }
    spritedatabase[14].nbframe=10;
    spritedatabase[14].framerate=3;//8;
    spritedatabase[14].sizex=18;
    spritedatabase[14].sizey=20;
    spritedatabase[14].abcoeff=25;

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

inline void myulStartAnim (int spritenb, u8 sframe, u8 endframe, u8 framerate)
{
    sprites[spritenb].startframe=sframe;
    sprites[spritenb].endframe=endframe;
    sprites[spritenb].framerate=framerate;
    sprites[spritenb].frameNumber=0;
    sprites[spritenb].animStage=0;
}


inline void myulSetAnim (int spritenb, u8 sframe, u8 endframe, u8 framerate)
{
    sprites[spritenb].startframe=sframe;
    sprites[spritenb].endframe=endframe;
    sprites[spritenb].framerate=framerate;
}

inline void myulDefaultAnimRestart (int spritenb)
{
    sprites[spritenb].startframe=0;
    sprites[spritenb].endframe=spritedatabase[sprites[spritenb].sprite].nbframe;
    sprites[spritenb].framerate=spritedatabase[sprites[spritenb].sprite].framerate;
    sprites[spritenb].frameNumber=0;
    sprites[spritenb].animStage=0;
}

inline void myulDefaultAnim (int spritenb)
{
    sprites[spritenb].startframe=0;
    sprites[spritenb].endframe=spritedatabase[sprites[spritenb].sprite].nbframe;
    sprites[spritenb].framerate=spritedatabase[sprites[spritenb].sprite].framerate;
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
                    if (sprites[sprite].frameNumber % sprites[sprite].framerate  == 0) sprites[sprite].animStage = (sprites[sprite].animStage + 1) % (sprites[sprite].endframe-sprites[sprite].startframe) ;
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




