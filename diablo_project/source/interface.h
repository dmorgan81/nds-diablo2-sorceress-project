#ifndef _INTERFACE_H
#define _INTERFACE_H

#include <ulib/ulib.h>
#include "structures.h"

void pause ();
void save();
void load();
void mainmenu();
void saveloadmenu(bool saveload);
void waypointAI(objectinfo* wp);
void DialogInBox(char* dialog,int speed,char* topBg,char* sound,int soundOffset,bool anim);
void skillmenu(bool levelup);
void death();










#endif
