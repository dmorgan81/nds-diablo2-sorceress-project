#include "collisions.h"

#include "Map.h"

extern charstruct sorc;







u8 GetTile(s32 x,s32 y)
{
    if(x<0 || y<0) return TILENB-1;
    //return map_col[y>>3][x>>3];//&45][x&60];
    return map_col[(x >> 3) + ((y >> 3) * MAPSIZE_X)];
}




u8 TileCollision(pointinfo* point, u8 flipped, s32 x, s32 y)
{
    return (GetTile(fix_norm(x)+point->x + (flipped*point->flipx), fix_norm(y)+point->y));
}






u8 anycollision(u8 tile,hitboxinfo* hitbox,int x, int y) // objectinfo* object
{
    if(TileCollision(&hitbox->left	, hitbox->flipped, x, y)==tile)return 1;
    if(TileCollision(&hitbox->right, hitbox->flipped, x, y)==tile)return 2;
    if(TileCollision(&hitbox->up	, hitbox->flipped, x, y)==tile)return 3;
    if(TileCollision(&hitbox->down	, hitbox->flipped, x, y)==tile)return 4;
    return 0;
}

u8 feetcollision(hitboxinfo* hitbox,int x, int y) // objectinfo* object
{
    if(TileCollision(&hitbox->left	, hitbox->flipped, x, y)>=NWALKABLETILE)return 1;
    if(TileCollision(&hitbox->right, hitbox->flipped, x, y)>=NWALKABLETILE)return 2;
    if(TileCollision(&hitbox->down	, hitbox->flipped, x-8, y)>=NWALKABLETILE)return 3;
    if(TileCollision(&hitbox->down	, hitbox->flipped, x, y)>=NWALKABLETILE)return 4;
    return 0;
}

bool boxcollision(hitboxinfo* hitbox1,s32 x1,s32 y1,hitboxinfo* hitbox2,s32 x2,s32 y2) /*s32 x2, s32 y2, u8 h2, u8 w2*/
{
    if(
        (   (fix_norm(x1)+hitbox1->middle.x) >= ((fix_norm(x2)+hitbox2->middle.x) - (( (hitbox2->right.x-hitbox2->left.x) + (hitbox1->right.x-hitbox1->left.x) )>>1))    )
        &&  (   (fix_norm(x1)+hitbox1->middle.x) <= ((fix_norm(x2)+hitbox2->middle.x) + (( (hitbox2->right.x-hitbox2->left.x) + (hitbox1->right.x-hitbox1->left.x) )>>1)) )
        &&  (   (fix_norm(y1)+hitbox1->middle.y) >= ((fix_norm(y2)+hitbox2->middle.y) - (( (hitbox2->down.y-hitbox2->up.y) + (hitbox1->down.y-hitbox1->up.y) )>>1))   )
        &&  (   (fix_norm(y1)+hitbox1->middle.y) <= ((fix_norm(y2)+hitbox2->middle.y) + (( (hitbox2->down.y-hitbox2->up.y) + (hitbox1->down.y-hitbox1->up.y) )>>1))   )
    )return 1;

    else return 0;
}



u8 TeleCollision(pointinfo point, u8 flipped,int x,int y)
{
    return (GetTile(fix_norm(sorc.x)+point.x + (flipped*point.flipx)+x, fix_norm(sorc.y)+point.y+y));
}


u8 anytelecollision(hitboxinfo hitbox,int x, int y)
{
    if(TeleCollision(hitbox.left, hitbox.flipped,x,y)>=NWALKABLETILE)return 1;
    if(TeleCollision(hitbox.right, hitbox.flipped,x,y)>=NWALKABLETILE)return 2;
    if(TeleCollision(hitbox.up, hitbox.flipped,x,y)>=NWALKABLETILE)return 3;
    if(TeleCollision(hitbox.down, hitbox.flipped,x,y)>=NWALKABLETILE)return 4;
    else return 0;
}



void zmCollision(objectinfo* zombie)
{
    if(boxcollision (&zombie->hitbox,zombie->x,zombie->y,&sorc.hitbox,sorc.x,sorc.y))
    {

        sorc.stats.vie_restante-=zombie->dommages;
//        PA_OutputText(1,0,0,"TOUCHEEEEEEEEEE %d",sorc.stats.vie_restante,zombie->dommages);
    }

}


void mCollision(objectinfo* missile)
{
    u16 i;
    for (i=0; i<MAX_OBJECT; i++)
    {

        if (objects[i].life>0)//vérifie que l'objet est bien en vie
        {

            if(boxcollision (&missile->hitbox,missile->x,missile->y,&objects[i].hitbox,objects[i].x,objects[i].y))
            {
                /*
                if(objects[i].life-=missile->dommages) objects[i].life=0;
                else objects[i].life-=missile->dommages;
                */
                objects[i].life-=missile->dommages;
                objects[i].status=missile->status;
                deletemissile(missile->arrayID);
                i=MAX_OBJECT;
            }

        }
    }
}



void orbCollision(objectinfo* missile)
{
    u16 i;
    for (i=0; i<MAX_OBJECT; i++)
    {

        if (objects[i].life>0)//vérifie que l'objet est bien en vie
        {

            if(boxcollision (&missile->hitbox,missile->x,missile->y,&objects[i].hitbox,objects[i].x,objects[i].y))
            {

                objects[i].life-=missile->dommages;
                objects[i].status=missile->status;
                i=MAX_OBJECT;
            }

        }
    }
}

void CheckSorcCollisions(void)
{

    while(TileCollision(&sorc.hitbox.left	, sorc.hitbox.flipped, sorc.x-sorc.hitbox.down.x, sorc.y-sorc.hitbox.down.y)>=NWALKABLETILE)
    {
        // Collision sur le côté gauche du sprite...
        sorc.x+= norm_fix(1); // Move by 1 pixel...
    }
    while(TileCollision(&sorc.hitbox.right, sorc.hitbox.flipped, sorc.x-sorc.hitbox.down.x, sorc.y-sorc.hitbox.down.y)>=NWALKABLETILE)
    {
        // Collision sur le côté droit du sprite...
        sorc.x-= norm_fix(1); // Move by 1 pixel...
    }
    while(TileCollision(&sorc.hitbox.up , sorc.hitbox.flipped, sorc.x-sorc.hitbox.down.x, sorc.y-sorc.hitbox.down.y)>=NWALKABLETILE)
    {
        // Collision au-dessus du sprite...
        sorc.y+=norm_fix(1);
    }
    while(TileCollision(&sorc.hitbox.down, sorc.hitbox.flipped, sorc.x-sorc.hitbox.down.x, sorc.y-sorc.hitbox.down.y)>=NWALKABLETILE)
    {
        // Collision sous le sprite...
        sorc.y -= norm_fix(1); // Move by 1 pixel...
    }

}

