#include "actions.h"
#include "sound.h"
#include "maps/waypoint.h"
u8 skillsLevels[SKILLNUMBER];
int skilldmg[SKILLNUMBER][2];
u8 currentSkill[2];
u8 skillpoints=1;
int lvlupicon=-1;
int lvlUpIcnPressed=0;
int MonBaseLife=1600;

void CheckForLevelUp()
{
    if (hero.stats.nextlvl<=hero.stats.experience)
    {
        hero.stats.nextlvl=hero.stats.nextlvl*(2.5/hero.stats.lvl)+hero.stats.nextlvl*.99; //curve is not that bad
        hero.stats.lvl++;
        hero.stats.vitality++;
        hero.stats.energy++;
        hero.stats.lifeMax=2000+(hero.stats.vitality-10)*500+hero.stats.lifeBonus;
        hero.stats.manaMax=37+2*(hero.stats.energy-35);
        hero.stats.curLife=hero.stats.lifeMax;
        hero.stats.curMana=hero.stats.manaMax;
        skillpoints++;
        MonBaseLife=40*(hero.stats.lvl+1)*(hero.stats.lvl+1)+1000*(hero.stats.lvl+1)-512; //fixed point *512 not 256
        topUpdateLevel();
        topDrawString(20*8,15,"           ");//erase current experience
        topDrawString(7*8,15,"           ");
        topPrintf(81,42,"    ");
        topPrintf(81,66,"    ");
        topPrintf(81,90,"    ");
        topPrintf(81,114,"    ");
        topPrintf(85,42,"%d",hero.stats.strenght);
        topPrintf(85,66,"%d",hero.stats.dexterity);
        topPrintf(85,90,"%d",hero.stats.vitality);
        topPrintf(85,114,"%d",hero.stats.energy);
    }
    if (skillpoints)
    {
        if (lvlupicon==-1) lvlupicon=myulCreateSprite(18,224,160,348);
        if (ul_keys.touch.held)
        {
            if(STYLUSBOX(224,160,24,24) &&(ul_keys.touch.click||(lvlUpIcnPressed)))
            {
                lvlUpIcnPressed++;
                myulSetAnim (lvlupicon,1,1,0,0);
            }
            else
            {
                myulSetAnim (lvlupicon,0,0,0,0);
                lvlUpIcnPressed=0;
            }
        }
        else if (ul_keys.touch.released)
        {
            if(STYLUSBOX(224,160,24,24) &&lvlUpIcnPressed>3)
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
    else if(lvlupicon!=-1)
    {
        myulDeleteSprite(lvlupicon);
        lvlupicon=-1;
    }
}

void Sort(int X,int Y)
{
    if(skillCost[ul_keys.held.L] <=hero.stats.curMana && !lvlUpIcnPressed)
    {
        hero.skillperiod=50;
        hero.cooldown=200;
        u16 angle = PA_GetAngle(CHARMID_X,CHARMID_Y, X,Y);
        hero.direction=angle_dir(angle);
        hero.action=3;


        selectedSkill[ul_keys.held.L] (X,Y,angle,skillsLevels[currentSkill[ul_keys.held.L]]);
        hero.stats.curMana -= skillCost[ul_keys.held.L];

        myulStartAnim (hero.sprite, 0, spritedatabase[0].nbframe,hero.skillperiod/spritedatabase[0].nbframe,1);//framerate according to skill period to match animation time

    }
    else if(!lvlUpIcnPressed&& Counter[TALKING]>60){CounterStart(TALKING); playSound(SFX_SOR_INEEDMANA);}
}
void updateAuras()
{
    int i;
            for(i=0; i<MAX_AURAS; i++)
            {
                if(auras[i].life>0) auras[i].fonction(&auras[i]);
            }
}

void nospell (int a, int b, u16 c,u8 d) {}

///firebolt///
void firebolt (int x,int y,u16 angle,u8 level)
{
    int nb=getUnusedMissile(), dommages=PA_RandMinMax(skilldmg[currentSkill[ul_keys.held.L]][0],skilldmg[currentSkill[ul_keys.held.L]][1]);
    newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle)*3,(-PA_Sin(angle))*3,dommages, &mdata[0] );
    playSound(SFX_FIREBOLT1);
    playSound(SFX_FIRECAST);
}

void icebolt (int x,int y,u16 angle,u8 level)
{
    playSound(SFX_COLDCAST);
    int nb=getUnusedMissile(), dommages=PA_RandMinMax(skilldmg[currentSkill[ul_keys.held.L]][0],skilldmg[currentSkill[ul_keys.held.L]][1]);
    newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,1.5*PA_Cos(angle),1.5*(-PA_Sin(angle)),dommages, &mdata[1] );
}

void chargedbolt (int x,int y,u16 angle,u8 level)
{
    playSound(SFX_CHARGEDBOLT1);
    int dommages=PA_RandMinMax(skilldmg[currentSkill[ul_keys.held.L]][0],skilldmg[currentSkill[ul_keys.held.L]][1]);
    int nb=getUnusedMissile();
    if (level>2)
    {
        newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),dommages, &mdata[5] );
        angle+=30;
        nb=getUnusedMissile();
        newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),dommages, &mdata[5] );
        angle-=60;
        nb=getUnusedMissile();
        newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),dommages, &mdata[5] );
        angle-=20;
        nb=getUnusedMissile();
        newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),dommages, &mdata[5] );
        angle+=100;
        nb=getUnusedMissile();
        newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),dommages, &mdata[5] );
    }
    else
    {
        newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),dommages, &mdata[5] );
        angle+=40;
        nb=getUnusedMissile();
        newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),dommages, &mdata[5] );
        angle-=80;
        nb=getUnusedMissile();
        newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),dommages, &mdata[5] );

    }
}

void iceorb (int x,int y,u16 angle,u8 level)
{
    int nb=getUnusedMissile(), dommages=PA_RandMinMax(skilldmg[currentSkill[ul_keys.held.L]][0],skilldmg[currentSkill[ul_keys.held.L]][1]);
    playSound(SFX_COLDCAST);
    newMissile(fix_norm(hero.x)+hero.hitbox.down.x, fix_norm(hero.y)+30, &missiles[nb],nb,angle,PA_Cos(angle),-PA_Sin(angle),dommages, &mdata[2] );
}

void blaze (int x,int y,u16 angle,u8 level)
{
    int dommages=PA_RandMinMax(skilldmg[currentSkill[ul_keys.held.L]][0],skilldmg[currentSkill[ul_keys.held.L]][1]);
    auras[0].life=1000;
    auras[0].variable=dommages;
    playSound(SFX_FIRECAST);
}

void firewall (int x,int y,u16 angle,u8 level)
{
    playSound(SFX_FIRECAST);
    x+=fix_norm(hero.x)-CAMERA_X;
    y+=fix_norm(hero.y)-CAMERA_Y;
    int nb=getUnusedMissile(), dommages=PA_RandMinMax(skilldmg[currentSkill[ul_keys.held.L]][0],skilldmg[currentSkill[ul_keys.held.L]][1]);
    newMissile(x,y, &missiles[nb],nb,384,0,0,dommages, &mdata[3] );
    nb=getUnusedMissile();
    newMissile(x+fix_norm(PA_Sin(angle)*13),y+fix_norm(PA_Cos(angle)*13), &missiles[nb],nb,384,0,0,dommages, &mdata[3] );
    nb=getUnusedMissile();
    newMissile(x-fix_norm(PA_Sin(angle)*13),y-fix_norm(PA_Cos(angle)*13), &missiles[nb],nb,384,0,0,dommages, &mdata[3] );
    nb=getUnusedMissile();
    newMissile(x+fix_norm(PA_Sin(angle)*26),y+fix_norm(PA_Cos(angle)*26), &missiles[nb],nb,384,0,0,dommages, &mdata[3] );
    nb=getUnusedMissile();
    newMissile(x-fix_norm(PA_Sin(angle)*26),y-fix_norm(PA_Cos(angle)*26), &missiles[nb],nb,384,0,0,dommages, &mdata[3] );
    //newMissile(x,y, &missiles[nb],nb,angle,0,0, &mdata[3] );
}

void hydra (int x,int y,u16 angle,u8 level)
{
    playSound(SFX_FIRECAST);
    int nb=getUnusedMissile(), dommages=PA_RandMinMax(skilldmg[currentSkill[ul_keys.held.L]][0],skilldmg[currentSkill[ul_keys.held.L]][1]);
    newMissile(fix_norm(hero.x)+hero.hitbox.down.x+x-CAMERA_X-10, fix_norm(hero.y)+y-CAMERA_Y+7, &missiles[nb],nb,384,0,0,dommages, &mdata[4] );
    missiles[nb].variables=0;
    nb=getUnusedMissile();
    newMissile(fix_norm(hero.x)+hero.hitbox.down.x+x-CAMERA_X, fix_norm(hero.y)+y-CAMERA_Y-8, &missiles[nb],nb,213,0,0,dommages, &mdata[4] );
    missiles[nb].variables=20;
    nb=getUnusedMissile();
    newMissile(fix_norm(hero.x)+hero.hitbox.down.x+x-CAMERA_X-20, fix_norm(hero.y)+y-CAMERA_Y-8, &missiles[nb],nb,43,0,0,dommages, &mdata[4] );
    missiles[nb].variables=40;
}

///Teleport///
void teleport(int x,int y,u16 angle,u8 level)
{
    x-=CHARFEET_X;
    y-=CHARFEET_Y;
    playSound(SFX_TELEPORT);
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
