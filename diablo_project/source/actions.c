#include "actions.h"
#include "Sor_Ineedmana.h"

u8 skillsLevels[SKILLNUMBER];
u8 currentSkill[2];
u8 skillpoints=2;
int lvlupicon=-1;
int lvlUpIcnPressed=0;
void CheckForLevelUp()
{
    if (hero.stats.nextlvl<=hero.stats.experience)
    {
        hero.stats.nextlvl=hero.stats.nextlvl*(2.5/hero.stats.lvl)+hero.stats.nextlvl*.99; //curve is not that bad
        hero.stats.lvl++;
        skillpoints++;
        PA_OutputText(1,20,1,"             ");
        if(hero.stats.lvl<10)PA_SetSpriteAnim(1, 0, hero.stats.lvl);
        else if (hero.stats.lvl==10)
        {
            PA_CreateSprite(1,5,(void*)lvlfont_Sprite,OBJ_SIZE_32X32,1,0,	25, 0);
            PA_SetSpriteXY(1,0,12,0);
            PA_SetSpriteAnim(1, 0, 1);
            PA_SetSpriteAnim(1, 5, 0);
        }
        else
        {
            PA_SetSpriteAnim(1, 0, hero.stats.lvl/10);
            PA_SetSpriteAnim(1, 5, hero.stats.lvl%10);
        }
        PA_OutputText(1,20,1,"Next %d",hero.stats.nextlvl);
    }
    if (skillpoints)
    {
        if (lvlupicon==-1) lvlupicon=myulCreateSprite(18,224,160,500);
        if (Stylus.Held)
        {
            if(Stylus.X>224&&Stylus.X<248&&Stylus.Y>160&&Stylus.Y<188&&(Stylus.Newpress||(lvlUpIcnPressed)))
            {
                lvlUpIcnPressed++;
                myulSetAnim (lvlupicon,1,1,0,0);
            }
            else{myulSetAnim (lvlupicon,0,0,0,0); lvlUpIcnPressed=0;}
        }
        else if (Stylus.Released)
        {
            if(Stylus.X>224&&Stylus.X<248&&Stylus.Y>160&&Stylus.Y<188&&lvlUpIcnPressed>3)
            {
            skillmenu(1);
            if (!skillpoints)
            {
                myulDeleteSprite(lvlupicon);
                lvlupicon=-1;
            }
            }
            lvlUpIcnPressed=0;
            myulSetAnim (lvlupicon,0,0,0,0);
        }

    }
}

void Sort(int X,int Y)
{
    if(cout_sort[Pad.Held.L] <=hero.stats.mana_restante )
    {
        hero.skillperiod=60;
        hero.cooldown=200;
        u16 angle = PA_GetAngle(CHARMID_X,CHARMID_Y, X,Y);
        hero.direction=angle_dir(angle);
        hero.action=3;


        sortchoisi[Pad.Held.L] (X,Y,angle,skillsLevels[currentSkill[Pad.Held.L]]);
        hero.stats.mana_restante -= cout_sort[Pad.Held.L];

        myulStartAnim (hero.sprite, 0, spritedatabase[0].nbframe,hero.skillperiod/spritedatabase[0].nbframe,1);//framerate according to skill period to match animation time

    }
    else AS_SoundDirectPlay(0,SOUND(Sor_Ineedmana));//AS_SoundQuickPlay((u8*)Sor_Ineedmana);
}

void nospell (int a, int b, u16 c,u8 d) {}

///firebolt///
#include "firebolt1.h"
void firebolt (int x,int y,u16 angle,u8 level)
{
    int nb=getUnusedMissile();
    newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle)<<1,(-PA_Sin(angle))<<1,mdata[0].dommages, &mdata[0] );
    AS_SoundQuickPlay((u8*)firebolt1);
}

void icebolt (int x,int y,u16 angle,u8 level)
{
    int nb=getUnusedMissile();
    newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,1.5*PA_Cos(angle),1.5*(-PA_Sin(angle)),mdata[1].dommages, &mdata[1] );
}

void chargedbolt (int x,int y,u16 angle,u8 level)
{
    int dommages=mdata[5].dommages+level>>1 nb=getUnusedMissile();

    if (level>2)
{
    newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),dommages, &mdata[5] );
    angle+=30;  nb=getUnusedMissile();  newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),dommages, &mdata[5] );
    angle-=60;  nb=getUnusedMissile();  newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),dommages, &mdata[5] );
    angle-=20;  nb=getUnusedMissile();  newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),dommages, &mdata[5] );
    angle+=100; nb=getUnusedMissile();  newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),dommages, &mdata[5] );
}
else
{
    newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),dommages, &mdata[5] );
    angle+=40; nb=getUnusedMissile(); newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),dommages, &mdata[5] );
    angle-=80; nb=getUnusedMissile(); newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),dommages, &mdata[5] );

}
}

void iceorb (int x,int y,u16 angle,u8 level)
{
    int nb=getUnusedMissile();
    newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),mdata[2].dommages, &mdata[2] );
}

void blaze (int x,int y,u16 angle,u8 level)
{
    auras[0].life=1000;
}

void firewall (int x,int y,u16 angle,u8 level)
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

void hydra (int x,int y,u16 angle,u8 level)
{
    int nb=getUnusedMissile();
    newMissile(fix_norm(hero.x)+hero.hitbox.down.x+x-CAMERA_X-10, fix_norm(hero.y)+15+y-CAMERA_Y, &missiles[nb],nb,384,0,0,mdata[4].dommages, &mdata[4] );
    missiles[nb].variables=0;
    nb=getUnusedMissile();
    newMissile(fix_norm(hero.x)+hero.hitbox.down.x+x-CAMERA_X-20, fix_norm(hero.y)+y-CAMERA_Y, &missiles[nb],nb,213,0,0,mdata[4].dommages, &mdata[4] );
    missiles[nb].variables=20;
    nb=getUnusedMissile();
    newMissile(fix_norm(hero.x)+hero.hitbox.down.x+x-CAMERA_X+2, fix_norm(hero.y)+y-CAMERA_Y, &missiles[nb],nb,43,0,0,mdata[4].dommages, &mdata[4] );
    missiles[nb].variables=40;
}

///Teleport///
#include "teleport1.h"
void teleport(int x,int y,u16 angle,u8 level)
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
