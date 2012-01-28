#ifndef _SOUND_H
#define _SOUND_H
#include <maxmod9.h>

void initSounds();
#define playSound(x)    mmEffect(x)
#define stopSound(x)    mmEffectCancel(x)
#define loadSound(x)    mmLoadEffect(x)
#define unloadSound(x)  mmUnloadEffect(x)
#endif // _SOUND_H
