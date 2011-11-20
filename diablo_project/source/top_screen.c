#include "top_screen.h"

void InitTopScreen (void)
{
/////////////////////
/////TOP SCREEN//////
/////////////////////
    PA_LoadBackground( 1, 3, &fond_haut);
    PA_SetTextTileCol(1, 0);
    PA_OutputText(1,7,1,"Exp %d",hero.stats.experience);
    PA_OutputText(1,20,1,"Next    %d",hero.stats.nextlvl);
    PA_OutputText(1,20,2,"Level");
    PA_OutputText(1,1,5,"Force      %d",hero.stats.force);
    PA_OutputText(1,1,8,"Dexterite  %d",hero.stats.dexterite);
    PA_OutputText(1,1,11,"Vitalite   %d",hero.stats.vitalite);
    PA_OutputText(1,1,14,"Energie    %d",hero.stats.energie);
    PA_SetTextTileCol(1, 1);
    PA_OutputText(1,7,17,"%d",hero.stats.resfire);
    PA_SetTextTileCol(1, 3);
    PA_OutputText(1,9,17,"%d",hero.stats.resice);
    PA_SetTextTileCol(1, 6);
    PA_OutputText(1,11,17,"%d",hero.stats.reslight);
    PA_SetTextTileCol(1, 2);
    PA_OutputText(1,13,17,"%d",hero.stats.respsn);


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

    PA_SetSpriteAnim(1, 0, hero.stats.lvl);
    PA_SetSpriteAnim(1, 3, 0);
    PA_SetSpriteAnim(1, 4, 8);
    PA_SetSpriteAnim(1, 2,hero.stats.mana_restante*20/hero.stats.mana_max);//mana=>ramene en x/20 pour les frames
    PA_SetSpriteAnim(1, 1, hero.stats.vie_restante*20/hero.stats.vie_max);//vie

}

void QuickTopScreenRefresh (void)
{

    //PA_OutputText(1,15,17,"          ");

    //PA_OutputText(1,0,0,"%d",PA_RTC.FPS );
    PA_OutputText(1,7,1,"Exp %d",hero.stats.experience);
    PA_SetSpriteAnim(1, 2,hero.stats.mana_restante*20/hero.stats.mana_max);//mana=>ramene en x/20 pour les frames
    PA_SetSpriteAnim(1, 1, hero.stats.vie_restante*20/hero.stats.vie_max);//vie

}
