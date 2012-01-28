#include <nds.h>
#include "soundbank.h"
#include "soundbank_bin.h"
#include "sound.h"
#include "misc.h"
#include "defines.h"
void initSounds()
{
    int i;
    bool soundsToLoad[MSL_NSAMPS];
    for (i=0; i<MSL_NSAMPS; i++)soundsToLoad[i]=1;
    //soundsToLoad[SFX_TYR_INTRO]=0;//dont load this dialog
    soundsToLoad[SFX_DEATH]=0;
    mmInitDefaultMem( (mm_addr)soundbank_bin );
    for (i=0; i<MSL_NSAMPS; i++){if(soundsToLoad[i])mmLoadEffect(i);} //loads all sfx
    for (i=0; i<MSL_NSONGS; i++)mmLoad(i); //loads all songs
    Counter[TALKING]=61;
}

