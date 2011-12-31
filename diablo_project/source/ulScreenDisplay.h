#ifndef _ULDISPLAY_H
#define _ULDISPLAY_H



#include <PA9.h>					// Include for PA_Lib
#include <ulib/ulib.h>			// Include for µLib
#include "structures.h"
#include "defines.h"

spritestruct sprites[MAX_SPRITES];
spritedata spritedatabase[MAX_DATASPRITES];
bool imagesused[MAX_DATASPRITES];//change

UL_IMAGE *mapTiles;
UL_MAP *Mymap;


void myulInitData (bool again);
int myulCreateSprite (u8 data,int x,int y, int prio);
inline void myulDeleteSprite (int nb);
inline void myulImageFlip (int /*sprite*/nb,bool fliph,bool flipv);
inline void myulImageColumn (int /*sprite*/nb,int column);
//inline void myulImageAngle(int nb,int angle,int x,int y);
inline void myulAnimBegin (int spritenb);
inline void myulStartAnim (int spritenb, u8 sframe, u8 endframe, u8 framerate,int cycles);
inline void myulSetAnim (int spritenb, u8 sframe, u8 endframe, u8 framerate,int cycles);
inline void myulDefaultAnimRestart (int spritenb);
inline void myulDefaultAnim (int spritenb);
inline void myulmyulSetSpritePrio( int sprite, int prio);
inline void myulSetCycles (int sprite,int cycles);

void myulScreenDraws();
void myulDrawSprites(bool anim);

inline void myulSetSpriteAblending (int nb,int value);
inline void myulSetSpriteColor (int nb,u16 color);
inline void myulSetSpriteXY (int nb,int x,int y);
inline void myulSetSpriteX (int nb,int x);
inline void myulSetSpriteY (int nb,int y);
inline int myulGetSpriteX (int nb);
inline int myulGetSpriteY (int nb);
inline int myulGetSpriteAnim (int nb);

#define myulDrawDialogBox(IMAGE,DIALOGY0){\
    ulSetDepth(350);\
    glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_ID(256));\
\
    ulSetImageTileSize (IMAGE,0,0,8,8);\
\
    IMAGE->x=0;\
    IMAGE->y=DIALOGY0;\
    ulDrawImage(IMAGE);\
\
    IMAGE->x=248;\
    IMAGE->y=DIALOGY0;\
    ulMirrorImageH(IMAGE,1);\
    ulDrawImage(IMAGE);\
\
    IMAGE->x=248;\
    IMAGE->y=184;\
    ulMirrorImageV(IMAGE,1);\
    ulDrawImage(IMAGE);\
\
    IMAGE->x=0;\
    IMAGE->y=184;\
    ulMirrorImageH(IMAGE,0);\
    ulDrawImage(IMAGE);\
\
    ulSetImageTileSize (IMAGE,0,8,8,8);\
    ulMirrorImageH(IMAGE,0);\
    for (i=0; i<30; i++)\
    {\
        IMAGE->x=8+(i<<3);\
        IMAGE->y=DIALOGY0;\
        ulMirrorImageV(IMAGE,0);\
        ulDrawImage(IMAGE);\
        IMAGE->y=184;\
        ulMirrorImageV(IMAGE,1);\
        ulDrawImage(IMAGE);\
    }\
    ulSetImageTileSize (IMAGE,0,16,8,8);\
    for (i=0; i<((192-DIALOGY0)>>3)-2; i++)\
    {\
        IMAGE->y=DIALOGY0+8+(i<<3);\
        IMAGE->x=0;\
        ulMirrorImageH(IMAGE,0);\
        ulDrawImage(IMAGE);\
        IMAGE->x=248;\
        ulMirrorImageH(IMAGE,1);\
        ulDrawImage(IMAGE);\
    }\
    glPolyFmt(POLY_ALPHA(20) | POLY_CULL_NONE | POLY_ID(256));\
    ulDrawFillRect(2,DIALOGY0+2,254,190,0x0421);\
    glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_ID(256));\
    }


#endif //_ULDISPLAY_H
