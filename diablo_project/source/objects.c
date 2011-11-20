#include "objects.h"

void noai (objectinfo* info) {}
objectdata data[MAX_DATA];
objectdata bgdata[MAX_BGDATA];
objectdata mdata[MAX_MDATA];
objectinfo objects[MAX_OBJECT];
objectinfo bgobjects[MAX_BGOBJECT];
objectinfo missiles[MAX_MISSILE];
fx_data fxdata[MAX_FXDATA];
fx_info fxinfo[MAX_FX];
aurainfo auras[MAX_AURAS];

bool objectused[MAX_OBJECT];
bool missileused[MAX_MISSILE];
void initobjects (void)
{
    loadBgData();
//Objects
    int i;
    for(i=0; i<MAX_OBJECT; i++)
    {
        objects[i].action=-1;
        objects[i].sprite=-1;
        objects[i].fx[0]=-1;
        objects[i].fx[1]=-1;
        objects[i].life=0;
        objects[i].status=0;
        objects[i].color=RGB15(31,31,31);
    }
    for(i=0; i<MAX_FX; i++)
    {
        fxinfo[i].used=0;
        fxinfo[i].sprite=-1;
    }
//tyrael
    data[0].spritedata=1;
    data[0].deathspritedata=-1;
    data[0].ai=&immortal;
    data[0].tile=0;
    data[0].vx=0;
    data[0].vy=0;
    data[0].life=500000;
    data[0].scroll=&objectscroll;
    data[0].collision=&noai;
    data[0].datanb=0;
    data[0].hitbox.down.y=50;
    data[0].hitbox.down.x=12;
    data[0].hitbox.up.y=0;
    data[0].hitbox.up.x=12;
    data[0].hitbox.left.x=0;
    data[0].hitbox.left.y=25;
    data[0].hitbox.right.x=24;
    data[0].hitbox.right.y=25;
    data[0].fxdata[0]=0;
    data[0].fxdata[1]=1;
//zombie
    data[1].spritedata=6;
    data[1].deathspritedata=-1;
    data[1].ai=&zombieAI;
    data[1].tile=0;
    data[1].vx=0;
    data[1].vy=0;
    data[1].life=50;
    data[1].dommages=1;
    data[1].scroll=&objectscroll;
    data[1].collision=&zmCollision;
    data[1].datanb=1;
    data[1].hitbox.down.y=33;
    data[1].hitbox.down.x=7;
    data[1].hitbox.up.y=0;
    data[1].hitbox.up.x=7;
    data[1].hitbox.left.x=0;
    data[1].hitbox.left.y=16;
    data[1].hitbox.right.x=14;
    data[1].hitbox.right.y=16;
    data[1].fxdata[0]=-1;
    data[1].fxdata[1]=-1;


//fallen
    data[2].spritedata=12;
    data[2].deathspritedata=-1;
    data[2].ai=&meleeAI;
    data[2].tile=0;
    data[2].vx=0;
    data[2].vy=0;
    data[2].life=50;
    data[2].dommages=0;
    data[2].scroll=&objectscroll;
    data[2].collision=&zmCollision;
    data[2].datanb=2;
    data[2].hitbox.down.y=27;
    data[2].hitbox.down.x=14;
    data[2].hitbox.up.y=5;
    data[2].hitbox.up.x=14;
    data[2].hitbox.left.x=6;
    data[2].hitbox.left.y=16;
    data[2].hitbox.right.x=22;
    data[2].hitbox.right.y=16;
    data[2].fxdata[0]=-1;
    data[2].fxdata[1]=-1;


    for(i=0; i<MAX_DATA; i++)
    {
        data[i].hitbox.middle.x=data[i].hitbox.down.x;
        data[i].hitbox.middle.y=data[i].hitbox.left.y;
    }


//missiles data

    for(i=0; i<MAX_MISSILE; i++)
    {
        missiles[i].action=-1;
        missiles[i].sprite=-1;
        missiles[i].fx[0]=-1;
        missiles[i].fx[1]=-1;
        missiles[i].color=RGB15(31,31,31);
    }
//firebolt
    mdata[0].spritedata=3;
    mdata[0].ai=&missileAI;
    mdata[0].vx=0;
    mdata[0].vy=0;
    mdata[0].life=256;
    mdata[0].dommages=25;
    mdata[0].status=S_ALARMED;
    mdata[0].scroll=&missilescroll;
    mdata[0].collision=&mCollision;
    mdata[0].datanb=0;
    mdata[0].hitbox.down.y=13;
    mdata[0].hitbox.down.x=15;
    mdata[0].hitbox.up.y=6;
    mdata[0].hitbox.up.x=15;
    mdata[0].hitbox.left.x=13;
    mdata[0].hitbox.left.y=9;
    mdata[0].hitbox.right.x=19;
    mdata[0].hitbox.right.y=9;
    mdata[0].fxdata[0]=-1;
    mdata[0].fxdata[1]=-1;
//icebolt
    mdata[1].spritedata=4;
    mdata[1].ai=&missileAI;
    mdata[1].vx=0;
    mdata[1].vy=0;
    mdata[1].dommages=5;
    mdata[1].life=256;
    mdata[1].status=S_ALARMED|S_COLD;
    mdata[1].scroll=&missilescroll;
    mdata[1].collision=&mCollision;
    mdata[1].datanb=1;
    mdata[1].hitbox.down.y=14;
    mdata[1].hitbox.down.x=13;
    mdata[1].hitbox.up.y=7;
    mdata[1].hitbox.up.x=13;
    mdata[1].hitbox.left.x=8;
    mdata[1].hitbox.left.y=10;
    mdata[1].hitbox.right.x=18;
    mdata[1].hitbox.right.y=10;
    mdata[1].fxdata[0]=-1;
    mdata[1].fxdata[1]=-1;

//iceorb
    mdata[2].spritedata=5;
    mdata[2].ai=&orbAI;
    mdata[2].vx=0;
    mdata[2].vy=0;
    mdata[2].life=175;
    mdata[2].dommages=20;
    mdata[2].status=S_ALARMED|S_COLD;
    mdata[2].scroll=&oneDirScroll;
    mdata[2].collision=&orbCollision;
    mdata[2].datanb=2;
    mdata[2].hitbox.down.y=8;
    mdata[2].hitbox.down.x=16;
    mdata[2].hitbox.up.y=8;
    mdata[2].hitbox.up.x=0;
    mdata[2].hitbox.left.x=0;
    mdata[2].hitbox.left.y=8;
    mdata[2].hitbox.right.x=16;
    mdata[2].hitbox.right.y=8;
    mdata[2].fxdata[0]=-1;
    mdata[2].fxdata[1]=-1;
    mdata[2].variables=85;

//fire
    mdata[3].spritedata=7;
    mdata[3].ai=&fireAI;
    mdata[3].vx=0;
    mdata[3].vy=0;
    mdata[3].life=500;
    mdata[3].status=S_ALARMED;
    mdata[3].dommages=1;
    mdata[3].scroll=&missilescroll;
    mdata[3].collision=&orbCollision;
    mdata[3].datanb=3;
    mdata[3].hitbox.down.y=67;
    mdata[3].hitbox.down.x=16;
    mdata[3].hitbox.up.y=60;
    mdata[3].hitbox.up.x=16;
    mdata[3].hitbox.left.x=0;
    mdata[3].hitbox.left.y=64;
    mdata[3].hitbox.right.x=32;
    mdata[3].hitbox.right.y=64;
    mdata[3].fxdata[0]=-1;
    mdata[3].fxdata[1]=-1;
    mdata[3].variables=85;

//hydra
    mdata[4].spritedata=9;
    mdata[4].ai=&hydraAI;
    mdata[4].vx=0;
    mdata[4].vy=0;
    mdata[4].life=500;
    mdata[4].status=S_ALARMED;
    mdata[4].dommages=1;
    mdata[4].scroll=&objectscroll;
    mdata[4].collision=&orbCollision;
    mdata[4].datanb=4;
    mdata[4].hitbox.down.y=36;
    mdata[4].hitbox.down.x=23;
    mdata[4].hitbox.up.y=15;
    mdata[4].hitbox.up.x=23;
    mdata[4].hitbox.left.x=19;
    mdata[4].hitbox.left.y=20;
    mdata[4].hitbox.right.x=27;
    mdata[4].hitbox.right.y=20;
    mdata[4].fxdata[0]=2;
    mdata[4].fxdata[1]=-1;
    mdata[4].variables=85;

    //chargedbolt
    mdata[5].spritedata=14;
    mdata[5].ai=&chargedboltAI;
    mdata[5].vx=0;
    mdata[5].vy=0;
    mdata[5].life=256;
    mdata[5].status=S_ALARMED;
    mdata[5].dommages=26;
    mdata[5].scroll=&oneDirScroll;
    mdata[5].collision=&mCollision;
    mdata[5].datanb=5;
    mdata[5].hitbox.down.y=15;
    mdata[5].hitbox.down.x=9;
    mdata[5].hitbox.up.y=3;
    mdata[5].hitbox.up.x=9;
    mdata[5].hitbox.left.x=3;
    mdata[5].hitbox.left.y=9;
    mdata[5].hitbox.right.x=15;
    mdata[5].hitbox.right.y=9;
    mdata[5].fxdata[0]=-1;
    mdata[5].fxdata[1]=-1;

    for(i=0; i<MAX_MDATA; i++)
    {
        mdata[i].hitbox.middle.x=mdata[i].hitbox.down.x;
        mdata[i].hitbox.middle.y=mdata[i].hitbox.left.y;
    }

//Effects
    fxdata[0].spritedata=2;
    fxdata[0].x=7;
    fxdata[0].y=-10;
    fxdata[0].hitbox.right.x=96;
    fxdata[0].hitbox.left.x=0;
    fxdata[0].hitbox.up.y=2;
    fxdata[0].hitbox.down.y=66;
    fxdata[0].flippedh=0;
    fxdata[0].scroll=&FXscroll;

    fxdata[1].spritedata=2;
    fxdata[1].x=-80;
    fxdata[1].y=-10;
    fxdata[1].hitbox.right.x=96;
    fxdata[1].hitbox.left.x=0;
    fxdata[1].hitbox.up.y=2;
    fxdata[1].hitbox.down.y=66;
    fxdata[1].flippedh=1;
    fxdata[1].scroll=&FXscroll;

    fxdata[2].spritedata=8;
    fxdata[2].x=8;
    fxdata[2].y=13;
    fxdata[2].hitbox.right.x=24;
    fxdata[2].hitbox.left.x=0;
    fxdata[2].hitbox.up.y=3;
    fxdata[2].hitbox.down.y=30;
    fxdata[2].flippedh=0;
    fxdata[2].scroll=&FXscroll;
//tree
    fxdata[3].spritedata=10;
    fxdata[3].x=49;
    fxdata[3].y=0;
    fxdata[3].hitbox.right.x=50;
    fxdata[3].hitbox.left.x=0;
    fxdata[3].hitbox.up.y=0;
    fxdata[3].hitbox.down.y=107;
    fxdata[3].flippedh=1;
    fxdata[3].scroll=&FXscroll;

    fxdata[4].spritedata=10;
    fxdata[4].x=0;
    fxdata[4].y=0;
    fxdata[4].hitbox.right.x=50;
    fxdata[4].hitbox.left.x=0;
    fxdata[4].hitbox.up.y=0;
    fxdata[4].hitbox.down.y=107;
    fxdata[4].flippedh=0;
    fxdata[4].scroll=&FXscroll;

//fences
    fxdata[5].spritedata=11;
    fxdata[5].x=0;
    fxdata[5].y=0;
    fxdata[5].hitbox.right.x=16;
    fxdata[5].hitbox.left.x=0;
    fxdata[5].hitbox.up.y=0;
    fxdata[5].hitbox.down.y=85;
    fxdata[5].flippedh=0;
    fxdata[5].scroll=&FXscroll;

    fxdata[6].spritedata=11;
    fxdata[6].x=16;
    fxdata[6].y=0;
    fxdata[6].hitbox.right.x=16;
    fxdata[6].hitbox.left.x=0;
    fxdata[6].hitbox.up.y=0;
    fxdata[6].hitbox.down.y=85;
    fxdata[6].flippedh=0;
    fxdata[6].scroll=&FXscroll;

//wpfires
    fxdata[7].spritedata=13;
    fxdata[7].x=0;
    fxdata[7].y=0;
    fxdata[7].hitbox.right.x=10;
    fxdata[7].hitbox.left.x=0;
    fxdata[7].hitbox.up.y=0;
    fxdata[7].hitbox.down.y=18;
    fxdata[7].flippedh=0;
    fxdata[7].scroll=&FXscroll;

    fxdata[8].spritedata=13;
    fxdata[8].x=64;
    fxdata[8].y=0;
    fxdata[8].hitbox.right.x=10;
    fxdata[8].hitbox.left.x=0;
    fxdata[8].hitbox.up.y=0;
    fxdata[8].hitbox.down.y=18;
    fxdata[8].flippedh=1;
    fxdata[8].scroll=&FXscroll;

    for(i=0; i < MAX_FXDATA; i++)
    {
        fxdata[i].hitbox.middle.x=fxdata[i].hitbox.down.x;
        fxdata[i].hitbox.middle.y=fxdata[i].hitbox.left.y;
    }


}
void deleteobject(s16 ID)
{
    objects[ID].action=-1;
    objects[ID].status=0;
    if( objects[ID].sprite != -1)
    {
        myulDeleteSprite(objects[ID].sprite);
        objects[ID].sprite=-1;
    }
    if (objects[ID].fx[0]!=-1) deleteFX(objects[ID].fx[0]);
    objects[ID].fx[0]=-1;
    if (objects[ID].fx[1]!=-1) deleteFX(objects[ID].fx[1]);
    objects[ID].fx[1]=-1;
    objectused[ID]=0;
}

void deletemissile(s16 ID)
{
    missiles[ID].action=-1;
    missiles[ID].status=0;
    if( missiles[ID].sprite != -1)
    {
        myulDeleteSprite(missiles[ID].sprite);
        missiles[ID].sprite=-1;
    }
    if (missiles[ID].fx[0]!=-1) deleteFX(missiles[ID].fx[0]);
    missiles[ID].fx[0]=-1;
    if (missiles[ID].fx[1]!=-1) deleteFX(missiles[ID].fx[1]);
    missiles[ID].fx[1]=-1;
    missileused[ID]=0;
}

void newObject(s32 x, s32 y, objectinfo* object,s16 ID, objectdata* data)
{
    if ( ID > -1)
    {
        object->spritedata=data->spritedata;
        if( object->sprite != -1)
        {
            myulDeleteSprite(object->sprite);
            object->sprite=-1;
        }
        object->ai=data->ai;
        object->hitbox=data->hitbox;
        object->x=norm_fix(x-object->hitbox.down.x);
        object->y=norm_fix(y-object->hitbox.down.y);

        object->vx=data->vx;
        object->vy=data->vy;
        object->color=RGB15(31,31,31);
        object->action=0;
        object->lastaction=-1;
        object->dir=0;
        object->life=data->life;
        object->dommages=data->dommages;
        object->sprite=-1;
        object->scroll=data->scroll;

        object->collision=data->collision;
        object->variables=data->variables;
        object->datanb=data->datanb;
        object->arrayID=ID;

        if (data->fxdata[0] != -1)
        {
            object->fx[0]=createFX(data->fxdata[0]);
            if (data->fxdata[1] != -1)
            {
                object->fx[1]=createFX(data->fxdata[1]);
            }
        }
        object->action=0;
        (object->scroll)(object);
        object->lastaction=0;
    }
}

s16 getUnusedObject(void)
{
    int i;
    for(i=0; i<MAX_OBJECT; i++)
    {
        if(objectused[i]==0)
        {
            objectused[i]=1;
            return i;
        }
    }
    return -1;
}

void SpawnObjects()
{
    int i,j,k,objectnb;
    //spawns objects with tile
    for (i=0; i < MAX_DATA; i++)
    {
        for (j=0; j<MAPSIZE_X; j++)
        {
            for (k=0; k<MAPSIZE_Y; k++)
            {
                if (data[i].tile)
                {
                    if(data[i].tile==GetTile(j<<3,k<<3))
                    {
                        objectnb=getUnusedObject();
                        newObject((j<<3)+4, (k<<3)+8, &objects[objectnb],objectnb, &data[i] );
                    }
                }
            }
        }
    }

    for (i=0; i < MAX_BGDATA; i++)
    {
        for (j=0; j<MAPSIZE_X; j++)
        {
            for (k=0; k<MAPSIZE_Y; k++)
            {
                if (bgdata[i].tile)
                {
                    if(bgdata[i].tile==GetTile(j<<3,k<<3))
                    {
                        objectnb=getUnusedBgObject();
                        newObject((j<<3)+4, (k<<3)+8, &bgobjects[objectnb],objectnb, &bgdata[i] );
                    }
                }
            }
        }
    }
}

void UpdateObjects()
{
    int i;
    for(i=0; i<MAX_OBJECT; i++)
    {
        //scroll all the objects
        if(objects[i].action > -1)
        {

            (objects[i].scroll)(&objects[i]);
            if(objects[i].sprite!=-1  ||  fxinfo[objects[i].fx[0]].sprite!=-1  ||  fxinfo[objects[i].fx[1]].sprite!=-1)
            {
                (objects[i].ai)(&objects[i]);
            }

        }
    }

for(i=0; i<MAX_BGOBJECT; i++)
    {
        //scroll all the objects
        if(bgobjects[i].action > -1)
        {

            (bgobjects[i].scroll)(&bgobjects[i]);
            if(bgobjects[i].sprite!=-1  ||  fxinfo[bgobjects[i].fx[0]].sprite!=-1  ||  fxinfo[bgobjects[i].fx[1]].sprite!=-1)
            {
                (bgobjects[i].ai)(&bgobjects[i]);
            }

        }
    }


    for(i=0; i<MAX_MISSILE; i++)
    {
        //scroll all the missiles
        if(missiles[i].action > -1)
        {
            (missiles[i].scroll)(&missiles[i]);
            (missiles[i].ai)(&missiles[i]);
        }
    }
}

void newMissile(s32 x, s32 y, objectinfo* object,s16 ID, s16 angle, s16 vx, s16 vy ,int dommages, objectdata* data )//change
{
    if ( ID > -1)
    {
        object->spritedata=data->spritedata;
//	object->pallete=data->pallete;
//	object->sizex=data->sizex;
//	object->sizey=data->sizey;
        if( object->sprite != -1)
        {
            myulDeleteSprite(object->sprite);
            object->sprite=-1;
        }
        object->ai=data->ai;
        object->hitbox=data->hitbox;
        object->x=norm_fix(x-object->hitbox.down.x);
        object->y=norm_fix(y-object->hitbox.down.y);

        object->vx=vx;
        object->vy=vy;
        object->angle=angle;
        object->dir=mangle_dir(angle);
        object->life=data->life;
        object->dommages=dommages;
        object->status=data->status;
        object->sprite=-1;
        object->scroll=data->scroll;

        object->collision=data->collision;
        object->variables=data->variables;
        object->datanb=data->datanb;
        object->arrayID=ID;
        if (data->fxdata[0] != -1)
        {
            object->fx[0]=createFX(data->fxdata[0]);
            if (data->fxdata[1] != -1)
            {
                object->fx[1]=createFX(data->fxdata[1]);
            }
        }
        object->action=0;
        //(object->scroll)(object);
    }
}

s16 getUnusedMissile(void)
{
    int i=0;
    for(i=0; i<MAX_MISSILE; i++)
    {
        if(missileused[i]==0)
        {
            missileused[i]=1;
            return i;
        }
    }
    return -1;
}




s16 getUnusedFX(void)
{
    int i;
    for(i=0; i<MAX_FX; i++)
    {
        if(fxinfo[i].used==0)
        {
            fxinfo[i].used=1;
            return i;
        }
    }
    return -1;
}




s8 createFX (s8 datanb)
{
    int nb=getUnusedFX();
    if (nb != -1)
    {
        fxinfo[nb].scroll=fxdata[datanb].scroll;
        fxinfo[nb].sprite=-1;
        fxinfo[nb].spritedata=fxdata[datanb].spritedata; //numero data sprite
        fxinfo[nb].flippedh=fxdata[datanb].flippedh;
        fxinfo[nb].flippedv=fxdata[datanb].flippedv;
        fxinfo[nb].x=fxdata[datanb].x;
        fxinfo[nb].y=fxdata[datanb].y;
        //fxinfo[nb].used=1;//deja mis à la valeur 1 dans getUnusedFX
        fxinfo[nb].hitbox=fxdata[datanb].hitbox;//copie du pointeur de structure data->info
        return nb;
    }
    else return -1;
}


inline void deleteFX (s8 fx)
{
    if (fxinfo[fx].sprite!=-1) myulDeleteSprite(fxinfo[fx].sprite);
    fxinfo[fx].used=0;
}


/////////WIP////////////

void MobDeath(objectinfo* mob,int time)
{
    hero.stats.experience+=mob->exp;
    if (data[mob->datanb].deathspritedata!=255)//-1=255because deathspritedata is u8
    {
        mob->action=0;
        if( mob->sprite != -1)
        {
            myulDeleteSprite(mob->sprite);
            mob->sprite=-1;
        }
        if (mob->fx[0]!=-1) deleteFX(mob->fx[0]);
        mob->fx[0]=-1;
        if (mob->fx[1]!=-1) deleteFX(mob->fx[1]);
        mob->fx[1]=-1;
        mob->ai=&deadMob;
        mob->spritedata=data[mob->datanb].deathspritedata;
        mob->scroll=&oneDirScroll;
        mob->variables=time;
        //play sound?
    }
    else deleteobject(mob->arrayID);
}



void deadMob(objectinfo* mob)
{
    mob->variables--;
    if (!mob->variables) deleteobject( mob->arrayID);
}
/////////WIP////////////




void blazeAura (aurainfo* aura)
{
    if (!(aura->life&15))
    {
        int objectnb=getUnusedMissile();
        newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+hero.hitbox.down.y, &missiles[objectnb],objectnb,384,0,0,mdata[3].dommages, &mdata[3] );
    }
    aura->life-=1;
//if(aura->life){}
}
