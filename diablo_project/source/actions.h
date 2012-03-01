#ifndef _ACTIONS_H
#define _ACTIONS_H

#include <ulib/ulib.h>
#include "PA_Math.h"

#include "structures.h"
#include "defines.h"
#include "ulScreenDisplay.h"
#include "objects.h"
#include "interface.h"

extern charstruct hero;
extern spritestruct sprites[MAX_SPRITES];
extern u8 skillsLevels[SKILLNUMBER];
extern int skilldmg[SKILLNUMBER][2];
extern u8 currentSkill[2];
extern inline void myulStartAnim (int spritenb, u8 sframe, u8 endframe, u8 framerate,int cycles);

void Sort(int X,int Y);
void CheckForLevelUp();
void updateAuras();

void nospell (int a, int b, u16 c,u8 d);
void firebolt (int x,int y,u16 angle,u8 level);
void icebolt (int x,int y,u16 angle,u8 level);
void chargedbolt (int x,int y,u16 angle,u8 level);
void iceorb (int x,int y,u16 angle,u8 level);
void blaze(int x,int y,u16 angle,u8 level);
void firewall (int x,int y,u16 angle,u8 level);
void hydra (int x,int y,u16 angle,u8 level);
void teleport(int x,int y,u16 angle,u8 level);

void (*selectedSkill[2]) (int,int,u16,u8);
int skillCost[2];


#endif
