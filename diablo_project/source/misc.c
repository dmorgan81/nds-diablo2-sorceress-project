#include <nds.h>
#include <time.h>
#include <ulib/ulib.h>
#include "misc.h"

s32 PA_VBLCounter[16]; // VBL counters
bool PA_VBLCounterOn[16]; // VBL counters enable/disable flag

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

inline void PA_VBLCounterStart(u8 nCounter)
{
    PA_VBLCounter[nCounter]   = 0;
    PA_VBLCounterOn[nCounter] = 1;
}
inline void PA_VBLCounterPause(u8 nCounter)
{
    PA_VBLCounterOn[nCounter] = 0;
}
inline void PA_VBLCounterUnpause(u8 nCounter)
{
    PA_VBLCounterOn[nCounter] = 1;
}

void PA_VBLCountersReset()
{
    register int i;
    for (i = 0; i < 16; i++)
    {
        PA_VBLCounter[i] = 0; // Ready to start
        PA_VBLCounterOn[i] = 0;  // Not counting yet
    }
}

inline void PA_RunCounters()
{
    register int i;
    for(i = 0; i < 16; i++)
        PA_VBLCounter[i] += PA_VBLCounterOn[i];
}
