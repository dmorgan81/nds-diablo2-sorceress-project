#include <nds.h>
#include <filesystem.h>
#include <ulib/ulib.h>			// Include for µLib
#include "soundbank.h"
#include "sound.h"
#include "misc.h"
#include "defines.h"

FILE* streamfile=0;
long streamFileSize=0;
long streamLoaded=0;
void initSounds()
{
    int i;
    bool soundsToLoad[MSL_NSAMPS];
    for (i=0; i<MSL_NSAMPS; i++)soundsToLoad[i]=1;
    //soundsToLoad[SFX_TYR_INTRO]=0;//dont load this dialog
    soundsToLoad[SFX_DEATH]=0;
    mmInitDefault( "soundbank.bin"); //(mm_addr)soundbank_bin );
    //use soundbank from filesystem, you have to create it with mmutils (or change the makefile)
    for (i=0; i<MSL_NSAMPS; i++)
    {
        if(soundsToLoad[i])mmLoadEffect(i);    //loads all sfx
    }
    for (i=0; i<MSL_NSONGS; i++)mmLoad(i); //loads all songs
    Counter[TALKING]=61;
}

bool initStream(char* rawfile)
{
    mystream.buffer_length = 1024;
    mystream.callback = stream;
    mystream.timer  = MM_TIMER0;
    mystream.manual = true;
    streamfile = fopen(rawfile,"rb");
    streamFileSize=0;
    streamLoaded=0;
    if (streamfile)
    {
        fseek(streamfile, 0, SEEK_END);
        streamFileSize = ftell(streamfile);
        fseek(streamfile, 0, SEEK_SET);
        mystream.sampling_rate = 22050;
        mystream.format = MM_STREAM_16BIT_MONO;
        mmStreamOpen(&mystream);
        mmStreamUpdate();
        return 1;
    }
    return 0;
}
void closeStream()
{
    if(streamfile)
    {
        mmStreamClose();
        fclose(streamfile);
    }
}


mm_word stream(mm_word length, mm_addr dest, mm_stream_formats format)
{
    if(streamfile)
    {
        size_t samplesize=0;
        switch(format)
        {
        case MM_STREAM_8BIT_MONO:
            samplesize = 1;
            break;
        case MM_STREAM_8BIT_STEREO:
            samplesize = 2;
            break;
        case MM_STREAM_16BIT_MONO:
            samplesize = 2;
            break;
        case MM_STREAM_16BIT_STEREO:
            samplesize = 4;
            break;
        }
        int res=0;
        //test is we will not try to copy somthing out of the file... Seems that nitrofs allows reading farther than the length of the file
        if(streamFileSize<(streamLoaded+length*samplesize))length%=streamFileSize-streamLoaded;
        else res = fread(dest,samplesize,length,streamfile);
        if(res)
        {
            length = res;
        }
        else
        {
            mmStreamClose();
            fclose(streamfile);
            length = 0;
        }
        streamLoaded+=length*samplesize;
    }
    return length;
}


