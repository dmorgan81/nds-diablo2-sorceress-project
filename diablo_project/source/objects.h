#ifndef _OBJECTS_H
#define _OBJECTS_H
#include <nds.h>
#include "PA_Math.h"
#include "defines.h"
#include "structures.h"
#include "objects/collisions.h"
#include "objects/bgobjects.h"
#include "ulScreenDisplay.h"
extern objectdata data[MAX_DATA];
extern objectdata bgdata[MAX_BGDATA];
extern objectdata mdata[MAX_MDATA];
extern objectinfo objects[MAX_OBJECT];
extern objectinfo bgobjects[MAX_BGOBJECT];
extern objectinfo missiles[MAX_MISSILE];
extern aurainfo auras[MAX_AURAS];
extern fx_data fxdata[MAX_FXDATA];
extern fx_info fxinfo[MAX_FX];
extern int curMaxObject,curMaxBgObject,curMaxMissile;

void initObjects (void);
void spawnObjects();
void updateObjects();
void deleteObject(s16 ID);
void deleteMissile(s16 ID);
void newObject(s32 x, s32 y, objectinfo* object,s16 ID, objectdata* data,bool array);
void newMissile(s32 x, s32 y, objectinfo* object,s16 ID, s16 angle, s16 vx, s16 vy ,int dommages, objectdata* data );
s16 getUnusedObject(void);
s16 getUnusedMissile(void);
s16 getUnusedFX(void);
s16 createFX (s16 datanb);
inline void deleteFX (s16 fx);

void mobDeath(objectinfo* mob,int time);
void deadMob(objectinfo* mob);

//scrolling
void objectScroll(objectinfo* mover);
void scrollFXonly(objectinfo* mover);
void missileScroll(objectinfo* mover);
void FXscroll(objectinfo* mover, bool nb);
void onemDirScroll(objectinfo* mover);
void deadScroll(objectinfo* mover);

//ais
inline void immortal(objectinfo* object);
void bgObjectAi(objectinfo* object);
void zombieAI(objectinfo* zombie);
void meleeAI(objectinfo* melee);
void chargedboltAI (objectinfo* missile);
void missileAI (objectinfo* missile);
void orbAI (objectinfo* missile);
void fireAI(objectinfo* missile);
void hydraAI(objectinfo* missile);


void blazeAura (aurainfo* aura);
#endif
