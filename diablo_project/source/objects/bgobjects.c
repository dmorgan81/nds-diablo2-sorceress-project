#include "../objects.h"
#include "bgobjects.h"
extern void noai (objectinfo* info);

bool bgobjectused[MAX_BGOBJECT];

s16 getUnusedBgObject(void)
{
    int i;
    for(i=0; i<MAX_BGOBJECT; i++)
    {
        if(bgobjectused[i]==0)
        {
            bgobjectused[i]=1;
            return i;
        }
    }
    return -1;
}
void deleteBgObject(s16 ID)
{
    bgobjects[ID].action=-1;
    bgobjects[ID].status=0;
    bgobjects[ID].life=0;
    if( bgobjects[ID].sprite != -1)
    {
        myulDeleteSprite(bgobjects[ID].sprite);
        bgobjects[ID].sprite=-1;
    }
    if (bgobjects[ID].fx[0]!=-1) deleteFX(bgobjects[ID].fx[0]);
    bgobjects[ID].fx[0]=-1;
    if (bgobjects[ID].fx[1]!=-1) deleteFX(bgobjects[ID].fx[1]);
    bgobjects[ID].fx[1]=-1;
    bgobjectused[ID]=0;
    if (ID==curMaxBgObject)curMaxBgObject--;
}

void loadBgData()
{
    int i;
    for(i=0; i<MAX_BGOBJECT; i++)
    {
        bgobjects[i].action=-1;
        bgobjects[i].sprite=-1;
        bgobjects[i].fx[0]=-1;
        bgobjects[i].fx[1]=-1;
        bgobjects[i].life=0;
        bgobjects[i].status=0;
        bgobjects[i].color=RGB15(31,31,31);
    }


    //tree
    bgdata[0].spritedata=-1;
    bgdata[0].deathspritedata=-1;
    bgdata[0].ai=&bgObjectAi;
    bgdata[0].tile=8;
    bgdata[0].vx=0;
    bgdata[0].vy=0;
    bgdata[0].life=500000;
    bgdata[0].dommages=0;
    bgdata[0].scroll=&scrollFXonly;
    bgdata[0].collision=&noai;
    bgdata[0].datanb=0;
    bgdata[0].hitbox.down.y=107;
    bgdata[0].hitbox.down.x=50;
    bgdata[0].hitbox.up.y=63;
    bgdata[0].hitbox.up.x=50;
    bgdata[0].hitbox.left.x=45;
    bgdata[0].hitbox.left.y=85;
    bgdata[0].hitbox.right.x=55;
    bgdata[0].hitbox.right.y=85;
    bgdata[0].fxdata[0]=3;
    bgdata[0].fxdata[1]=4;

    //fence
    bgdata[1].spritedata=-1;
    bgdata[1].deathspritedata=-1;
    bgdata[1].ai=&bgObjectAi;
    bgdata[1].tile=9;
    bgdata[1].vx=0;
    bgdata[1].vy=0;
    bgdata[1].life=500000;
    bgdata[1].dommages=0;
    bgdata[1].scroll=&scrollFXonly;
    bgdata[1].collision=&noai;
    bgdata[1].datanb=1;
    bgdata[1].hitbox.down.y=85;
    bgdata[1].hitbox.down.x=8;
    bgdata[1].hitbox.up.y=75;
    bgdata[1].hitbox.up.x=8;
    bgdata[1].hitbox.left.x=0;
    bgdata[1].hitbox.left.y=80;
    bgdata[1].hitbox.right.x=16;
    bgdata[1].hitbox.right.y=80;
    bgdata[1].fxdata[0]=5;
    bgdata[1].fxdata[1]=6;

    //wpfire
    bgdata[2].spritedata=-1;
    bgdata[2].deathspritedata=-1;
    bgdata[2].ai=&noai;
    bgdata[2].tile=2;
    bgdata[2].vx=0;
    bgdata[2].vy=0;
    bgdata[2].life=0;               //life=0 ==>missiles dont collide on it
    bgdata[2].dommages=0;
    bgdata[2].scroll=&scrollFXonly;
    bgdata[2].collision=&noai;
    bgdata[2].datanb=2;
    bgdata[2].hitbox.down.y=18;
    bgdata[2].hitbox.down.x=10;
    bgdata[2].hitbox.up.y=18;
    bgdata[2].hitbox.up.x=10;
    bgdata[2].hitbox.left.x=10;
    bgdata[2].hitbox.left.y=18;
    bgdata[2].hitbox.right.x=10;
    bgdata[2].hitbox.right.y=18;
    bgdata[2].fxdata[0]=7;
    bgdata[2].fxdata[1]=8;

    //torch

    bgdata[3].spritedata=-1;
    bgdata[3].deathspritedata=-1;
    bgdata[3].ai=&immortal;
    bgdata[3].tile=11;
    bgdata[3].vx=0;
    bgdata[3].vy=0;
    bgdata[3].life=500000;
    bgdata[3].dommages=0;
    bgdata[3].scroll=&scrollFXonly;
    bgdata[3].collision=&noai;
    bgdata[3].datanb=3;
    bgdata[3].hitbox.down.y=43;
    bgdata[3].hitbox.down.x=11;
    bgdata[3].hitbox.up.y=13;
    bgdata[3].hitbox.up.x=11;
    bgdata[3].hitbox.left.x=9;
    bgdata[3].hitbox.left.y=28;
    bgdata[3].hitbox.right.x=13;
    bgdata[3].hitbox.right.y=28;
    bgdata[3].fxdata[0]=9;
    bgdata[3].fxdata[1]=-1;

    //rock

    bgdata[4].spritedata=-1;
    bgdata[4].deathspritedata=-1;
    bgdata[4].ai=&noai;
    bgdata[4].tile=12;
    bgdata[4].vx=0;
    bgdata[4].vy=0;
    bgdata[4].life=0;
    bgdata[4].dommages=0;
    bgdata[4].scroll=&scrollFXonly;
    bgdata[4].collision=&noai;
    bgdata[4].datanb=4;
    bgdata[4].hitbox.down.y=14;
    bgdata[4].hitbox.down.x=8;
    bgdata[4].hitbox.up.y=2;
    bgdata[4].hitbox.up.x=8;
    bgdata[4].hitbox.left.x=2;
    bgdata[4].hitbox.left.y=8;
    bgdata[4].hitbox.right.x=14;
    bgdata[4].hitbox.right.y=8;
    bgdata[4].fxdata[0]=10;
    bgdata[4].fxdata[1]=-1;





    for(i=0; i<MAX_BGDATA; i++)
    {
        bgdata[i].hitbox.middle.x=bgdata[i].hitbox.down.x;
        bgdata[i].hitbox.middle.y=bgdata[i].hitbox.left.y;
    }
}
