#ifndef _TOP_SCREEN_H
#define _TOP_SCREEN_H
#include <PA9.h>					// Include for PA_Lib
#include <ulib/ulib.h>
#include "all_gfx.h"
#include "structures.h"


extern void MajStats();

extern charstruct sorc;
extern bool secondpast;


void QuickTopScreenRefresh (void);
void InitTopScreen (void);
#endif //_TOP_SCREEN_H
