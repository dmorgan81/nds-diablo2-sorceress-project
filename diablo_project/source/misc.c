#include <nds.h>
#include <time.h>
#include <ulib/ulib.h>
#include "misc.h"
#include "top_screen.h"
#include "ulScreenDisplay.h"
s32 Counter[16]; // VBL counters
bool CounterOn[16]; // VBL counters enable/disable flag

void WaitForVBL()
{
    UpdateRTC();
    ulReadKeys(0);
    PA_RunCounters();
    ulSyncFrame();
    ulEndFrame();
}
void UpdateRTC()
{
    time_t unixTime = time(NULL);
    struct tm* RTCV = gmtime((const time_t *) & unixTime);
    MY_RTC.Seconds = RTCV->tm_sec;
    MY_RTC.Minutes = RTCV->tm_min;
    MY_RTC.Hour = RTCV->tm_hour;
    MY_RTC.Day = RTCV->tm_mday;
    MY_RTC.Month = RTCV->tm_mon + 1;
    MY_RTC.Year = 1900 + RTCV->tm_year;
}

inline void CounterStart(u8 nCounter)
{
    Counter[nCounter]   = 0;
    CounterOn[nCounter] = 1;
}
inline void CounterPause(u8 nCounter)
{
    CounterOn[nCounter] = 0;
}
inline void CounterUnpause(u8 nCounter)
{
    CounterOn[nCounter] = 1;
}

void CountersReset()
{
    register int i;
    for (i = 0; i < 16; i++)
    {
        Counter[i] = 0; // Ready to start
        CounterOn[i] = 0;  // Not counting yet
    }
}

inline void PA_RunCounters()
{
    register int i;
    for(i = 0; i < 16; i++)
        Counter[i] += CounterOn[i];
}

void MySplash()
{
    s32 time=180;
    topDrawBlackScreen();
    myulDrawBlackScreen();

    topSetBackground("d_Splash1");
    swiWaitForVBlank();
    topSetBackground("d_Splash1");
    ulShowSplashScreen(3);
    UL_IMAGE* d_splash2 = ulLoadImageFilePNG("/gfx/d_Splash2_png.png",0, UL_IN_RAM, UL_PF_PAL8);
    ulStartDrawing2D();
    ulDrawImage(d_splash2);
    ulEndDrawing();

    //wait 3seconds or press key
    while(time>0 && !(ul_keys.pressed.value || ul_keys.touch.click))
    {
        time--;
        WaitForVBL();
    }
    UL_IMAGE* loadingimg = ulLoadImageFilePNG("/gfx/loading_png.png",0, UL_IN_RAM, UL_PF_PAL8);
    loadingimg->x=32;
    //loading frame 0
    ulSetImageTileSize (loadingimg, 0, 0, 192, 192);
    ulStartDrawing2D();
    ulDrawImage(loadingimg);
    ulEndDrawing();
    ulDeleteImage (loadingimg);
    ulDeleteImage (d_splash2);
}


