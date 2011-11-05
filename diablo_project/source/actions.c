#include "actions.h"






void Sort(int X,int Y)
{
    if(cout_sort[Pad.Held.L] <=sorc.stats.mana_restante )
    {
        sorc.skillperiod=60;
        sorc.cooldown=200;
        u16 angle = PA_GetAngle(CHARMID_X,CHARMID_Y, X,Y);
        sorc.direction=angle_dir(angle);
        sorc.action=3;


        sortchoisi[Pad.Held.L] (X,Y,angle);
        sorc.stats.mana_restante -= cout_sort[Pad.Held.L];

        myulStartAnim (sorc.sprite, 0, spritedatabase[0].nbframe,sorc.skillperiod/spritedatabase[0].nbframe);//framerate according to skill period to match animation time

    }
}

void nospell (int a, int b, u16 c) {}

///firebolt///
#include "firelaunch1.h"
void firebolt (int x,int y,u16 angle)
{
    int nb=getUnusedMissile();
    newMissile(fix_norm(sorc.x)+sorc.hitbox.down.x, fix_norm(sorc.y)+30, &missiles[nb],nb,angle,PA_Cos(angle)<<1,(-PA_Sin(angle))<<1,mdata[0].dommages, &mdata[0] );
    AS_SoundDefaultPlay((u8*)firelaunch1, (u32)firelaunch1_size, 100, 64, false,0);
}

void icebolt (int x,int y,u16 angle)
{
    int nb=getUnusedMissile();
    newMissile(fix_norm(sorc.x)+sorc.hitbox.down.x, fix_norm(sorc.y)+30, &missiles[nb],nb,angle,1.5*PA_Cos(angle),1.5*(-PA_Sin(angle)),mdata[1].dommages, &mdata[1] );
}

void chargedbolt (int x,int y,u16 angle)
{
    int nb=getUnusedMissile();
    newMissile(fix_norm(sorc.x)+sorc.hitbox.down.x, fix_norm(sorc.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),mdata[5].dommages, &mdata[5] );
    nb=getUnusedMissile();
    angle+=40;
    newMissile(fix_norm(sorc.x)+sorc.hitbox.down.x, fix_norm(sorc.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),mdata[5].dommages, &mdata[5] );
    nb=getUnusedMissile();
    angle-=80;
    newMissile(fix_norm(sorc.x)+sorc.hitbox.down.x, fix_norm(sorc.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),mdata[5].dommages, &mdata[5] );
}

void iceorb (int x,int y,u16 angle)
{
    int nb=getUnusedMissile();
    newMissile(fix_norm(sorc.x)+sorc.hitbox.down.x, fix_norm(sorc.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),mdata[2].dommages, &mdata[2] );
}

void blaze (int x,int y,u16 angle)
{
    auras[0].life=1000;
}

void firewall (int x,int y,u16 angle)
{
    x+=fix_norm(sorc.x)-CAMERA_X;
    y+=fix_norm(sorc.y)-CAMERA_Y;
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
    newMissile(fix_norm(sorc.x)+sorc.hitbox.down.x+x-CAMERA_X-10, fix_norm(sorc.y)+15+y-CAMERA_Y, &missiles[nb],nb,384,0,0,mdata[4].dommages, &mdata[4] );
    nb=getUnusedMissile();
    newMissile(fix_norm(sorc.x)+sorc.hitbox.down.x+x-CAMERA_X-20, fix_norm(sorc.y)+y-CAMERA_Y, &missiles[nb],nb,213,0,0,mdata[4].dommages, &mdata[4] );
    nb=getUnusedMissile();
    newMissile(fix_norm(sorc.x)+sorc.hitbox.down.x+x-CAMERA_X+2, fix_norm(sorc.y)+y-CAMERA_Y, &missiles[nb],nb,43,0,0,mdata[4].dommages, &mdata[4] );
}

///Teleport///
#include "teleport1.h"
void teleport(int x,int y,u16 angle)
{
    x-=CHARFEET_X;
    y-=CHARFEET_Y;
    AS_SoundDefaultPlay((u8*)teleport1, (u32)teleport1_size, 55, 64, false,0);
    int j,k;

    if(anytelecollision(sorc.hitbox,x,y))
    {
        //check if theres a near point to teleport
        for (j=x-20; j<x+20; j+=8)
        {
            for (k=y-20; k<y+20; k+=8)
            {

                if (!anytelecollision(sorc.hitbox,j,k))
                {
                    sorc.x+=norm_fix(j);
                    sorc.y+=norm_fix(k);
                    j=x+16;
                    k=y+16;
                }
            }
        }
        x=0;
        y=0;
    }

    sorc.x+=norm_fix(x);
    sorc.y+=norm_fix(y);
}
