////////////////////////////////////////////
////////////////////////////////////////////
///////////////DIABLO II////////////////////
///////////SORCERESS PROJECT////////////////
////////////////////////////////////////////
////////////////////////////////////////////


//Includes PALib, µLibrary et headers
#include <nds.h>
#include "main.h"
#include "structures.h"
#include "defines.h"
#include "ulScreenDisplay.h"
#include "top_screen.h"
#include "player.h"
#include "actions.h"
#include "objects.h"
#include "objects/collisions.h"
#include "interface.h"
#include "misc.h"
#include "sound.h"
#include "quests.h"
#include "maps/map.h"
#include "maps/waypoint.h"

#ifdef Test
//#define _NOSPLASH_ //quote this line to make splash appear
#endif
#define NOGBA


////////////////////////////////
/////FUNCTIONS DECLARATIONS/////
////////////////////////////////
void setHeroData();
void CallAllInits();
void statsUpdate();
extern bool isEmulator();
////////////////////////////////
/////VARIABLES DECLARATIONS/////
////////////////////////////////
s8 fps = 0; //Our FPS
u8 old_time=0;
bool secondpast=1;
extern charstruct hero;

///////////////////////////////
int bg3_sub;

int main( int argc, char **argv)
{
///////////////////////////////
/////VARIABLES DEFINITIONS/////
///////////////////////////////

    CallAllInits();


    hero.sprite=myulCreateSprite(0,CAMERA_X, CAMERA_Y, CHARFEET_Y);


    auras[0].fonction=&blazeAura;


///////////////////////////
////////Main Start/////////
///////////////////////////
#ifdef MUSIC_ON
//    AS_MP3StreamPlay("tristram.mp3");
#endif

    int i=0;
    Mymap->scrollX=fix_norm(hero.x)-CAMERA_X;
    Mymap->scrollY=fix_norm(hero.y)-CAMERA_Y;
    updateObjects();
#ifdef Test
    s16 x,y;
#endif
    int objectnb=-1;

#ifndef Test
    hero.direction=4;
    movechar();



    if(!hero.stats.experience)
    {
        objectnb=getUnusedObject();
        newObject(80, -40, &objects[objectnb],objectnb, &data[4],0);
        for (i=0; i<280; i++)
        {
            updateObjects();
            objects[objectnb].y+=64;
            sprites[objects[objectnb].sprite].prio=100;
            sprites[objects[objectnb].sprite].prio=100;
            sprites[fxinfo[objects[objectnb].fx[0]].sprite].prio=100;
            sprites[fxinfo[objects[objectnb].fx[1]].sprite].prio=100;
            myulScreenDraws();
            //waitforvbl without key update
            UpdateRTC();
            PA_RunCounters();
            ulSyncFrame();
            ulEndFrame();
        }

        DialogInBox("Welcome to the world of Sanctuary, sorceress.\nAs you may know, this land is, once again, struck by the Three.\n\n\
I am the Archangel Tyrael. I came here to prevent Diablo from freeing his brother, Baal. But I have failed. Now, Terror and Destruction roam free throughout your world.\n\n\
Even now, they head towards the Eastern capital of Kurast - to the very heart of the Zakarum Temple. There they hope to find their eldest brother, Mephisto, the Lord of Hatred who was imprisoned there ages ago.\n\n\
If the three Prime Evils unite, they will be invincible. Though it is unclear as to what their aims are, it is certain that they must be stopped at all costs.\n\n\
I am broken and the energys that tie me to this world are diminishing rapidly.\n\n\
You must take up this quest and prevent the Three Brothers from reuniting. You must cross the sea and search for Diablo and Baal in Kurast.\n\n\
Now hurry, mortal... Time is running out for all of us!\n",15,"tyrael","/Tyr_intro.raw",6*15*8,1);

        skillmenu(1);
    }
#endif

    WaitForVBL();
    CounterStart(VBL);
    while(1)
    {
        while(hero.stats.curLife>0&&hero.stats.curLife<=hero.stats.lifeMax)
        {


            myulSetSpritePrio(hero.sprite,CHARFEET_Y);
            if (!(Counter[VBL]&128))//change
            {
                for (i=0; i<MAX_DATASPRITES; i++)
                {
                    imagesused[i]=0;
                }
            }
            myulScreenDraws();

            if (!(Counter[VBL]&128))
            {
#ifdef Test
                topPrintf(1,8*8,"tex: %d    ",ulGetTexVramAvailMemory());
                topPrintf(1,9*8,"vertex: %d    ",ulGetVertexAvailMemory());
#endif
                if (ulGetTexVramAvailMemory()<10000) //security, use it only when necessary because it make some flashes on real ds if the sprite is used right after
                {
                    for (i=1; i<MAX_DATASPRITES; i++)
                    {
                        if(!imagesused[i])ulUnrealizeImage(spritedatabase[i].image);
                    }
                }
            }
            quickTopScreenRefresh();
            hero.cooldown=0;
            statsUpdate();
            movechar();

#ifdef Test
            objectnb=-1;
            if (ul_keys.held.A)
            {
                objectnb=getUnusedMissile();
                if (objectnb<MAX_MISSILE && objectnb!=-1)
                {

                    x=fix_norm(hero.x)+hero.hitbox.down.x;
                    y=fix_norm(hero.y)+hero.hitbox.right.y;

                    newMissile(x, y, &missiles[objectnb],objectnb,dir_angle(3),256,-256,mdata[0].dommages, &mdata[0] );
                }
            }
#endif



#ifndef NOSPAWN
            mobSpawn();
#endif
            updateAuras();
            updateObjects();
            updateQuests();
            if(ul_keys.pressed.X) saveloadmenu(0);
            if(ul_keys.pressed.Y) saveloadmenu(1);
#ifdef Test
            if(ul_keys.held.B)
            {
                hero.stats.experience+=30;
            }
#endif
            if(SKILLMENU_KEY)	skillmenu(0); //will be changed later, we cant firce player to levelup skills if they just want to switch
            if(PAUSEKEY || ul_keys.held.lid) pause();//(int*)ul_keys.pressed.start);
            //if (ul_keys.held.value& RESETKEYS )exit(0);
            CheckForLevelUp();
            WaitForVBL();
        }
        hero.stats.curLife=10;
        death();
    }

//Fin de la boucle infinie
    return 0;
}
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///////////////////////////Main END//////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////















int ulInitNitroFS();


void setHeroData()
{

/////////////////
/////charvar/////
/////////////////
    selectedSkill[0]=&nospell;
    selectedSkill[1]=&nospell;
    hero.action=0;
    hero.speed=256;
    hero.speed2=181;//multiplie par 181 sois 1.7 en point fixe
    hero.x=norm_fix(128);//80
    hero.y=norm_fix(50);//40

///Hitboxinfos///
    hero.hitbox.left.x=11;
    hero.hitbox.left.y=43;
    hero.hitbox.right.x=20;
    hero.hitbox.right.y=43;
    hero.hitbox.up.x=16;
    hero.hitbox.up.y=40;
    hero.hitbox.down.x=16;
    hero.hitbox.down.y=47;
    hero.hitbox.middle.x=16;
    hero.hitbox.middle.y=43;
///stats///
    hero.stats.strength=10;
    hero.stats.dexterity=25;
    hero.stats.vitality=10;
    hero.stats.energy=35;
    hero.stats.lifeMax=2000+(hero.stats.vitality-10)*500;
    hero.stats.curLife=hero.stats.lifeMax;
    hero.stats.manaMax=35;
    hero.stats.curMana=(hero.stats.manaMax);

    hero.stats.strengthBase=10;
    hero.stats.strengthCoeff=0;
    hero.stats.dexterityBase=25;
    hero.stats.dexterityCoeff=0;
    hero.stats.vitalityBase=10;
    hero.stats.vitalityCoeff=1;
    hero.stats.energyBase=35;
    hero.stats.energyCoeff=1;
    hero.stats.lifeBase=2000;
    hero.stats.lifeCoeff=500;
    hero.stats.manaBase=35;
    hero.stats.manaCoeff=2;
    hero.stats.experience=0;
    hero.stats.nextlvl=400;
    hero.stats.level=1;
}

void CallAllInits()
{
    int i;
    char buffer[30];
    FILE* conf_ini=NULL;

    setHeroData();

    ulInit(UL_INIT_ALL);
    ulInitGfx();
    ulInitText();
    ulSetMainLcd(0);
    videoSetModeSub(MODE_5_2D | DISPLAY_BG3_ACTIVE);
    vramSetBankH(VRAM_H_SUB_BG);
    vramSetBankI(VRAM_I_SUB_BG_0x06208000);
    bg3_sub = bgInitSub(3, BgType_Bmp8, BgSize_B8_256x256, 0,0);
    ulSetTexVramParameters(UL_BANK_A | UL_BANK_B | UL_BANK_C | UL_BANK_D, VRAM_A, 512 << 10); //256ko de vram
    CountersReset();
    if (!ulInitNitroFS())
    {
        while(1)
        {
            ulStartDrawing2D();
            ulDrawTextBox(3,171,253,190,"Filesystem error. Please patch dldi and make sure your flashcart supports argv.",0);
            ulEndDrawing();
            WaitForVBL();
        }
    }

    conf_ini=fopen("/config.ini","rb");
    if(!conf_ini)
    {
        while(1)
        {
            ulStartDrawing2D();
            ulDrawTextBox(3,171,253,190,"Error loading ini file",0);
            ulEndDrawing();
            WaitForVBL();
        }
    }
    initTopScreen();

#ifndef _NOSPLASH_
    //Show splash screens, uLibrary, Project...
    MySplash();

    UL_IMAGE* loadingimg = ulLoadImageFilePNG("/gfx/loading_png.png",0, UL_IN_RAM, UL_PF_PAL8);
    loadingimg->x=32;
    //loading frame 0
    ulSetImageTileSize (loadingimg, 0, 0, 192, 192);
    ulStartDrawing2D();
    ulDrawImage(loadingimg);
    ulEndDrawing();
#endif

#ifndef _NOSPLASH_
    //loading frame 1
    ulSetImageTileSize (loadingimg, 192, 0, 192, 192);
    ulStartDrawing2D();
    ulDrawImage(loadingimg);
    ulEndDrawing();
#endif
    initSounds();
    initObjects ();

#ifndef _NOSPLASH_
    //loading frame 2
    ulSetImageTileSize (loadingimg, 384, 0, 192, 192);
    ulStartDrawing2D();
    ulDrawImage(loadingimg);
    ulEndDrawing();
#endif

    myulInitData ();
    if(!fscanf(conf_ini,"map=<%29[a-z A-Z]>\n",buffer))
    {
        PARSERROR;
        while(1)
        {
            WaitForVBL();
        }
    }
#ifndef _NOSPLASH_
    //loading frame 3
    ulSetImageTileSize (loadingimg, 576, 0, 192, 192);
    ulStartDrawing2D();
    ulDrawImage(loadingimg);
    ulEndDrawing();
    ulDeleteImage (loadingimg);
#endif
    changemap(buffer);//"Blood Moor");
    //allocate some memory for wp string (to avoid the functions to free NULL pointer)
    WPactivated=malloc(sizeof(char));
    *WPactivated='\0';

#ifndef Test
    for (i=0; i<SKILLNUMBER; i++)
    {
        skillsLevels[i]=0;
    }
#else
    for (i=0; i<SKILLNUMBER; i++)
    {
        skillsLevels[i]=1;
    }
#endif
    Counter[TOPSCREEN]=8;
    createQuestList();
    mainmenu();
    quickTopScreenRefresh();
    topSetNormalScreen();
    WaitForVBL();
    if(!wasQuestAlreadyLoaded("essai"))loadQuest("essai",1);

    if(isEmulator()) topPrintf(0,0,"Emulator : Save not available");

}


void statsUpdate()
{
    register int i;
    hero.lastx=hero.x;
    hero.lasty=hero.y;

#ifndef NOGBA
    secondpast=(MY_RTC.Seconds!=old_time);
#else
    old_time+=1;
    secondpast=(old_time%60==0);
    old_time%=60;
#endif
    fps+=1;

    if (hero.cooldown) hero.cooldown--;
    if (secondpast)
    {
#ifndef NOGBA
        old_time=MY_RTC.Seconds;
#endif
#ifdef Test
        topPrintf(0,0,"%d",fps );
#endif
        fps = 0;


        for(i=0; i<hero.stats.lifeMax/200; i++)//0.5% per second is enough?
        {
            if(hero.stats.curLife<hero.stats.lifeMax)
            {
                hero.stats.curLife+=1;
            }
            else i=hero.stats.lifeMax;
        }

        for(i=0; i<2; i++)
        {
            if((hero.stats.curMana<hero.stats.manaMax) && !hero.skillperiod) hero.stats.curMana++;
        }
    }

}

