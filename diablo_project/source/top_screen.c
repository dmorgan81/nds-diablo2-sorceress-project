#include "top_screen.h"
#include "defines.h"
int lastLifeLevel,lastManaLevel,orbLifeLevel,orbManaLevel;
_GFX_ALIGN char *topscr_buffer=NULL;
_GFX_ALIGN char *topscr_font=NULL;
_GFX_ALIGN char *topscr_orbs=NULL;
_GFX_ALIGN char *topscr_levelFont=NULL;
_GFX_ALIGN short *topscr_palbuffer=NULL;
u8 lvlfontsizes[10]= {18,9,14,14,15,15,14,14,15,14};
extern int bg3_sub;
void InitTopScreen (void)
{
    topscr_buffer=(char*)malloc(256*192*sizeof(char));
    topscr_orbs=(char*)malloc(256*42*sizeof(char));
    topscr_palbuffer=(short*)malloc(256*sizeof(short));
    topscr_font=(char*)malloc(256*24*sizeof(char));
    topscr_levelFont=(char*)malloc(210*21*sizeof(char));


    int i;
    FILE* file;
    if (topscr_buffer&&topscr_palbuffer)
    {
        file=fopen("/fond_haut_Bitmap.bin", "rb");
        //copy main background
        fread(topscr_buffer, sizeof(char), 256*192, file);
        //copy images of the orbs and the backup of the background
        for(i=0; i<42; i++)
        {
            fread(topscr_orbs+168*i, sizeof(char), 84, file);
            dmaCopy(topscr_buffer+(143+i)*256+17,topscr_orbs+84+i*168,42);
            dmaCopy(topscr_buffer+(143+i)*256+198,topscr_orbs+126+i*168,42);
            fseek(file,172,SEEK_CUR);
        }

        //copy the level numbers font
        fseek(file,256*192+84,SEEK_SET);
        for(i=0; i<21; i++)
        {
            fread(topscr_levelFont+210*i, sizeof(char), 168, file);
            fseek(file,88,SEEK_CUR);
        }
        fseek(file,256*192+256*21+84,SEEK_SET);
        for(i=0; i<21; i++)//copy images of the orbs and the backup of the background
        {
            fread(topscr_levelFont+210*i+168, sizeof(char), 42, file);
            fseek(file,256*(192+21+i)+84,SEEK_SET);
        }

        fclose(file);
        dmaCopy(topscr_buffer, bgGetGfxPtr(bg3_sub), 256*192);
        file=fopen("/fond_haut_Pal.bin", "rb");
        fread(topscr_palbuffer, sizeof(short), 256, file);
        fclose(file);

        file=fopen("/exocet_Bitmap.bin", "rb");
        fread(topscr_font, sizeof(char), 256*24, file);
        fclose(file);
        dmaCopy(topscr_palbuffer, BG_PALETTE_SUB, 256*2);
    }
    //topDrawImage(17,143,topscr_orbs,0,0,42,42,168);
    //topDrawImage(198,143,topscr_orbs,42,0,42,42,168);
    dmaCopy(topscr_buffer, bgGetGfxPtr(bg3_sub), 256*192);
    dmaCopy(topscr_palbuffer, BG_PALETTE_SUB, 256*2);
    PA_VBLCounterStart(1);

}

void QuickTopScreenRefresh (void)
{
    if(!(PA_VBLCounter[1]&15))
    {

        ///Draw buffer to screen
        dmaCopy(topscr_buffer, bgGetGfxPtr(bg3_sub), 256*192);
        dmaCopy(topscr_palbuffer, BG_PALETTE_SUB, 256*2);
    }
    //we do actualize top screen every 16 frames, enough to have something smooth, and it doesnt impact the overall fps
    else if (!(PA_VBLCounter[1]&7))
    {
        ///set the correct images of the orbs in the buffer
        orbLifeLevel=((hero.stats.lifeMax-hero.stats.curLife)*42)/hero.stats.lifeMax;
        //check what should be change
        if(lastLifeLevel<orbLifeLevel)topDrawImage(17,143,topscr_orbs,84,0,42,orbLifeLevel,168);
        else topDrawImage(17,143+orbLifeLevel,topscr_orbs,0,orbLifeLevel,42,42-orbLifeLevel,168);
        orbManaLevel=((hero.stats.manaMax-hero.stats.curMana)*42)/hero.stats.manaMax;
        if(lastManaLevel<orbManaLevel)topDrawImage(198,143,topscr_orbs,126,0,42,orbManaLevel,168);             //same
        else topDrawImage(198,143+orbManaLevel,topscr_orbs,42,orbManaLevel,42,42-orbManaLevel,168);
        lastLifeLevel=orbLifeLevel;
        lastManaLevel=orbManaLevel;
        topPrintf(7*8,7,"Experience");
        topPrintf(7*8,15,"%d",hero.stats.experience);
        topPrintf(20*8,7,"Next level");
        topPrintf(20*8,15,"%d",hero.stats.nextlvl);
        topPrintf(7,42,"Strenght");
        topPrintf(7,66,"Dexterity");
        topPrintf(7,90,"Vitality");
        topPrintf(7,114,"Energy");

        topPrintf(85,42,"%d",hero.stats.strenght);
        topPrintf(85,66,"%d",hero.stats.dexterity);
        topPrintf(85,90,"%d",hero.stats.vitality);
        topPrintf(85,114,"%d",hero.stats.energy);
        topPrintf(7*8,134,"%d",hero.stats.resfire);
        topPrintf(9*8,134,"%d",hero.stats.resice);
        topPrintf(11*8,134,"%d",hero.stats.reslight);
        topPrintf(13*8,134,"%d",hero.stats.respsn);
    }
}


void topDrawImage(int x,int y,char* source,int offsetx,int offsety,int sizex, int sizey,int dataheight)
{
    register int i;
    if(sizey&3) //if the number of lines is even we can copy 2line at the same time
    {
        for (i=0; i<sizey; i++)
        {
            dmaCopyHalfWords (2,source+offsetx+dataheight*(offsety+i),topscr_buffer+x+SCREEN_WIDTH*(y+i) , sizex);
        }
    }
    if(sizey&1) //if the number of lines is even we can copy 2line at the same time
    {
        for (i=0; i<sizey-3; i+=4)
        {
            dmaCopyHalfWordsAsynch (0,source+offsetx+dataheight*(offsety+i),topscr_buffer+x+SCREEN_WIDTH*(y+i) , sizex);
            dmaCopyHalfWordsAsynch (1,source+offsetx+dataheight*(offsety+i+1),topscr_buffer+x+SCREEN_WIDTH*(y+i+1) , sizex);
            dmaCopyHalfWordsAsynch (2,source+offsetx+dataheight*(offsety+i+2),topscr_buffer+x+SCREEN_WIDTH*(y+i+2) , sizex);
            dmaCopyHalfWords (3,source+offsetx+dataheight*(offsety+i+3),topscr_buffer+x+SCREEN_WIDTH*(y+i+3) , sizex);
        }
    }

    else
    {
        for (i=0; i<sizey-1; i+=2)
        {
            dmaCopyHalfWordsAsynch (2,source+offsetx+dataheight*(offsety+i),topscr_buffer+x+SCREEN_WIDTH*(y+i) , sizex);
            dmaCopyHalfWords (3,source+offsetx+dataheight*(offsety+i+1),topscr_buffer+x+SCREEN_WIDTH*(y+i+1) , sizex);
        }
    }
}

void topDrawString(int x,int y,char* string)
{
    int i=0;
    while(*(string+i) != '\0')
    {
        topDrawChar(*(string+i),x+(i<<3),y);
        i++;
    }
}


void topUpdateLevel(void)
{
    if(hero.stats.lvl<10)
    {
        topDrawString(10,5,"    ");
        topDrawString(10,13,"    ");
        topDrawString(10,21,"    ");
        topDrawImage(26-lvlfontsizes[hero.stats.lvl]/2, 7,topscr_levelFont,(hero.stats.lvl*21),0,lvlfontsizes[hero.stats.lvl],21,210);
    }
    else
    {
        topDrawString(10,5,"    ");
        topDrawString(10,13,"    ");
        topDrawString(10,21,"    ");
        topDrawImage(26-(lvlfontsizes[hero.stats.lvl/10]+lvlfontsizes[hero.stats.lvl%10])/2, 7,topscr_levelFont,((hero.stats.lvl/10)*21),0,lvlfontsizes[hero.stats.lvl/10],21,210);
        topDrawImage(26-(-lvlfontsizes[hero.stats.lvl/10]+lvlfontsizes[hero.stats.lvl%10])/2, 7,topscr_levelFont,((hero.stats.lvl%10)*21),0,lvlfontsizes[hero.stats.lvl%10],21,210);
    }
}
