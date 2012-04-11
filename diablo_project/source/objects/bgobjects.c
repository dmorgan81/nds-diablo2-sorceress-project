#include "../objects.h"
#include "bgobjects.h"
#include "../interface.h"
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


#include "bgobjectsdata.txt"


    for(i=0; i<MAX_BGDATA; i++)
    {
        bgdata[i].hitbox.middle.x=bgdata[i].hitbox.down.x;
        bgdata[i].hitbox.middle.y=bgdata[i].hitbox.left.y;
    }
}
