#ifndef _MAIN_H
#define _MAIN_H

// Include for PA_Lib
#include <ulib/ulib.h>			// Include for µLib

#include <filesystem.h>
#include "PA_Math.h"
//#include "efs_lib.h"				// Include for EFS_lib

//#include "all_gfx.h"
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

extern UL_MAP *Mymap;
#endif //_MAIN_H
