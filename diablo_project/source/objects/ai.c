//////////////////////////////////////////////////
//////////////////////////////////////////////////
////////////Artificial Intelligence///////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
#include "../objects.h"
extern objectdata data[MAX_DATA];
extern objectdata mdata[MAX_MDATA];
extern objectinfo objects[MAX_OBJECT];
extern objectinfo missiles[MAX_MISSILE];
extern fx_data fxdata[MAX_FXDATA];
extern fx_info fxinfo[MAX_FX];
extern aurainfo auras[MAX_AURAS];

extern bool objectused[MAX_OBJECT];
extern bool missileused[MAX_MISSILE];




inline void immortal(objectinfo* object)
{
    object->life = 500000;
}


void bgObjectAi(objectinfo* object)
{
    if (fix_norm(object->y)+object->hitbox.down.y > fix_norm(hero.y)+hero.hitbox.down.y && fix_norm(object->y) < fix_norm(hero.y)+hero.hitbox.down.y)
    {
        SetSpriteAblending (fxinfo[object->fx[0]].sprite,BGOBJ_AB);
        SetSpriteAblending (fxinfo[object->fx[1]].sprite,BGOBJ_AB);

    }
    else
    {
        SetSpriteAblending (fxinfo[object->fx[0]].sprite,31);
        SetSpriteAblending (fxinfo[object->fx[1]].sprite,31);
    }
}


void zombieAI(objectinfo* zombie)
{
    (zombie->collision)(zombie);
    int movangle=PA_GetAngle(fix_norm(zombie->x)+zombie->hitbox.down.x,fix_norm(zombie->y)+zombie->hitbox.down.y,fix_norm(hero.x)+hero.hitbox.down.x,fix_norm(hero.y)+hero.hitbox.down.y);
    zombie->vx=PA_Cos(movangle)>>1;//make total move 0.5px per frame
    zombie->vy=-PA_Sin(movangle)>>1;
    if (zombie->status&S_COLD)
    {
        zombie->color=0x6400;//RGB15(0,0,31);    //set color to blue and make half speed
        zombie->vx>>=1;
        zombie->vy>>=1;
    }

    if(feetcollision(&zombie->hitbox,zombie->x+zombie->vx,zombie->y))
    {
        zombie->vx=0;
    }

    if(feetcollision(&zombie->hitbox,zombie->x,zombie->y+zombie->vy))
    {
        zombie->vy=0;
    }

    zombie->x+=zombie->vx;
    zombie->y+=zombie->vy;

    zombie->dir=angle_dir(movangle);
    if (zombie->life < 1)
    {
        MobDeath(zombie,300);
    }
}
//change
void meleeAI(objectinfo* melee)
{
    (melee->collision)(melee);
    melee->variables=100;
    if (melee->life > 0)
    {
        melee->lastdir=melee->dir;
        melee->lastaction=melee->action;
        int movangle=PA_GetAngle(fix_norm(melee->x)+melee->hitbox.down.x,fix_norm(melee->y)+melee->hitbox.down.y,fix_norm(hero.x)+hero.hitbox.down.x,fix_norm(hero.y)+hero.hitbox.down.y);


        if (!(melee->cd%melee->variables))
        {

            if (PA_Distance(fix_norm(melee->x)+melee->hitbox.down.x,fix_norm(melee->y)+melee->hitbox.down.y,fix_norm(hero.x)+hero.hitbox.down.x,fix_norm(hero.y)+hero.hitbox.down.y)<50)
            {
                //if in front of here, attack him
                melee->action=2;
            }
            else if (PA_Distance(fix_norm(melee->x)+melee->hitbox.down.x,fix_norm(melee->y)+melee->hitbox.down.y,fix_norm(hero.x)+hero.hitbox.down.x,fix_norm(hero.y)+hero.hitbox.down.y)>7000 && !melee->status&S_ALARMED)
            {
                //if too far and not alarmed, dont ignore here
                melee->action=0;
            }

            else if (PA_RandMax(5))
            {
                //follow hero...
                melee->action=1;
            }
            else
            {
                // or stand for few seconds
                melee->action=0;
            }
        }
        switch (melee->action)
        {
        case 0:
            melee->vx=0;
            melee->vy=0;
            break;
        case 1:
            if (PA_Distance(fix_norm(melee->x)+melee->hitbox.down.x,fix_norm(melee->y)+melee->hitbox.down.y,fix_norm(hero.x)+hero.hitbox.down.x,fix_norm(hero.y)+hero.hitbox.down.y)<50)
            {
                melee->action=2;
            }
            melee->vx=PA_Cos(movangle)>>1;
            melee->vy=-PA_Sin(movangle)>>1;
            break;
        case 2:
            melee->vx=0;
            melee->vy=0;
            break;
        }
        melee->update=(melee->lastdir!=melee->dir)||(melee->lastaction!=melee->action);
        if(melee->update)
        {
            myulAnimBegin (melee->sprite);//sprite should always exist, its melee!!!
            melee->update=0;
        }

        //check ground collision
        if(feetcollision(&melee->hitbox,melee->x+melee->vx,melee->y))
        {
            melee->vx=0;
        }

        if(feetcollision(&melee->hitbox,melee->x,melee->y+melee->vy))
        {
            melee->vy=0;
        }
        melee->x+=melee->vx;
        melee->y+=melee->vy;
        melee->cd++;

        melee->dir=angle_dir(movangle);
        if (melee->status&S_COLD)
        {
            melee->color=0x7d86;//set color to blue and make half speed
            melee->vx>>=1;
            melee->vy>>=1;
        }
    }
// TODO (Clement#1#): add damages A FAIRE OBLIGATOIREMENT


    else
    {
        MobDeath(melee,300);
    }

}




void missileAI (objectinfo* missile)
{
    (missile->collision)(missile);
    missile->x += missile->vx;
    missile->y += missile->vy;
    missile->life-=1;
    if (anycollision(VOIDTILE,&missile->hitbox,missile->x-missile->hitbox.down.x,missile->y-missile->hitbox.down.y))
    {
        missile->life=0;
    }




    if (missile->life < 1)
    {
        deletemissile( missile->arrayID);
    }
}

void orbAI(objectinfo* missile)
{
    (missile->collision)(missile);


    missile->x += missile->vx;
    missile->y += missile->vy;
    missile->life-=1;

    if(( missile->life % 5 ) == 0)
    {
        int nb=getUnusedMissile();
        int angle=(missile->angle+missile->variables)&511;
        newMissile(fix_norm(missile->x)+10, fix_norm(missile->y)+16, &missiles[nb],nb,angle,2*PA_Cos(angle),2*(-PA_Sin(angle)),mdata[1].dommages, &mdata[1] );
        missile->variables+=196;

    }
    if (anycollision(VOIDTILE,&missile->hitbox,missile->x-missile->hitbox.down.x,missile->y-missile->hitbox.down.y))
    {
        missile->life=0;
    }



    if (missile->life < 1)
    {
        deletemissile( missile->arrayID);
    }
}

void fireAI(objectinfo* missile)
{
    (missile->collision)(missile);

    missile->life-=1;

    if( missile->life<475)
    {
        myulSetAnim (missile->sprite, 4, 10, 8, 0);

    }
    if (anycollision(VOIDTILE,&missile->hitbox,missile->x-missile->hitbox.down.x,missile->y-missile->hitbox.down.y))
    {
        missile->life=0;
    }



    if (missile->life < 1)
    {
        deletemissile( missile->arrayID);
    }
}

void chargedboltAI (objectinfo* missile)
{
    (missile->collision)(missile);
    missile->x += missile->vx;//+PA_RandMinMax(-100,100);
    missile->y += missile->vy;//+PA_RandMinMax(-100,100);
    missile->life-=1;
    if (anycollision(VOIDTILE,&missile->hitbox,missile->x-missile->hitbox.down.x,missile->y-missile->hitbox.down.y))
    {
        missile->life=0;
    }
    if (missile->life < 1)
    {
        deletemissile( missile->arrayID);
    }
}
void hydraAI(objectinfo* missile)
{
    missile->dir=angle_dir(missile->angle);
    missile->action=1;
    (missile->collision)(missile);
    missile->life-=1;
    missile->variables++;
    if( !(missile->variables&63))
    {
        int i;
        int bestdistance=norm_fix(75);
        int nearestobject=-1;
        for(i=0; i<=curMaxObject; i++)
        {
            if(objects[i].life>0)
            {
                int objdistance=PA_Distance(fix_norm(missile->x)+missile->hitbox.middle.x,fix_norm(missile->y)+missile->hitbox.middle.y,fix_norm(objects[i].x)+objects[i].hitbox.middle.x,fix_norm(objects[i].y)+objects[i].hitbox.middle.y);
                if(objdistance<bestdistance)
                {
                    nearestobject=i;
                    bestdistance=objdistance;
                }
            }
        }
        if (nearestobject!=-1)
        {
            missile->angle=PA_GetAngle(fix_norm(missile->x)+missile->hitbox.up.x,fix_norm(missile->y)+missile->hitbox.up.y,fix_norm(objects[nearestobject].x)+objects[nearestobject].hitbox.middle.x,fix_norm(objects[nearestobject].y)+objects[nearestobject].hitbox.middle.y);
            int nb=getUnusedMissile();
            newMissile(fix_norm(missile->x+PA_Cos(missile->angle)*10)+missile->hitbox.up.x,fix_norm(missile->y)+missile->hitbox.up.y, &missiles[nb],nb,missile->angle,1.5*PA_Cos(missile->angle),1.5*(-PA_Sin(missile->angle)),mdata[0].dommages, &mdata[0] );
        }
        if(missile->life<1) deletemissile(missile->arrayID);
    }
}
