#ifndef _OBJECTS_H
#define _OBJECTS_H
#include <PA9.h>
#include "defines.h"
#include "structures.h"
#include "collisions.h"
#include "ulScreenDisplay.h"
extern objectdata data[MAXDATA];
extern objectdata mdata[MAXM_DATA];
extern objectinfo objects[MAX_OBJECT];
extern objectinfo missiles[MAX_MISSILE];
extern aurainfo auras[MAX_AURAS];

void initobjects (void);
void SpawnObjects();
void UpdateObjects();
void deleteobject(s16 ID);
void deletemissile(s16 ID);
void newObject(s32 x, s32 y, objectinfo* object,s16 ID, objectdata* data);
void newMissile(s32 x, s32 y, objectinfo* object,s16 ID, s16 angle, s16 vx, s16 vy ,int dommages, objectdata* data );
s16 getUnusedObject(void);
s16 getUnusedMissile(void);
s16 getUnusedFX(void);
void objectscroll(objectinfo* mover);
void ScrollFXonly(objectinfo* mover);
void missilescroll(objectinfo* mover);
void FXscroll(objectinfo* mover, bool nb);
s8 createFX (s8 datanb);
inline void deleteFX (s8 fx);


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
void orbscroll(objectinfo* mover);

void blazeAura (aurainfo* aura);
#endif
