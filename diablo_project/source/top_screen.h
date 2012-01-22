#ifndef _TOP_SCREEN_H
#define _TOP_SCREEN_H
#include <ulib/ulib.h>
#include "PA_Math.h"					// Include for PA_Lib
//#include "all_gfx.h"
#include "structures.h"


extern void MajStats();

extern charstruct hero;
extern bool secondpast;



void QuickTopScreenRefresh (void);
void InitTopScreen (void);
void topDrawImage(int x,int y,char* source,int offsetx,int offsety,int sizex, int sizey,int dataheight);
void topUpdateLevel(void);
void topDrawString(int x,int y,char* string);
#define topDrawChar(character,x,y) topDrawImage(x,y,topscr_font,(((character)-32)*8)&255,(((character)-32)>>5)<<3,8,8,256)
#define topPrintf(x, y, format...)		({ char __str[500]; sprintf(__str , ##format); topDrawString(x, y, __str); })


#endif //_TOP_SCREEN_H
