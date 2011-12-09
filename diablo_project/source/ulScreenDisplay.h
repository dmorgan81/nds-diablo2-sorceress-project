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
inline void myulSetSpritePrio( int sprite, int prio);
void myulScreenDraws(void);

inline void SetSpriteAblending (int nb,int value);
inline void SetSpriteColor (int nb,u16 color);
inline void SetSpriteXY (int nb,int x,int y);
inline void SetSpriteX (int nb,int x);
inline void SetSpriteY (int nb,int y);
inline int GetSpriteX (int nb);
inline int GetSpriteY (int nb);




#endif //_ULDISPLAY_H
