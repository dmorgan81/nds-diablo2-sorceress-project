#ifndef _MAIN_H
#define _MAIN_H

#include <PA9.h>					// Include for PA_Lib
#include <ulib/ulib.h>			// Include for µLib
//#include "efs_lib.h"				// Include for EFS_lib

#include "all_gfx.h"
#include "d_Splash2_png.h"
#include "loading_png.h"

#include "structures.h"
#include "defines.h"
#include "ulScreenDisplay.h"
#include "top_screen.h"
#include "actions.h"
#include "objects.h"
#include "objects/collisions.h"
#include "interface.h"
void movechar();
void noactioncheck();
/*extern void Sort(int X,int Y);
extern void InitTopScreen (void);
extern void QuickTopScreenRefresh (void);*/

extern UL_MAP *Mymap;
#endif //_MAIN_H
