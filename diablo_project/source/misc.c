#include <nds.h>
#include <time.h>
#include <ulib/ulib.h>
#include "misc.h"

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
