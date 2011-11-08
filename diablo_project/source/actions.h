#ifndef _ACTIONS_H
#define _ACTIONS_H

#include <PA9.h>
#include <ulib/ulib.h>
#include "structures.h"
#include "defines.h"
#include "ulScreenDisplay.h"
#include "objects.h"

extern charstruct hero;
extern spritestruct sprites[MAX_SPRITES];
extern inline void myulStartAnim (int spritenb, u8 sframe, u8 endframe, u8 framerate);

void Sort(int X,int Y);

void nospell (int a, int b, u16 c);
void firebolt (int x,int y,u16 angle);
void icebolt (int x,int y,u16 angle);
void chargedbolt (int x,int y,u16 angle);
void iceorb (int x,int y,u16 angle);
void blaze(int x,int y,u16 angle);
void firewall (int x,int y,u16 angle);
void hydra (int x,int y,u16 angle);
void teleport(int x,int y,u16 angle);

void (*sortchoisi[2]) (int,int,u16);
int cout_sort[2];


#endif
