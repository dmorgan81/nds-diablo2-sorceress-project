#ifndef _MISC_H
#define _MISC_H

#include <nds.h>
struct
{
    u16 Year;
    u8 Month;
    u8 Day;
    u8 Hour;
    u8 Minutes;
    u8 Seconds;
//	u8 FPS, Frames, OldSeconds; // To test the FPS...
} MY_RTC;

extern s32 Counter[16]; // VBL counters
extern bool CounterOn[16]; // VBL counters enable/disable flag

inline void CounterStart(u8 nCounter);
inline void CounterPause(u8 nCounter);
inline void CounterUnpause(u8 nCounter);

void CountersReset();

inline void PA_RunCounters();

void WaitForVBL();
void UpdateRTC();

#endif
