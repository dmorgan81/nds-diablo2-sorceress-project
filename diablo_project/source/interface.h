#ifndef _INTERFACE_H
#define _INTERFACE_H

#include <ulib/ulib.h>
#include "structures.h"
#include "ulScreenDisplay.h"
#include "objects.h"
#include "actions.h"
#include "top_screen.h"

void pause (u8 *quitcondition);
void DialogInBox(char* dialog,int speed);
void skillmenu(bool levelup);
void death();









#endif
