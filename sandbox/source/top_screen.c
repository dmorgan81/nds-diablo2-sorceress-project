#include "top_screen.h"

void InitTopScreen (void)
{
/////////////////////
/////TOP SCREEN//////
/////////////////////
    PA_LoadBackground( 1, 3, &fond_haut);
    PA_SetTextTileCol(1, 0);
    PA_OutputText(1,7,1,"Exp %d",sorc.stats.experience);
    PA_OutputText(1,20,1,"Next    %d",sorc.stats.nextlvl);
    PA_OutputText(1,20,2,"Level");
    PA_OutputText(1,1,5,"Force      %d",sorc.stats.force);
    PA_OutputText(1,1,8,"Dexterite  %d",sorc.stats.dexterite);
    PA_OutputText(1,1,11,"Vitalite   %d",sorc.stats.vitalite);
    PA_OutputText(1,1,14,"Energie    %d",sorc.stats.energie);
    PA_SetTextTileCol(1, 1);
    PA_OutputText(1,7,17,"%d",sorc.stats.resfire);
    PA_SetTextTileCol(1, 3);
    PA_OutputText(1,9,17,"%d",sorc.stats.resice);
    PA_SetTextTileCol(1, 6);
    PA_OutputText(1,11,17,"%d",sorc.stats.reslight);
    PA_SetTextTileCol(1, 2);
    PA_OutputText(1,13,17,"%d",sorc.stats.respsn);


    PA_SetTextTileCol(1, 0);
    PA_LoadSpritePal(1,0,(void*)lvlfont_Pal);
    PA_LoadSpritePal(1,1,(void*)vie_Pal);
    PA_LoadSpritePal(1,2,(void*)mana_Pal);
    PA_LoadSpritePal(1,3,(void*)sorts_Pal);

    PA_CreateSprite(1,0,(void*)lvlfont_Sprite,OBJ_SIZE_32X32,1,0,	20, 0);
    PA_CreateSprite(1,2,(void*)mana_Sprite,OBJ_SIZE_64X64,1,2,192,128);
    PA_CreateSprite(1,1,(void*)vie_Sprite,OBJ_SIZE_64X64,1,1,0,128);
    PA_CreateSprite(1,3,(void*)sorts_Sprite,OBJ_SIZE_32X32,1,3,	60, 160);
    PA_CreateSprite(1,4,(void*)sorts_Sprite,OBJ_SIZE_32X32,1,3,	164, 160);

    PA_SetSpriteAnim(1, 0, sorc.stats.lvl);
    PA_SetSpriteAnim(1, 3, 0);
    PA_SetSpriteAnim(1, 4, 8);
    PA_SetSpriteAnim(1, 2,sorc.stats.mana_restante*20/sorc.stats.mana_max);//mana=>ramene en x/20 pour les frames
    PA_SetSpriteAnim(1, 1, sorc.stats.vie_restante*20/sorc.stats.vie_max);//vie

}

void QuickTopScreenRefresh (void)
{

    PA_OutputText(1,15,17,"          ");

    //PA_OutputText(1,0,0,"%d",PA_RTC.FPS );

    PA_SetSpriteAnim(1, 2,sorc.stats.mana_restante*20/sorc.stats.mana_max);//mana=>ramene en x/20 pour les frames
    PA_SetSpriteAnim(1, 1, sorc.stats.vie_restante*20/sorc.stats.vie_max);//vie

}
