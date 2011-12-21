#ifndef _COLLISIONS_H
#define _COLLISIONS_H

#include <PA9.h>
#include "../structures.h"
#include "../defines.h"
#include "../objects.h"

u8 GetTile(s32 x,s32 y);
u8 TileCollision(pointinfo* point, u8 flipped, s32 x, s32 y);
u8 anycollision(u8 tile,hitboxinfo* hitbox,int x, int y);
u8 feetcollision(hitboxinfo* hitbox,int x, int y);
bool boxcollision(hitboxinfo* hitbox1,s32 x1,s32 y1,hitboxinfo* hitbox2,s32 x2,s32 y2);
u8 TeleCollision(pointinfo point, u8 flipped,int x,int y);
u8 anytelecollision(hitboxinfo hitbox,int x, int y);
void CheckSorcCollisions(void);
void mCollision(objectinfo* missile);
void orbCollision(objectinfo* missile);
void CheckheroCollisions(void);




#endif
