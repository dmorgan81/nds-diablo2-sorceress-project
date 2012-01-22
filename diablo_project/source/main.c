////////////////////////////////////////////
////////////////////////////////////////////
///////////////DIABLO II////////////////////
///////////SORCERESS PROJECT////////////////
////////////////////////////////////////////
////////////////////////////////////////////



//Includes PALib, µLibrary et headers
#include <nds.h>
#include "main.h"
#include "misc.h"
#define Test
//#define NOSPAWN
#ifdef Test
#define _NOSPLASH_ //quote this line to make splash appear
#endif
#define NOGBA


////////////////////////////////
/////FUNCTIONS DECLARATIONS/////
////////////////////////////////

void MySplash();
void CallAllInits();
void MajStats();

////////////////////////////////
/////VARIABLES DECLARATIONS/////
////////////////////////////////
s8 fps = 0; //Our FPS
u8 old_time=0;
bool secondpast=1;
charstruct hero;
extern void save();
extern int currentMap;
extern int MonBaseLife;
///////////////////////////////
int bg3_sub;

int main( int argc, char **argv)
{
///////////////////////////////
/////VARIABLES DEFINITIONS/////
///////////////////////////////


/////////////////
/////charvar/////
/////////////////
    sortchoisi[0]=&nospell;
    sortchoisi[1]=&nospell;
    hero.action=0;
    hero.vitesse=256;
    hero.vitesse2=181;//multiplie par 181 sois 1.7 en point fixe
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
    hero.stats.strenght=10;
    hero.stats.dexterity=25;
    hero.stats.vitality=10;
    hero.stats.energy=35;
    hero.stats.lifeMax=2000;
    hero.stats.curLife=hero.stats.lifeMax;
    hero.stats.manaMax=35;
    hero.stats.curMana=(hero.stats.manaMax);
    hero.stats.experience=0;
    hero.stats.nextlvl=400;
    hero.stats.lvl=1;

/////////////////////////////////////////////



    CallAllInits();


    hero.sprite=myulCreateSprite(0,CAMERA_X, CAMERA_Y, CHARFEET_Y);






    auras[0].fonction=&blazeAura;






///////////////////////////
////////Main Start/////////
///////////////////////////
#ifdef MUSIC_ON
//    AS_MP3StreamPlay("tristram.mp3");
#endif
#ifdef Test
//    //PA_OutputText(1,0,0,"u8%d obj%d",sizeof(u8),sizeof(objectinfo));
#endif

    int objectnb=getUnusedObject();
    newObject(80, -40, &objects[objectnb],objectnb, &data[0],0);


    int i=0;
    Mymap->scrollX=fix_norm(hero.x)-CAMERA_X;
    Mymap->scrollY=fix_norm(hero.y)-CAMERA_Y;
    updateObjects();
#ifdef Test
    s16 x,y;
#endif
#ifndef Test
    hero.direction=4;
    movechar();
    for (i=0; i<280; i++)
    {
        updateObjects();
        objects[objectnb].y+=64;
        sprites[objects[objectnb].sprite].prio=100;
        sprites[objects[objectnb].sprite].prio=100;
        sprites[fxinfo[objects[objectnb].fx[0]].sprite].prio=100;
        sprites[fxinfo[objects[objectnb].fx[1]].sprite].prio=100;
        myulScreenDraws();
        WaitForVBL();
    }

    DialogInBox("Welcome to the world of Sanctuary, sorceress.\nAs you may know, this land is, once again, struck by the Three.\n\n\
I am the Archangel Tyrael. I came here to prevent Diablo from freeing his brother, Baal. But I have failed. Now, Terror and Destruction roam free throughout your world.\n\n\
Even now, they head towards the Eastern capital of Kurast - to the very heart of the Zakarum Temple. There they hope to find their eldest brother, Mephisto, the Lord of Hatred who was imprisoned there ages ago.\n\n\
If the three Prime Evils unite, they will be invincible. Though it is unclear as to what their aims are, it is certain that they must be stopped at all costs.\n\n\
I am broken and the energys that tie me to this world are diminishing rapidly.\n\n\
You must take up this quest and prevent the Three Brothers from reuniting. You must cross the sea and search for Diablo and Baal in Kurast.\n\n\
Now hurry, mortal... Time is running out for all of us!\n",10,1);
#endif
    skillmenu(1);
    objectnb=getUnusedObject();
    newObject(100, 50, &objects[objectnb],objectnb, &data[3],0);

    WaitForVBL();

    PA_VBLCounterStart(0);
    while(1)
    {
        while(hero.stats.curLife>0&&hero.stats.curLife<=hero.stats.lifeMax)
        {

            hero.cooldown=0;
            MajStats();
            movechar();
            QuickTopScreenRefresh();

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


            myulSetSpritePrio(hero.sprite,CHARFEET_Y);

            if (!(PA_VBLCounter[0]&128))//change
            {
                for (i=0; i<MAX_DATASPRITES; i++)
                {
                    imagesused[i]=0;
                }
            }
            myulScreenDraws();

            if (!(PA_VBLCounter[0]&128))
            {
#ifdef Test
                //PA_OutputText(1,1,8,"tex: %d    ",ulGetTexVramAvailMemory());
                //PA_OutputText(1,1,9,"vertex: %d    ",ulGetVertexAvailMemory());
#endif
                if (ulGetTexVramAvailMemory()<10000) //security, use it only when necessary because it make some flashes on real ds if the sprite is used right after
                {
                    for (i=1; i<MAX_DATASPRITES; i++)
                    {
                        if(!imagesused[i])ulUnrealizeImage(spritedatabase[i].image);
                    }
                }
            }


#ifndef NOSPAWN
            //spawning
            if(!(PA_VBLCounter[0]&511))
            {
                if (hero.stats.lvl<2)
                {
                    objectnb=getUnusedObject();
                    int x=PA_RandMinMax (128+currentMap*50, 330+currentMap*500),y=PA_RandMinMax (86+currentMap*150, 286+currentMap*256);
                    while (GetTile(x,y)>=NWALKABLETILE)
                    {
                        x=PA_RandMinMax (128+currentMap*50, 330+currentMap*500);
                        y=PA_RandMinMax (86+currentMap*150, 286+currentMap*256);
                    }
                    if (!PA_RandMax(2))
                    {
                        newObject(x,y, &objects[objectnb],objectnb, &data[1],0 );
                        objects[objectnb].life=((MonBaseLife*data[1].life)/100+512)>>9;
                    }
                    else
                    {
                        newObject(x,y, &objects[objectnb],objectnb, &data[2+currentMap],0 );
                        objects[objectnb].life=((MonBaseLife*data[2+currentMap].life)/100+512)>>9;
                    }
                }
                else for(i=0; i<=(hero.stats.lvl>>1)+1; i++)
                    {
                        objectnb=getUnusedObject();
                        int x=PA_RandMinMax (128+currentMap*50, 330+currentMap*500),y=PA_RandMinMax (86+currentMap*150, 286+currentMap*256);
                        while (GetTile(x,y)>=NWALKABLETILE)
                        {
                            x=PA_RandMinMax (128+currentMap*50, 330+currentMap*500);
                            y=PA_RandMinMax (86+currentMap*150, 286+currentMap*256);
                        }
                        if (!PA_RandMax(2))
                        {
                            newObject(x,y, &objects[objectnb],objectnb, &data[1],0 );
                            objects[objectnb].life=((MonBaseLife*data[1].life)/100+512)>>9;
                        }
                        else
                        {
                            newObject(x,y, &objects[objectnb],objectnb, &data[2+currentMap],0 );
                            objects[objectnb].life=((MonBaseLife*data[2+currentMap].life)/100+512)>>9;
                        }
                    }
            }
#endif
            for(i=0; i<MAX_AURAS; i++)
            {
                if(auras[i].life>0)
                    auras[i].fonction(&auras[i]);
            }

            updateObjects();
            if(ul_keys.pressed.X) saveloadmenu(0);
            if(ul_keys.pressed.Y) saveloadmenu(1);
#ifdef Test
            if(ul_keys.pressed.B) hero.stats.experience+=100;
#endif
            if(ul_keys.pressed.select)	skillmenu(0); //will be changed later, we cant firce player to levelup skills if they just want to switch
            if(PAUSEKEY || ul_keys.held.lid) pause();//(int*)ul_keys.pressed.start);


            CheckForLevelUp();
            WaitForVBL();
        }
        hero.stats.curLife=0;
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

















void CallAllInits()
{

    ulInit(UL_INIT_ALL);
    ulInitGfx();
    ulInitText();
    ulSetMainLcd(0);
    videoSetModeSub(MODE_5_2D | DISPLAY_BG3_ACTIVE);
    vramSetBankH(VRAM_H_SUB_BG);
    vramSetBankI(VRAM_I_SUB_BG_0x06208000);
    bg3_sub = bgInitSub(3, BgType_Bmp8, BgSize_B8_256x256, 0,0);
    ulSetTexVramParameters(UL_BANK_A | UL_BANK_B | UL_BANK_C | UL_BANK_D, VRAM_A, 512 << 10); //256ko de vram
    PA_VBLCountersReset();
    if (!nitroFSInit())
    {
        ////PA_OutputText(0, 1, 1, "Filesystem init error !!!");
        for(;;) WaitForVBL();
    }


#ifndef _NOSPLASH_
    //Affiches des splashs, PAlib, uLibrary, Project...
    MySplash();

    UL_IMAGE* loadingimg = ulLoadImageFilePNG((void*)loading_png, (int)loading_png, UL_IN_RAM, UL_PF_PAL8);
    loadingimg->x=32;
    //loading frame 0
    ulSetImageTileSize (loadingimg, 0, 0, 192, 192);
    ulStartDrawing2D();
    ulDrawImage(loadingimg);
    ulEndDrawing();
#endif
    //Font PALIB
    /*
        //PA_InitCustomText(1, 0, exocet);//obselete
        PA_LoadText(1, 0, &exocet);
        PATEXT_ALL_COL_WHITE //define, changing default text color
        //essai pour les palettes

        int screen=1;
        PA_CreateTextPal(screen, 0, 31, 31, 31);
        PA_CreateTextPal(screen, 1, 31, 0, 0);
        PA_CreateTextPal(screen, 2, 0, 31, 0);
        PA_CreateTextPal(screen, 3, 0, 0, 31);
        PA_CreateTextPal(screen, 4, 31, 0, 31);
        PA_CreateTextPal(screen, 5, 0, 31, 31);
        PA_CreateTextPal(screen, 6, 31, 31, 0);
        PA_CreateTextPal(screen, 7, 25, 25, 25);
        PA_CreateTextPal(screen, 8, 20, 20, 20);
        PA_CreateTextPal(screen, 9, 0, 0, 0);*/
#ifndef _NOSPLASH_
    //loading frame 1
    ulSetImageTileSize (loadingimg, 192, 0, 192, 192);
    ulStartDrawing2D();
    ulDrawImage(loadingimg);
    ulEndDrawing();
#endif

#ifdef MUSIC_ON
    /*
        // Check if tristram.mp3 is there, regardless if libfat or EFS_Lib is used
        MP3FILE* file = FILE_OPEN("tristram.mp3");
        if (!file)
        {
            //PA_OutputText(0, 1, 1, "tristram.mp3 not found !!!");
            for(;;) WaitForVBL();
        }
        FILE_CLOSE(file);
        */
#endif
    initobjects ();
#ifndef _NOSPLASH_
    //loading frame 2
    ulSetImageTileSize (loadingimg, 384, 0, 192, 192);
    ulStartDrawing2D();
    ulDrawImage(loadingimg);
    ulEndDrawing();
#endif

    /*
        // Init AS_Lib for mp3
        PA_VBLFunctionInit(AS_SoundVBL);
        AS_Init(AS_MODE_MP3 | AS_MODE_SURROUND | AS_MODE_16CH);
        AS_SetDefaultSettings(AS_PCM_8BIT, 16384, AS_NO_DELAY);//AS_SURROUND delay is creepy
        AS_ReserveChannel(0);//hero's channel

    */
    InitTopScreen ();
#ifndef _NOSPLASH_
    //loading frame 3
    ulSetImageTileSize (loadingimg, 576, 0, 192, 192);
    ulStartDrawing2D();
    ulDrawImage(loadingimg);
    ulEndDrawing();
    ulDeleteImage (loadingimg);
#endif
    myulInitData (0);
    changemap(0);
    int i;
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
    WaitForVBL();
}











void MySplash()
{
    s32 time=180;
    _GFX_ALIGN char *buffer=(char*)malloc(49152*sizeof(char));
    _GFX_ALIGN short *palbuffer=(short*)malloc(256*sizeof(short));
    FILE* file;
    if (buffer&&palbuffer)
    {
        file=fopen("/d_Splash1_Bitmap.bin", "rb");
        fread(buffer, 1, 49152*sizeof(u8), file);
        fclose(file);
        dmaCopy(buffer, bgGetGfxPtr(bg3_sub), 256*192);
        file=fopen("/d_Splash1_Pal.bin", "rb");
        fread(palbuffer, 1, 256*sizeof(short), file);
        fclose(file);
        dmaCopy(palbuffer, BG_PALETTE_SUB, 256*2);
    }
    free(buffer);
    free(palbuffer);

    ulShowSplashScreen(3);
    UL_IMAGE* d_splash2 = ulLoadImageFilePNG((void*)d_Splash2_png, (int)d_Splash2_png, UL_IN_RAM, UL_PF_PAL8);
    ulStartDrawing2D();
    ulDrawImage(d_splash2);
    ulEndDrawing();

    //Soit on attend 3 secondes de splash, soit on appuye sur une touche
    while(time>0 && !(ul_keys.pressed.value || ul_keys.touch.click))
    {
        time--;
        WaitForVBL();
    }
    UL_IMAGE* loadingimg = ulLoadImageFilePNG((void*)loading_png, (int)loading_png, UL_IN_RAM, UL_PF_PAL8);
    loadingimg->x=32;
    //loading frame 0
    ulSetImageTileSize (loadingimg, 0, 0, 192, 192);
    ulStartDrawing2D();
    ulDrawImage(loadingimg);
    ulEndDrawing();
    ulDeleteImage (loadingimg);
    ulDeleteImage (d_splash2);


}






void MajStats()
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
        //PA_OutputText(1,0,0,"%d",fps );
#endif
        fps = 0;


        for(i=0; i<25; i++)
        {
            if(hero.stats.curLife<hero.stats.lifeMax)
            {
                hero.stats.curLife+=1;
            }
            else i=25;
        }

        for(i=0; i<2; i++)
        {
            if((hero.stats.curMana<hero.stats.manaMax) && !hero.skillperiod) hero.stats.curMana++;
        }
    }

}






void movechar()
{

    if (hero.action<=3)
    {
        if (hero.skillperiod==1)
        {
            myulDefaultAnim (hero.sprite);
        }
        if (hero.skillperiod)		hero.skillperiod--;
        else if (hero.cooldown)
        {
            hero.cooldown--;
            hero.action=2;
        }
// NOTE (Clement#1#): attention .click marche pas, pourquoi?
        else if (ul_keys.touch.click)
        {
            Sort(ul_keys.touch.x, ul_keys.touch.y);
        }
        else hero.action=2;

    }

    if (hero.action<=2)
    {
        if 		(ul_keys.held.right&& ul_keys.held.down)
        {
            hero.direction=1;
            hero.action=2;
        }
        else if 	(ul_keys.held.left	&& ul_keys.held.down)
        {
            hero.direction=7;
            hero.action=2;
        }
        else if 	(ul_keys.held.right&& ul_keys.held.up)
        {
            hero.direction=3;
            hero.action=2;
        }
        else if 	(ul_keys.held.left	&& ul_keys.held.up)
        {
            hero.direction=5;
            hero.action=2;
        }
        else hero.action=1;

    }


    if(!hero.action || hero.action ==1)
    {

        if			(ul_keys.held.right)
        {
            hero.direction=2;
            hero.action=1;
        }
        else 	if	(ul_keys.held.left)
        {
            hero.direction=6;
            hero.action=1;
        }
        else 	if (ul_keys.held.down)
        {
            hero.direction=0;
            hero.action=1;
        }
        else 	if (ul_keys.held.up)
        {
            hero.direction=4;
            hero.action=1;
        }
        else 		hero.action=0;

    }


    u8 columnaddaction;
    if (hero.action>1) columnaddaction= (hero.action-1)*5;
    else columnaddaction= hero.action*5;
    switch (hero.direction)
    {
    case 0 :
        myulImageColumn (hero.sprite,columnaddaction);

        break;

    case 1 :
        myulImageColumn (hero.sprite,1+columnaddaction);
        myulImageFlip(hero.sprite,0,0);
        break;

    case 2 :
        myulImageColumn (hero.sprite,2+columnaddaction);
        myulImageFlip(hero.sprite,0,0);
        break;

    case 3 :
        myulImageColumn (hero.sprite,3+columnaddaction);
        myulImageFlip(hero.sprite,0,0);
        break;

    case 4 :
        myulImageColumn (hero.sprite,4+columnaddaction);

        break;

    case 5 :
        myulImageColumn (hero.sprite,3+columnaddaction);
        myulImageFlip(hero.sprite,1,0);
        break;

    case 6 :
        myulImageColumn (hero.sprite,2+columnaddaction);
        myulImageFlip(hero.sprite,1,0);
        break;

    case 7 :
        myulImageColumn (hero.sprite,1+columnaddaction);
        myulImageFlip(hero.sprite,1,0);
        break;

    }




    if (hero.action ==1 || hero.action ==2)
    {

        switch (hero.direction%2)
        {
        case 0 :
            hero.x += ((ul_keys.held.right - ul_keys.held.left)*VITESSE);
            hero.y += ((ul_keys.held.down - ul_keys.held.up)*VITESSE);
            break;
        case 1 :
            hero.x += ((ul_keys.held.right - ul_keys.held.left)*VITESSE2);
            hero.y += ((ul_keys.held.down - ul_keys.held.up)*VITESSE2);
            break;
        }
    }
    CheckheroCollisions();
    Mymap->scrollX=fix_norm(hero.x)-CAMERA_X;
    Mymap->scrollY=fix_norm(hero.y)-CAMERA_Y;
#ifdef Test
    //PA_OutputText(1,17,17,"%d",fix_norm(hero.x));
    //PA_OutputText(1,17,19,"    ");
    //PA_OutputText(1,17,19,"%d",GetTile(fix_norm(hero.x),fix_norm(hero.y)));
    //PA_OutputText(1,17,18,"%d",fix_norm(hero.y));
#endif
}



