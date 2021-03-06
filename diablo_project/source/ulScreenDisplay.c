#include "ulScreenDisplay.h"
#include "top_screen.h"
int curMaxSprite;//same trick as in objects.c

sprite_columns columns[50];


void myulInitData ()
{
    int i;
    ulSetTransparentColor(RGB15(31, 0, 31));
#include "spritesdata.txt" //all data in txt file to avoid overload of the c file
    //au cas ou

    for (i=0; i<MAX_SPRITES ; i++)
    {
        sprites[i].used=0;
        sprites[i].sprite=-1;
        sprites[i].prio=-1;
        sprites[i].color=RGB15(31, 31, 31);
        sprites[i].cycles=0;
    }
    //la map
    //mapTiles = ulLoadImageFilePNG((void*)map_png, (int)map_png_size, UL_IN_VRAM, UL_PF_PAL4);
    //Mymap = ulCreateMap(mapTiles,/*Tileset*/map,8,8,/*Tiles size*/60,45,/*Map size*/UL_MF_U16);//Map format
    //map_col=tilescollision_map;
    ulSetAutoDepth(0);

}

void myulLoadSprite(int data)
{
    if(!spritedatabase[data].image)
    {
        spritedatabase[data].image=ulLoadImageFilePNG(spritedatabase[data].file, 0, UL_IN_RAM, spritedatabase[data].palCount);
        while(spritedatabase[data].image == NULL)
        {
            ERROR("couldnt load sprite");
            WaitForVBL();
        }
        //spritedatabase[data].loaded=TRUE;
    }
}

void myulLoadSpriteFromFile(char* fname)
{
    FILE* file=NULL;
    int data=-1;
    file=fopen(fname,"r");
    if(file)
    {
        //each line contain a datasprite number
        while(fscanf(file,"%i\n",&data) != EOF)myulLoadSprite(data);
    }
}

void myulFreeSprite(int data)
{
    if(spritedatabase[data].image)ulDeleteImage(spritedatabase[data].image);
    //spritedatabase[data].loaded=FALSE;
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
        sprites[nb].endframe=spritedatabase[data].nbframe-1;
        sprites[nb].framerate=spritedatabase[data].framerate;
        sprites[nb].abcoeff=spritedatabase[data].abcoeff;
        sprites[nb].animStage=0;
        sprites[nb].frameNumber=0;
        sprites[nb].color=RGB15(31, 31, 31);
        sprites[nb].cycles=spritedatabase[data].cycles;
        sprites[nb].colInfo=spritedatabase[data].colInfo;
        myulSetSpritePrio( nb, prio);
        if (nb>curMaxSprite)curMaxSprite=nb;
    }
    else
    {
        //PA_OutputText(1,15,17,"SPRITES LIMIT REACHED");
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
    //sprites[nb].colInfo=spritedatabase[sprites[nb].sprite].colInfo+column;
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
    sprites[spritenb].cycles=cycles;
}

inline void myulDefaultAnimRestart (int spritenb)
{
    sprites[spritenb].startframe=0;
    sprites[spritenb].endframe=spritedatabase[sprites[spritenb].sprite].nbframe-1;
    sprites[spritenb].framerate=spritedatabase[sprites[spritenb].sprite].framerate;
    sprites[spritenb].frameNumber=0;
    sprites[spritenb].animStage=0;
    sprites[spritenb].cycles=0;
}

inline void myulDefaultAnim (int spritenb)
{
    sprites[spritenb].startframe=0;
    sprites[spritenb].endframe=spritedatabase[sprites[spritenb].sprite].nbframe-1;
    sprites[spritenb].framerate=spritedatabase[sprites[spritenb].sprite].framerate;
    sprites[spritenb].cycles=0;
}

inline void myulSetSpritePrio( int sprite, int prio)
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


int shakeframes=0;
inline void myulStartShake (int frames)
{
    shakeframes=frames;
}

void myulShakeScreen()
{
    if (shakeframes)
    {
        ulMoveScreenView(PA_RandMinMax(-3,3),PA_RandMinMax(-3,3));
        shakeframes--;
    }
    else ulMoveScreenView(0,0);
}
//use this to clear vram, must be used before drawing menu to avoid to fulfill vram
void myulUnrealizeSprites()
{
    int i;
    for (i=1; i<MAX_DATASPRITES; i++)
    {
        ulUnrealizeImage(spritedatabase[i].image);
    }
}

void myulScreenDraws()
{
    ulStartDrawing2D();

    ulSetDepth(0);
    myulShakeScreen();
    //Fond sur l'�cran du bas
    glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_ID(0));
#ifndef Test
    ulDrawMap(Mymap);
#else
    ulDrawGradientRect(0, 0, 256, 192, RGB15(0, 0, 24), RGB15(0, 0, 0), RGB15(0, 0, 0), RGB15(0, 0, 24));
#endif
    UL_IMAGE *spriteimage;
    int i;
    for (i=0; i<=curMaxSprite ; i++)
    {
        if(sprites[i].used)
        {
            if(sprites[i].framerate)
            {
                sprites[i].frameNumber++;
                if (sprites[i].frameNumber == sprites[i].framerate )
                {
                    if (sprites[i].cycles)//it is not a loop
                    {
                        topPrintf(128,70,"%i",sprites[i].animStage);
                        topPrintf(128,78,"%i",sprites[i].startframe);
                        topPrintf(128,86,"%i",sprites[i].endframe);
                        topPrintf(128,94,"%i",sprites[i].framerate);
                        topPrintf(128,102,"%i",sprites[i].sprite);

                        //last frame? a cycle might have ended
                        if (((sprites[i].animStage + 1) == (sprites[i].endframe-sprites[i].startframe+1))) sprites[i].cycles--;
                        if(!sprites[i].cycles) sprites[i].framerate = 0;// no more animation, last frame and cycle were reached
                        else sprites[i].animStage = (sprites[i].animStage + 1) % (sprites[i].endframe-sprites[i].startframe+1) ;
                    }
                    else sprites[i].animStage = (sprites[i].animStage + 1) % (sprites[i].endframe-sprites[i].startframe+1) ;
                    sprites[i].frameNumber=0;
                }
            }
            myulLoadSprite(sprites[i].sprite);
            spriteimage=spritedatabase[sprites[i].sprite].image;

            spriteimage->x=sprites[i].x;
            spriteimage->y=sprites[i].y;
//                if(sprites[i].angle)spriteimage->angle=(-sprites[i].angle)<<6;//change
//                	spriteimage->centerX = sprites[i].midx;
//	spriteimage->centerY = sprites[i].midy;
            //Tile to display
            ulSetImageTileSize (
                spriteimage,
                sprites[i].colInfo->offset.x+(spritedatabase[sprites[i].sprite].regular*sprites[i].colInfo->size.x*sprites[i].column),																			//image, starting x
                sprites[i].colInfo->size.y*(sprites[i].animStage+sprites[i].startframe),	//starting y : size*(frame+startframe)
                sprites[i].colInfo->size.x,																// size x
                sprites[i].colInfo->size.y);															// size y

            ulMirrorImageH( spriteimage, sprites[i].flippedh);
            ulMirrorImageV( spriteimage, sprites[i].flippedv);
            ulSetDepth(sprites[i].prio);
            glPolyFmt(POLY_ALPHA(sprites[i].abcoeff) | POLY_CULL_NONE | POLY_ID(sprites[i].prio));
            ulSetImageTint(spriteimage,sprites[i].color);
            ulDrawImage(spriteimage);
            imagesused[sprites[i].sprite]=1;
        }
    }
//ulPrintf_xy(0,0,"%d",Counter[VBL]);
    ulEndDrawing();
}

void myulDrawSprites(bool anim)
{
    int i;
    ulSetDepth(0);
    myulShakeScreen();
    ulDrawMap(Mymap);
    UL_IMAGE *spriteimage;
    for (i=0; i<=curMaxSprite ; i++)
    {
        if(sprites[i].used)
        {
            if(sprites[i].framerate&&anim)
            {
                sprites[i].frameNumber++;
                if (sprites[i].frameNumber == sprites[i].framerate )
                {
                    if (sprites[i].cycles)//it is not a loop
                    {
                        topPrintf(128,70,"%i",sprites[i].animStage + 1);
                        //last frame? a cycle might have ended
                        if (!((sprites[i].animStage + 1) % (sprites[i].endframe-sprites[i].startframe))) sprites[i].cycles--;
                        if(!sprites[i].cycles) sprites[i].framerate = 0;// no more animation, last frame and cycle were reached
                        else sprites[i].animStage = (sprites[i].animStage + 1) % (sprites[i].endframe-sprites[i].startframe) ;
                    }
                    else sprites[i].animStage = (sprites[i].animStage + 1) % (sprites[i].endframe-sprites[i].startframe) ;
                    sprites[i].frameNumber=0;
                }
            }
            myulLoadSprite(sprites[i].sprite);
            spriteimage=spritedatabase[sprites[i].sprite].image;
            spriteimage->x=sprites[i].x;
            spriteimage->y=sprites[i].y;
            ulSetImageTileSize (
                spriteimage,
                sprites[i].colInfo->offset.x+(spritedatabase[sprites[i].sprite].regular*sprites[i].colInfo->size.x*sprites[i].column),																			//image, starting x
                sprites[i].colInfo->size.y*(sprites[i].animStage+sprites[i].startframe),	//starting y : size*(frame+startframe)
                sprites[i].colInfo->size.x,																// size x
                sprites[i].colInfo->size.y);														// size y
            ulMirrorImageH( spriteimage, sprites[i].flippedh);
            ulMirrorImageV( spriteimage, sprites[i].flippedv);
            ulSetDepth(sprites[i].prio);
            glPolyFmt(POLY_ALPHA(sprites[i].abcoeff) | POLY_CULL_NONE | POLY_ID(sprites[i].prio));

            ulDrawImage(spriteimage);
        }
    }
}

void myulDrawBlackScreen()
{
    ulStartDrawing2D();
    ulDrawFillRect(0,0,256,192,RGB15(0,0,0));
    ulEndDrawing();
    ulSyncFrame();
    ulEndFrame();
}


