#include "actions.h"






void Sort(int X,int Y)
{
    if(cout_sort[Pad.Held.L] <=hero.stats.mana_restante )
    {
        hero.skillperiod=60;
        hero.cooldown=200;
        u16 angle = PA_GetAngle(CHARMID_X,CHARMID_Y, X,Y);
        hero.direction=angle_dir(angle);
        hero.action=3;


        sortchoisi[Pad.Held.L] (X,Y,angle);
        hero.stats.mana_restante -= cout_sort[Pad.Held.L];

        myulStartAnim (hero.sprite, 0, spritedatabase[0].nbframe,hero.skillperiod/spritedatabase[0].nbframe);//framerate according to skill period to match animation time

    }
}

void nospell (int a, int b, u16 c) {}

///firebolt///
#include "firebolt1.h"
void firebolt (int x,int y,u16 angle)
{
    int nb=getUnusedMissile();
    newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle)<<1,(-PA_Sin(angle))<<1,mdata[0].dommages, &mdata[0] );
    AS_SoundQuickPlay((u8*)firebolt1);
}

void icebolt (int x,int y,u16 angle)
{
    int nb=getUnusedMissile();
    newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,1.5*PA_Cos(angle),1.5*(-PA_Sin(angle)),mdata[1].dommages, &mdata[1] );
}

void chargedbolt (int x,int y,u16 angle)
{
    int nb=getUnusedMissile();
    newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),mdata[5].dommages, &mdata[5] );
    nb=getUnusedMissile();
    angle+=40;
    newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),mdata[5].dommages, &mdata[5] );
    nb=getUnusedMissile();
    angle-=80;
    newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),mdata[5].dommages, &mdata[5] );
}

void iceorb (int x,int y,u16 angle)
{
    int nb=getUnusedMissile();
    newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),mdata[2].dommages, &mdata[2] );
}

void blaze (int x,int y,u16 angle)
{
    auras[0].life=1000;
}

void firewall (int x,int y,u16 angle)
{
    x+=fix_norm(hero.x)-CAMERA_X;
    y+=fix_norm(hero.y)-CAMERA_Y;
    int nb=getUnusedMissile();
    newMissile(x,y, &missiles[nb],nb,384,0,0,mdata[3].dommages, &mdata[3] );
    nb=getUnusedMissile();
    newMissile(x+fix_norm(PA_Sin(angle)*13),y+fix_norm(PA_Cos(angle)*13), &missiles[nb],nb,384,0,0,mdata[3].dommages, &mdata[3] );
    nb=getUnusedMissile();
    newMissile(x-fix_norm(PA_Sin(angle)*13),y-fix_norm(PA_Cos(angle)*13), &missiles[nb],nb,384,0,0,mdata[3].dommages, &mdata[3] );
    nb=getUnusedMissile();
    newMissile(x+fix_norm(PA_Sin(angle)*26),y+fix_norm(PA_Cos(angle)*26), &missiles[nb],nb,384,0,0,mdata[3].dommages, &mdata[3] );
    nb=getUnusedMissile();
    newMissile(x-fix_norm(PA_Sin(angle)*26),y-fix_norm(PA_Cos(angle)*26), &missiles[nb],nb,384,0,0,mdata[3].dommages, &mdata[3] );
    //newMissile(x,y, &missiles[nb],nb,angle,0,0, &mdata[3] );
}

void hydra (int x,int y,u16 angle)
{
    int nb=getUnusedMissile();
    newMissile(fix_norm(hero.x)+hero.hitbox.down.x+x-CAMERA_X-10, fix_norm(hero.y)+15+y-CAMERA_Y, &missiles[nb],nb,384,0,0,mdata[4].dommages, &mdata[4] );
    nb=getUnusedMissile();
    newMissile(fix_norm(hero.x)+hero.hitbox.down.x+x-CAMERA_X-20, fix_norm(hero.y)+y-CAMERA_Y, &missiles[nb],nb,213,0,0,mdata[4].dommages, &mdata[4] );
    nb=getUnusedMissile();
    newMissile(fix_norm(hero.x)+hero.hitbox.down.x+x-CAMERA_X+2, fix_norm(hero.y)+y-CAMERA_Y, &missiles[nb],nb,43,0,0,mdata[4].dommages, &mdata[4] );
}

///Teleport///
#include "teleport1.h"
void teleport(int x,int y,u16 angle)
{
    x-=CHARFEET_X;
    y-=CHARFEET_Y;
    AS_SoundQuickPlay((u8*)teleport1);
    int j,k;

    if(anytelecollision(hero.hitbox,x,y))
    {
        //check if theres a near point to teleport
        for (j=x-20; j<x+20; j+=8)
        {
            for (k=y-20; k<y+20; k+=8)
            {

                if (!anytelecollision(hero.hitbox,j,k))
                {
                    hero.x+=norm_fix(j);
                    hero.y+=norm_fix(k);
                    j=x+16;
                    k=y+16;
                }
            }
        }
        x=0;
        y=0;
    }

    hero.x+=norm_fix(x);
    hero.y+=norm_fix(y);
}
