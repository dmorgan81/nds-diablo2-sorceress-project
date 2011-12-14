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

void myulScreenDraws(void);
void myulDrawSpritesNoAnim ();

inline void myulSetSpriteAblending (int nb,int value);
inline void myulSetSpriteColor (int nb,u16 color);
inline void myulSetSpriteXY (int nb,int x,int y);
inline void myulSetSpriteX (int nb,int x);
inline void myulSetSpriteY (int nb,int y);
inline int myulGetSpriteX (int nb);
inline int myulGetSpriteY (int nb);
inline int myulGetSpriteAnim (int nb);




#endif //_ULDISPLAY_H
