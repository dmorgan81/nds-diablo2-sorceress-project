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

extern s32 PA_VBLCounter[16]; // VBL counters
extern bool PA_VBLCounterOn[16]; // VBL counters enable/disable flag

inline void PA_VBLCounterStart(u8 nCounter);
inline void PA_VBLCounterPause(u8 nCounter);
inline void PA_VBLCounterUnpause(u8 nCounter);

void PA_VBLCountersReset();

inline void PA_RunCounters();

void WaitForVBL();
void UpdateRTC();

#endif
