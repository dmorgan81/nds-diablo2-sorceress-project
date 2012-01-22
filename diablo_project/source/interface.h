#ifndef _INTERFACE_H
#define _INTERFACE_H

#include <ulib/ulib.h>
#include "structures.h"
#include "ulScreenDisplay.h"
#include "objects.h"
#include "actions.h"
#include "top_screen.h"
#include "Maps/Map.h"
void pause ();
void save();
void load();
void saveloadmenu(bool saveload);
void waypointmenu(objectinfo* wp);
void DialogInBox(char* dialog,int speed,bool anim);
void skillmenu(bool levelup);
void death();










#endif
