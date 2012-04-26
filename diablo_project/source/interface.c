#include "main.h"
#include "sound.h"
#include "misc.h"
#include "interface.h"
#include "maps/waypoint.h"
#include "quests.h"
extern int curMaxSprite;
bool dialbox=0;
extern const unsigned short skillmenu_map[24][32];
extern u8 skillsLevels[SKILLNUMBER];
const u8 requiredLevel[SKILLNUMBER]= {1/*firebolt*/,1/*icebolt*/,15/*iceorb*/,5/*firewall*/,10/*blaze*/,15/*hydra*/,1/*chargedbolt*/,5/*teleport*/};
extern int MonBaseLife;
inline int FormulaDam(int lvl, int dam,int dam1,int dam2,int dam3,int dam4,int dam5)
{
    if (lvl==1) return dam;
    else if (lvl>=2 && lvl<=8) return (dam+(lvl-1)*dam1);
    else if (lvl>=9 && lvl<=16) return (dam+7*dam1+(lvl-8)*dam2);
    else if (lvl>=17 && lvl<=22) return (dam+7*dam1+8*dam2+(lvl-16)*dam3);
    else if (lvl>=23 && lvl<=28) return (dam+7*dam1+8*dam2+6*dam3+(lvl-22)*dam4);
    else return (dam+7*dam1+8*dam2+6*dam3+6*dam4+(lvl-28)*dam5);
}


int FormulaManaCost(int lvl,int manashift,int mana,int lvlmana)
{
    return ((1<<(manashift+8))/256*((lvlmana*(lvl-1)+mana)))>>8;
}

extern u8 skillpoints;

void saveToFile(char* name)
{
    FILE *save_file = fopen(name, "wb");
    int version=VERSION_NUMBER,wplen=strlen(WPactivated);
    if (!save_file)topPrintf(0,0,"Can't open save, emulator?");
    {
        //header
        fwrite("Diablo Project Save\nVersion",1,strlen("Diablo Project Save\nVersion"),save_file);
        fwrite(&version,sizeof(int),1,save_file);
        fwrite(&wplen,sizeof(int),1,save_file); //activated waypoints string lentgh
        //data
        fwrite(&hero.stats,sizeof(hero.stats),1, save_file);
        fwrite(&skillsLevels,sizeof(skillsLevels),1, save_file);
        fwrite(&skillpoints,sizeof(skillpoints),1, save_file);
//        fwrite(&skillCost,sizeof(skillCost),1, save_file);
//        fwrite(&skilldmg,sizeof(skilldmg),1, save_file);
        fwrite(killedMobs,sizeof(killedMobs),1,save_file);
        fwrite(&currentMap,sizeof(char),currentMapStrLength,save_file);
        fwrite(WPactivated,sizeof(char),wplen,save_file);
        fsaveQuests(save_file);
        fprintf(save_file,"EndOfSaveFile");
        fclose(save_file);
    }
}

void save()
{
    saveToFile("fat:/d2save.sav");
}
bool loadFromSave(char* savefile)
{
    int i=0,version=0,wplen=0;
    FILE *save_file = fopen(savefile, "rb");
    char* hbuffer=NULL;
    hbuffer=malloc(sizeof(char)*strlen("Diablo Project Save\nVersion") + 1);
    if (!save_file)topPrintf(0,0,"Can't open save, emulator?");
    else
    {

        for (i=0; i<strlen("Diablo Project Save\nVersion") ; i++)hbuffer[i]=fgetc(save_file);
        hbuffer[i]='\0';
        if(strcmp(hbuffer,"Diablo Project Save\nVersion")) ERROR("Saved data corrupted.");
        else
        {
            fread(&version,sizeof(int),1,save_file);
            switch(version)
            {
                //when modifications of save storage are made, simply add a case for conversion
            case 0101002 :

                fread(&wplen,sizeof(int),1, save_file);       //activated waypoints string lentgh
                if(WPactivated)free(WPactivated);               //erase and free memory of old string
                WPactivated=malloc((wplen+1)*sizeof(char));     //allocate memory for the string
                *WPactivated='\0';
                fread(&hero.stats,sizeof(hero.stats),1, save_file);
                fread(&skillsLevels,sizeof(skillsLevels),1, save_file);
                fread(&skillpoints,sizeof(skillpoints),1, save_file);
//                fread(&skillCost,sizeof(skillCost),1, save_file);
//                fread(&skilldmg,sizeof(skilldmg),1, save_file);
                fread(killedMobs,sizeof(killedMobs),1,save_file);
                fread(&currentMap,sizeof(char),currentMapStrLength,save_file);
                fread(WPactivated,sizeof(char),wplen,save_file);
                WPactivated[wplen]='\0';
                floadQuests(save_file);

                if(fscanf(save_file,"EndOfSaveFile")==EOF)//basic check
                {
                    ERROR("error loading save...");
                    fclose(save_file);
                    return 0;
                }
                else
                {
                    //refresh top screen and stats
                    topPrintf(20*8,15,"           ");//erase current experience
                    topPrintf(7*8,15,"           ");
                    topPrintf(81,42,"    ");
                    topPrintf(81,66,"    ");
                    topPrintf(81,90,"    ");
                    topPrintf(81,114,"    ");
                    topPrintf(85,42,"%d",hero.stats.strenght);
                    topPrintf(85,66,"%d",hero.stats.dexterity);
                    topPrintf(85,90,"%d",hero.stats.vitality);
                    topPrintf(85,114,"%d",hero.stats.energy);
                    topUpdateLevel();
                    hero.stats.curLife=hero.stats.lifeMax;
                    hero.stats.curMana=hero.stats.manaMax;
                    MonBaseLife=40*(hero.stats.lvl+1)*(hero.stats.lvl+1)+1000*(hero.stats.lvl+1)-512; //fixed point *512 not 256
                    changemap(currentMap);
                }
                break;
            default:
                ERROR("Saved data corrupted.");
                fclose(save_file);
                return 0;
                break;
            }
        }
        fclose(save_file);
        return 1;
    }
    return 0;
}

void load()
{
    saveToFile("fat:/d2save.bak");
    if( !loadFromSave("fat:/d2save.sav") )loadFromSave("fat:/d2save.bak");
}

void mainmenu()
{
    WaitForVBL();
    topDrawBlackScreen();
    myulDrawBlackScreen();
    bool loop=1,helpmenu=0;
    int frameNumber=0, animStage=0;
    ulSetMainLcd(1);
    UL_IMAGE *topscreen= ulLoadImageFilePNG("/gfx/mainmenutop_png.png",0, UL_IN_RAM, UL_PF_PAL8);
    UL_IMAGE *logo= ulLoadImageFilePNG("/gfx/d2logo_png.png",0, UL_IN_RAM, UL_PF_PAL8);

    topSetBackground("mainmenubot");

    logo->x=67;
    logo->y=15;
    while(loop)
    {
        ulStartDrawing2D();
        ulSetDepth(255);
        ulDrawImage(topscreen);

        if(!helpmenu)
        {
            ulSetDepth(256);
            frameNumber++;
            if (frameNumber % 9  == 0) animStage = (animStage + 1) % 8 ;
            ulSetImageTileSize (logo, 0,	57*animStage, 118, 57);
            ulDrawImage(logo);
            ulPrintf_xy(150,180,"Version:%s",VERSION);
        }
        ulEndDrawing();
        if(ul_keys.touch.click)
        {
            if(ul_keys.touch.x>30 && ul_keys.touch.x<225 && ul_keys.touch.y>23 && ul_keys.touch.y<52)loop=0;
            else if(STYLUSBOX(30,73,225-30,102-73))
            {
                load();
                loop=0;
            }
            else if(STYLUSBOX(65,133,173-65,163-133))
            {
                helpmenu=helpmenu^1;
                ulDeleteImage(topscreen);
                if(helpmenu)topscreen=ulLoadImageFilePNG("/gfx/controls_png.png",0, UL_IN_RAM, UL_PF_PAL8);
                else topscreen= ulLoadImageFilePNG("/gfx/mainmenutop_png.png",0, UL_IN_RAM, UL_PF_PAL8);
            }
        }
        WaitForVBL();
    }
    ulDeleteImage(topscreen);
    ulDeleteImage(logo);
    topDrawBlackScreen();
    myulDrawBlackScreen();
    ulSetMainLcd(0);
}

void saveloadmenu(bool saveload)
{
    bool loop=1,loaded=0;
    int i;
    UL_IMAGE *box = ulLoadImageFilePNG("/gfx/textbox_png.png",0, UL_IN_RAM, UL_PF_PAL4);
    WaitForVBL();
    while (loop)
    {
        ulStartDrawing2D();
        myulDrawSprites(0);
        myulDrawDialogBox(box,168);
        if(saveload)
        {
            ulDrawTextBox(3,171,253,190,"Press A button to load your saved progress or B to resume game.",0);
            if (ul_keys.pressed.A)
            {
                ulEndDrawing();
                ulStartDrawing2D();
                myulDrawSprites(0);
                myulDrawDialogBox(box,168);
                ulDrawTextBox(3,171,253,190,"Loading please wait...",0);
                load();
                loaded=1;
                loop=0;
            }
        }
        else
        {
            ulDrawTextBox(3,171,253,190,"Press A button to save your progress or B to resume game.",0);
            if (ul_keys.pressed.A)
            {
                ulEndDrawing();
                ulStartDrawing2D();
                myulDrawSprites(0);
                myulDrawDialogBox(box,168);
                ulDrawTextBox(3,171,253,190,"Saving please wait...",0);
                save();
                loop=0;
            }
        }
        ulEndDrawing();
        if (ul_keys.pressed.B) loop=0;
        WaitForVBL();
    }
    ulDeleteImage(box);
    if(loaded)skillmenu(0);
}



void waypointAI(objectinfo* wp)
{
    if (GetTile(fix_norm(hero.x)+hero.hitbox.down.x,fix_norm(hero.y)+hero.hitbox.down.y)==1 && ul_keys.pressed.A)
    {
        if(!isWaypointActivated(currentMap))activateWaypoint(currentMap);
        showWPMenu();
    }
}

void pause ()//with booloean parameter checked at each frame
{
    CounterPause(0);
    WaitForVBL();
    int frameNumber=0, animStage=0;
    UL_IMAGE *pentacle = ulLoadImageFilePNG("/gfx/pentacle_png.png",0, UL_IN_RAM, UL_PF_PAL4),
                         *pausesprite = ulLoadImageFilePNG("/gfx/pause_png.png",0, UL_IN_RAM, UL_PF_PAL2);
    while (!(PAUSEKEY))
    {
        ulStartDrawing2D();
        myulDrawSprites (0);

        ulSetDepth(255);
        glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_ID(0));
        pausesprite->x=70;
        pausesprite->y=80;
        pentacle->y=65;



        frameNumber++;
        if (frameNumber % 8  == 0) animStage = (animStage + 1) % 8 ;
        ulSetImageTileSize (pentacle, 0,	64*animStage, 64, 64);
        pentacle->x=12;
        ulDrawImage(pentacle);
        pentacle->x=187;
        ulDrawImage(pentacle);
        ulDrawImage(pausesprite);
        ulEndDrawing();
        WaitForVBL();
    }
    ulDeleteImage (pentacle);
    ulDeleteImage (pausesprite);
    CounterStart(VBL);
}

//this function copies the way ulDrawTextBox manage text to know how many characters there is on the first line of text
int TextBoxGetLineCharNb(int x0, int y0, int x1, int y1, const char *text)
{
    int nb=0;
    if (y1>(y0+ul_curFont->charHeight))
    {
        int x,y, x2;
        unsigned char c;
        const char *text2;
        x = x0;
        y = y0;
        while(*text && y==y0)
        {
            c = *text;
            nb++;
            if (c == ' ')
            {
                text2 = text;
                x2 = x;
                do
                {
                    x2 += ul_curFont->charWidths[(int)(*text2++)];
                    if (x2 > x1)
                    {
                        text++;
                        goto newline;
                    }
                }
                while(*text2 != '\n' && *text2 != ' ' && *text2);
            }
            if (x + ul_curFont->charWidths[c] > x1 || *text=='\n')
            {
newline:
                //Prochaine ligne
                x = x0;
                y += ul_curFont->charHeight;
                //Trop bas -> terminé
                if (y + ul_curFont->charHeight > y1)
                    return nb;
                //Retour -> saute
                if (*text == '\n')
                    text++;
                continue;
            }
            x += ul_curFont->charWidths[c];
            text++;
        }
    }
    else while(*text)
        {
            text++;
            nb++;
        }
    return nb;
}


void DialogInBox(char* dialog,int speed,char* topBg,char* sound,int soundOffset,bool anim)
{
    int i;
    //mm_sfxhand sfx=0;
    bool sfx=0;
    int offset=5*speed;
    UL_IMAGE *box = ulLoadImageFilePNG("/gfx/textbox_png.png",0, UL_IN_RAM, UL_PF_PAL4);
    if(topBg)topSetBackground(topBg);
    //if(sound!=-1) loadSound(sound);
    while(*dialog&& !ul_keys.pressed.start)//offset<((190-DIALOGY0)<<3))
    {
        if(offset>=soundOffset)
        {
            if(*sound!=0 && !sfx)    sfx=initStream(sound);
            else if (*sound!=0)streamUpdate();
        }
        offset+=1+2*ul_keys.held.B;
        if (187<128+(offset/speed))
        {
            dialog+=TextBoxGetLineCharNb(3,190-(offset/speed),253,190,dialog);
            offset-=8*speed;
        }
        ulStartDrawing2D();
        myulDrawSprites(anim);
        myulDrawDialogBox(box,128);
        ulDrawTextBox(3,190-(offset/speed),253,190,dialog,0);
        ulEndDrawing();
        WaitForVBL();
    }
    topSetNormalScreen();
    ulDeleteImage(box);
    closeStream();
}



void skillmenu(bool levelup)
{
    bool endloop=0;
    const void (*skillfunction[SKILLNUMBER])(int,int,u16)= {(void*)&firebolt,(void*)&icebolt,(void*)&iceorb,(void*)&blaze,(void*)&firewall,(void*)&hydra,(void*)&chargedbolt,(void*)&teleport};
    const u8 skillx[SKILLNUMBER]= {12,12,60,60,108,156,12,60};
    const u8 skilly[SKILLNUMBER]= {12,60,60,12,12,12,108,108};
    const u8 skillframe[SKILLNUMBER]= {0,2,8,3,4,7,1,5};
    const u8 fDam[SKILLNUMBER][2][6]=
    {
        {{6,3,4,8,18,54}        ,{12,3,6,10,20,56}      } ,
        {{6,2,4,6,8,10}         ,{10,3,5,7,9,11}       } ,
        {{80,20,24,28,29,30}    ,{90,21,25,29,30,31}    } ,
        {{4,2,3,4,6,9}          ,{8,2,3,4,6,9}          } ,
        {{15,9,14,21,21,21}     ,{20,9,14,21,21,21}     } ,
        {{24,9,13,17,21,25}     ,{34,11,15,19,23,27}    } ,
        {{4,1,1,2,3,4}          ,{8,1,1,2,3,4}          } ,
        {{0,0,0,0,0,0}          ,{0,0,0,0,0,0}          }
    };
    const int skillRatio[SKILLNUMBER]= {1,1,1,9,9,1,1,0};
    const int fMana[SKILLNUMBER][3]=
    {
        {7,5,0},
        {8,3,0},
        {7,50,1},
        {7,22,1},
        {8,22,1},
        {7,40,1},
        {5,24,4},
        {8,24,-1}
    };
    u8 i;

    WaitForVBL();
    myulUnrealizeSprites();
    myulDrawBlackScreen();
    UL_IMAGE *skillicons = ulLoadImageFilePNG("/gfx/sorts_png.png",0, UL_IN_RAM, UL_PF_PAL4);
    UL_IMAGE *numberslot = ulLoadImageFilePNG("/gfx/number_png.png",0, UL_IN_RAM, UL_PF_PAL2);
    UL_IMAGE *exitbtn=ulLoadImageFilePNG("/gfx/exit_png.png",0, UL_IN_VRAM, UL_PF_PAL4);
    UL_IMAGE *skillTiles = ulLoadImageFilePNG("/gfx/skilltiles_png.png",0, UL_IN_VRAM, UL_PF_PAL4);
    UL_MAP *skillbg = ulCreateMap(skillTiles,/*Tileset*/skillmenu_map,8,8,/*Tiles size*/32,24,/*Map size*/UL_MF_U16);//Map format

    while (!endloop)
    {

        ulStartDrawing2D();
        ulSetDepth(0);
        //Fond sur l'écran du bas
        ulDrawMap(skillbg);
        //ulDrawImage(skillbg);

        glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_ID(0));

        for(i=0; i<SKILLNUMBER; i++)
        {
            ulSetDepth(1);
            numberslot->x=skillx[i]+30;
            numberslot->y=skilly[i]+20;
            ulDrawImage(numberslot);
            ulSetDepth(2);
            skillicons->x=skillx[i];
            skillicons->y=skilly[i];
            ulSetImageTileSize (skillicons,0,32*skillframe[i],32,32);
            if (!skillsLevels[i])
            {
                ulSetImageTint(skillicons,0x14d4);
            }
            else ulSetImageTint(skillicons,0x7fff);
            ulDrawImage(skillicons);
            ulSetDepth(3);
            ulPrintf_xy(skillx[i]+33,skilly[i]+24,"%i",skillsLevels[i]);
        }
        if (skillpoints&&levelup)ulPrintf_xy(3,1,"Click to upgrade skill. Points left : %i",skillpoints);
        else if (selectedSkill[0]==&nospell)ulPrintf_xy(3,1,"Please click to select your first skill");
        exitbtn->x=212;
        exitbtn->y=156;
        ulDrawImage(exitbtn);
        ulEndDrawing();



        WaitForVBL();

        if(ul_keys.touch.click)
        {

            for(i=0; i<SKILLNUMBER; i++)
            {
//                if(ul_keys.touch.x>skillx[i]&&ul_keys.touch.x<(skillx[i]+32)&&ul_keys.touch.y>skilly[i]&&ul_keys.touch.y<(skilly[i]+32))
                if(STYLUSBOX(skillx[i],skilly[i],32,32))
                {
                    if (levelup&&skillpoints&&(hero.stats.lvl>=requiredLevel[i]))
                    {
                        //should ask for confirmation
                        skillsLevels[i]++;
                        skillpoints--;
                        //ulPrintf_xy(skillx[i]+33,skilly[i]+24,"%i",skillsLevels[i]);
                    }
                    else if (skillsLevels[i] && !(levelup&&skillpoints))
                    {
                        currentSkill[ul_keys.held.L]=i;
                        //Calculate damages, mana
                        skillCost[ul_keys.held.L]=FormulaManaCost(skillsLevels[i],fMana[i][0],fMana[i][1],fMana[i][2]);
                        skilldmg[i][0]=(FormulaDam(skillsLevels[i],fDam[i][0][0],fDam[i][0][1],fDam[i][0][2],fDam[i][0][3],fDam[i][0][4],fDam[i][0][5])>>1)*skillRatio[i];
                        skilldmg[i][1]=(FormulaDam(skillsLevels[i],fDam[i][1][0],fDam[i][1][1],fDam[i][1][2],fDam[i][1][3],fDam[i][1][4],fDam[i][1][5])>>1)*skillRatio[i];
                        //select the skill and changes images according to it
                        selectedSkill[ul_keys.held.L]=(void*)skillfunction[i];
                        topSetSkill(skillframe[currentSkill[ul_keys.held.L]],ul_keys.held.L);
                        if (selectedSkill[ul_keys.held.L ^ 1]==&nospell) //check if other skill has been set (only useful at game start)
                        {
                            currentSkill[ul_keys.held.L ^ 1] =currentSkill[ul_keys.held.L];
                            selectedSkill[ul_keys.held.L ^ 1]   =selectedSkill[ul_keys.held.L];
                            skillCost[ul_keys.held.L ^ 1]    =skillCost[ul_keys.held.L];
                            topSetSkill(skillframe[currentSkill[ul_keys.held.L^1]],ul_keys.held.L^1);
                        }
                        i=SKILLNUMBER;
                        endloop=1;
                    }
                    else if (Counter[TALKING]>60)
                    {
                        CounterStart(TALKING);
                        playSound(SFX_SOR_CANTUSEYET);
                    }
                }
                else if ((ul_keys.touch.x>212&&ul_keys.touch.x<244&&ul_keys.touch.y>156&&ul_keys.touch.y<188)  || SKILLMENU_KEY)
                {
                    if (selectedSkill[0]!=&nospell && selectedSkill[1]!=&nospell) endloop=1;
                }
            }
        }

    }



    ulDeleteImage   (skillicons);
    ulDeleteImage   (numberslot);
    ulDeleteImage   (skillTiles);
    ulDeleteImage   (exitbtn);
    ulDeleteMap     (skillbg);
    myulDrawBlackScreen();

}



void death()
{
    WaitForVBL();
    myulUnrealizeSprites();
    extern char currentMap[currentMapStrLength];
    quickTopScreenRefresh();
    UL_IMAGE *deathscreen = ulLoadImageFilePNG("/gfx/deathscreen_png.png",0, UL_IN_RAM, UL_PF_PAL8);
    ulStartDrawing2D();
    ulSetDepth(0);
    ulDrawImage(deathscreen);
    loadSound(SFX_DEATH);
    playSound(SFX_DEATH);
    ulEndDrawing();
    WaitForVBL();
    while (!(ul_keys.pressed.value||ul_keys.touch.click))WaitForVBL();
    ulDeleteImage(deathscreen);
    hero.stats.curLife=hero.stats.lifeMax;
    quickTopScreenRefresh();
    myulInitData(1);
    changemap(currentMap);
    WaitForVBL();
    unloadSound(SFX_DEATH);
}

