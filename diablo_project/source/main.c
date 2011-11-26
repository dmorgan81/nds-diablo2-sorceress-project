////////////////////////////////////////////
////////////////////////////////////////////
///////////////DIABLO II////////////////////
///////////SORCERESS PROJECT////////////////
////////////////////////////////////////////
////////////////////////////////////////////



//Includes PALib, µLibrary et headers
#include "main.h"
#define Test
#define NOSPAWN
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


///////////////////////////////

int main( int argc, char **argv)
{
///////////////////////////////
/////VARIABLES DEFINITIONS/////
///////////////////////////////


/////////////////
/////charvar/////
/////////////////
    sortchoisi[0]=&firebolt;
    sortchoisi[1]=&iceorb;
    hero.action=0;
    hero.vitesse=256;
    hero.vitesse2=181;//multiplie par 181 sois 1.7 en point fixe
    hero.x=norm_fix(125);//80
    hero.y=norm_fix(30);//40

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
    hero.stats.force=1;
    hero.stats.dexterite=1;
    hero.stats.vitalite=1;
    hero.stats.energie=1  ;
    hero.stats.vie_max=2000;
    hero.stats.vie_restante=(hero.stats.vie_max);
    hero.stats.mana_max=100;
    hero.stats.mana_restante=(hero.stats.mana_max);
    hero.stats.experience=1;
    hero.stats.nextlvl=10;
    hero.stats.lvl=1;

/////////////////////////////////////////////
    hero.stats.mana_restante=0;


    CallAllInits();


    hero.sprite=myulCreateSprite(0,CAMERA_X, CAMERA_Y, CHARFEET_Y);






    auras[0].fonction=&blazeAura;
    cout_sort[0]=10;
    cout_sort[1]=10;






///////////////////////////
////////Main Start/////////
///////////////////////////
#ifdef MUSIC_ON
    AS_MP3StreamPlay("tristram.mp3");
#endif
#ifdef Test
//    PA_OutputText(1,0,0,"u8%d obj%d",sizeof(u8),sizeof(objectinfo));
#endif

    int objectnb=getUnusedObject();
    newObject(200, 64, &objects[objectnb],objectnb, &data[0],0);
    objectnb=getUnusedObject();
    newObject(100, 64, &objects[objectnb],objectnb, &data[2],0 );

    int i=0;

#ifdef Test
    s16 x,y;
#endif
    skillmenu();
    PA_WaitForVBL();
    PA_VBLCounterStart(2);//change
    while(1)
    {
        while(hero.stats.vie_restante>0&&hero.stats.vie_restante<=hero.stats.vie_max)
        {
            hero.cooldown=0;
            MajStats();
            movechar();
#ifdef Test
            PA_OutputText(1,1,7,"distance: %d      ",PA_Distance(fix_norm(objects[2].x)+objects[2].hitbox.down.x,fix_norm(objects[2].y)+objects[2].hitbox.down.y,fix_norm(hero.x)+hero.hitbox.down.x,fix_norm(hero.y)+hero.hitbox.down.y));

            objectnb=-1;
            if (Pad.Held.A)
            {
                objectnb=getUnusedMissile();
                if (objectnb<MAX_MISSILE && objectnb!=-1)
                {

                    x=fix_norm(hero.x)+hero.hitbox.down.x;//PA_RandMax(400);
                    y=fix_norm(hero.y)+hero.hitbox.right.y;//PA_RandMax(310);
                    newMissile(x, y, &missiles[objectnb],objectnb,dir_angle(3),256,-256,mdata[0].dommages, &mdata[0] );
                }
            }
            //PA_OutputText(1,0,0,"%d",secondpast );

            if (Pad.Held.Y)
            {
                changemap(0,1);
            }
            if (Pad.Held.X)
            {
                changemap(1,1);
            }



#endif



            myulSetSpritePrio(hero.sprite,CHARFEET_Y);
            ulReadKeys(0);

            if (!(PA_VBLCounter[2]&128))//change
            {
                for (i=0; i<MAX_DATASPRITES; i++)
                {
                    imagesused[i]=0;
                }
            }
            myulScreenDraws();

            if (!(PA_VBLCounter[2]&128))
            {

                PA_OutputText(1,1,8,"tex: %d    ",ulGetTexVramAvailMemory());
                PA_OutputText(1,1,9,"vertex: %d    ",ulGetVertexAvailMemory());
                PA_OutputText(1,1,10,"state: %d    ",spritedatabase[3].image->imgState);
                for (i=1; i<MAX_DATASPRITES; i++)
                {
                    if(!imagesused[i])ulUnrealizeImage(spritedatabase[i].image);
                }




                PA_OutputText(1,1,11,"state: %d    ",spritedatabase[3].image->imgState);

            }


#ifndef NOSPAWN
            //zm spawning
            if(secondpast)
            {

                for(i=0; i<3; i++)
                {
                    objectnb=getUnusedObject();
                    newObject(PA_RandMinMax (128, 330),PA_RandMinMax (86, 286), &objects[objectnb],objectnb, &data[1],0 );
                }
            }
#endif
            for(i=0; i<MAX_AURAS; i++)
            {
                if(auras[i].life>0)
                    auras[i].fonction(&auras[i]);
            }

            UpdateObjects();


            if(Pad.Newpress.Select)	skillmenu();
            if(Pad.Newpress.Start) pause(&Pad.Newpress.Start);
            PA_WaitForVBL();
        }
        hero.stats.vie_restante=0;
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
    PA_Init();
    PA_InitVBL();
    ulInit(UL_INIT_ALL);
    ulInitGfx();
    ulInitText();
    ulSetMainLcd(0);

    ulSetTexVramParameters(UL_BANK_A | UL_BANK_B  , VRAM_A, 256 << 10); //256ko de vram
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
    PA_CreateTextPal(screen, 9, 0, 0, 0);
#ifndef _NOSPLASH_
    //loading frame 1
    ulSetImageTileSize (loadingimg, 192, 0, 192, 192);
    ulStartDrawing2D();
    ulDrawImage(loadingimg);
    ulEndDrawing();
#endif
    /*
        // Initialize EFS
        if (!EFS_Init(EFS_AND_FAT | EFS_DEFAULT_DEVICE, NULL))
        {
            PA_OutputText(1, 1, 1, "Filesystem init error !!!");
            for(;;) PA_WaitForVBL();
        }
    */
#ifdef MUSIC_ON
    if (!nitroFSInit())
    {
        PA_OutputText(0, 1, 1, "Filesystem init error !!!");
        for(;;) PA_WaitForVBL();
    }

    // Check if tristram.mp3 is there, regardless if libfat or EFS_Lib is used
    MP3FILE* file = FILE_OPEN("tristram.mp3");
    if (!file)
    {
        PA_OutputText(0, 1, 1, "tristram.mp3 not found !!!");
        for(;;) PA_WaitForVBL();
    }
    FILE_CLOSE(file);
#endif
    initobjects ();
#ifndef _NOSPLASH_
    //loading frame 2
    ulSetImageTileSize (loadingimg, 384, 0, 192, 192);
    ulStartDrawing2D();
    ulDrawImage(loadingimg);
    ulEndDrawing();
#endif


    // Init AS_Lib for mp3
    PA_VBLFunctionInit(AS_SoundVBL);
    AS_Init(AS_MODE_MP3 | AS_MODE_SURROUND | AS_MODE_16CH);
    AS_SetDefaultSettings(AS_PCM_8BIT, 16384, AS_SURROUND);

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
    changemap(0,1);
    int i;
    #ifndef Test
    for (i=0;i<SKILLNUMBER;i++){skillsLevels[i]=0;}
    #else
    for (i=0;i<SKILLNUMBER;i++){skillsLevels[i]=1;}
    #endif
}











void MySplash()
{
    s32 i;
    s32 time=180;
    //On mets l'cran en luminusité -31, ce qui le rend noir
    PA_SetBrightness(1, -31);

    //On charge le splash de PAlib
    //PA_EasyBgLoad(1, 1, pasplash);//obselete
    PA_LoadBackground(1, 1, &pasplash);
    //On le fait apparaitre doucement (fade)
    for( i=(-31) ; i<=0 ; i++ )
    {
        PA_SetBrightness(1, i);
        PA_WaitForVBL();
    }

    //On Affiche celui de la ulib avec sa super animation!
    ulShowSplashScreen(3);//splash modifié pour n'apparaitre que sur l'écran de la ulib

    //effet inverse pour le PAsplash, disparait (fade)
    for( i=0 ; i>=(-31) ; i-- )
    {
        PA_SetBrightness(1, i);
        PA_WaitForVBL();
    }
    //On supprime le splash de PAlib
    PA_ResetBg(1);

    //Et on recommence tout ça...
    //PA_EasyBgLoad(1, 1, d_Splash1);//obselete
    PA_LoadBackground(1, 1, &d_Splash1);

    UL_IMAGE* d_splash2 = ulLoadImageFilePNG((void*)d_Splash2_png, (int)d_Splash2_png, UL_IN_RAM, UL_PF_PAL8);
    ulStartDrawing2D();
    ulDrawImage(d_splash2);
    ulEndDrawing();

    for( i=(-31) ; i<=0 ; i++ )
    {
        PA_SetBrightness(1, i);
        PA_WaitForVBL();
    }


    //Soit on attend 3 secondes de splash, soit on appuye sur une touche
    while(time>0 && !(Pad.Newpress.Anykey || Stylus.Newpress))
    {
        time--;
        PA_WaitForVBL();
    }
    UL_IMAGE* loadingimg = ulLoadImageFilePNG((void*)loading_png, (int)loading_png, UL_IN_RAM, UL_PF_PAL8);
    loadingimg->x=32;
    //loading frame 0
    ulSetImageTileSize (loadingimg, 0, 0, 192, 192);
    ulStartDrawing2D();
    ulDrawImage(loadingimg);
    ulEndDrawing();
    ulDeleteImage (loadingimg);

    for( i=0 ; i>=(-31) ; i-- )
    {
        PA_SetBrightness(1, i);
        PA_WaitForVBL();
    }


    //On efface tout ça
    PA_SetBrightness(1, 0);
    PA_ResetBg(1);
    ulDeleteImage (d_splash2);


}






void MajStats()
{
    int i;
    hero.lastx=hero.x;
    hero.lasty=hero.y;

#ifndef NOGBA
    secondpast=(PA_RTC.Seconds!=old_time);
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
        old_time=PA_RTC.Seconds;
#endif
#ifdef Test
        PA_OutputText(1,0,0,"%d",fps );
#endif
        fps = 0;


        for(i=0; i<25; i++)
        {
            if(hero.stats.vie_restante<hero.stats.vie_max)
            {
                hero.stats.vie_restante+=1;
            }
            else i=25;
        }

        QuickTopScreenRefresh();
        for(i=0; i<6; i++)
        {
            if((hero.stats.mana_restante<hero.stats.mana_max) && !hero.skillperiod) hero.stats.mana_restante++;
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
        else if (Stylus.Newpress)	Sort(Stylus.X, Stylus.Y);
        else hero.action=2;

    }

    if (hero.action<=2)
    {
        if 		(Pad.Held.Right&& Pad.Held.Down)
        {
            hero.direction=1;
            hero.action=2;
        }
        else if 	(Pad.Held.Left	&& Pad.Held.Down)
        {
            hero.direction=7;
            hero.action=2;
        }
        else if 	(Pad.Held.Right&& Pad.Held.Up)
        {
            hero.direction=3;
            hero.action=2;
        }
        else if 	(Pad.Held.Left	&& Pad.Held.Up)
        {
            hero.direction=5;
            hero.action=2;
        }
        else hero.action=1;

    }


    if(!hero.action || hero.action ==1)
    {

        if			(Pad.Held.Right)
        {
            hero.direction=2;
            hero.action=1;
        }
        else 	if	(Pad.Held.Left)
        {
            hero.direction=6;
            hero.action=1;
        }
        else 	if (Pad.Held.Down)
        {
            hero.direction=0;
            hero.action=1;
        }
        else 	if (Pad.Held.Up)
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
            hero.x += ((Pad.Held.Right - Pad.Held.Left)*VITESSE);
            hero.y += ((Pad.Held.Down - Pad.Held.Up)*VITESSE);
            break;
        case 1 :
            hero.x += ((Pad.Held.Right - Pad.Held.Left)*VITESSE2);
            hero.y += ((Pad.Held.Down - Pad.Held.Up)*VITESSE2);
            break;
        }
    }
    CheckheroCollisions();
    Mymap->scrollX=fix_norm(hero.x)-CAMERA_X;
    Mymap->scrollY=fix_norm(hero.y)-CAMERA_Y;
#ifdef Test
    PA_OutputText(1,17,17,"%d",fix_norm(hero.x));
    PA_OutputText(1,17,19,"    ");
    PA_OutputText(1,17,19,"%d",GetTile(fix_norm(hero.x),fix_norm(hero.y)));
    PA_OutputText(1,17,18,"%d",fix_norm(hero.y));
#endif
}



