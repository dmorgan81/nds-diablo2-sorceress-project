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
int curMaxObject,curMaxBgObject,curMaxMissile;    //small trick to avoid long browsing in arrays for nothing,
//becoming useless when a lot of objects are create and then deleted because the value will not be
//decreased, would need to browse the arrays again, and then it would be useless
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
        objects[i].color=0x7fff;
    }
    for(i=0; i<MAX_FX; i++)
    {
        fxinfo[i].used=0;
        fxinfo[i].sprite=-1;
    }

#include "objects/objectsdata.txt"  //Really, hm, shouldnt do this beacuse its risked but it make the file less fat.
    //all data in txt file to avoid overload of the c file
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
        missiles[i].color=0x7ffff;
    }

#include "objects/missilesdata.txt" //all data in txt file to avoid overload of the c file
    for(i=0; i<MAX_MDATA; i++)
    {
        mdata[i].hitbox.middle.x=mdata[i].hitbox.down.x;
        mdata[i].hitbox.middle.y=mdata[i].hitbox.left.y;
    }

//Effects

#include "objects/fxdata.txt"       //all data in txt file to avoid overload of the c file

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
    if (ID==curMaxObject)curMaxObject--;
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
    if (ID==curMaxMissile)curMaxMissile--;
}

void newObject(s32 x, s32 y, objectinfo* object,s16 ID, objectdata* data,bool array)
{
    if ( ID != -1)
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
        object->color=0x7fff;
        object->action=0;
        object->lastaction=-1;
        object->dir=0;
        object->life=data->life;
        object->exp=data->exp;
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
        if (!array)
        {
            if (ID>curMaxObject)curMaxObject=ID;
        }
        else if (ID>curMaxBgObject)curMaxBgObject=ID;
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
                        newObject((j<<3)+4, (k<<3)+8, &objects[objectnb],objectnb, &data[i],0 );
                    }
                }
            }
        }
    }

    //curMaxObject=objectnb; // we know that the last object created has the highest rank in the array
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
                        newObject((j<<3)+4, (k<<3)+8, &bgobjects[objectnb],objectnb, &bgdata[i] ,1);
                    }
                }
            }
        }
    }
    //curMaxBgObject=objectnb; //same here
}

void UpdateObjects()
{
    int i;
    for(i=0; i<=curMaxObject; i++)//MAX_OBJECT; i++)
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

    for(i=0; i<=curMaxBgObject; i++)
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


    for(i=0; i<=curMaxMissile; i++)
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
        if (ID>curMaxMissile)curMaxMissile=ID;
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




s16 createFX (s16 datanb)
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


inline void deleteFX (s16 fx)
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
        mob->scroll=&deadScroll;
        if((fix_norm(mob->x-hero.x)+mob->hitbox.left.x<=256-CAMERA_X && fix_norm(mob->x-hero.x)+mob->hitbox.right.x >=-CAMERA_X)&&(fix_norm(mob->y-hero.y)+mob->hitbox.up.y<=192-CAMERA_Y && fix_norm(mob->y-hero.y)+mob->hitbox.down.y>=-CAMERA_Y))
        {
            mob->sprite=myulCreateSprite(mob->spritedata, fix_norm(mob->x-hero.x)+CAMERA_X, fix_norm(mob->y-hero.y)+CAMERA_Y,fix_norm(mob->y-hero.y)+CAMERA_Y+mob->hitbox.down.y);
            myulImageColumn (mob->sprite,0);
            myulImageFlip(mob->sprite,0,0);
            myulmyulSetSpritePrio(mob->sprite,myulGetSpriteY(mob->sprite)+mob->hitbox.down.y);
        }
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
