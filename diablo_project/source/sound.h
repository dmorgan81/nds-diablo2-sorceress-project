#ifndef _SOUND_H
#define _SOUND_H
#include <maxmod9.h>

void initSounds();
#define playSound(x)    mmEffect(x)
#define stopSound(x)    mmEffectCancel(x)
#define loadSound(x)    mmLoadEffect(x)
#define unloadSound(x)  mmUnloadEffect(x)

#define streamUpdate() 		mmStreamUpdate()

struct Song{
	const mm_word rate;
	const mm_stream_formats format;
	const char* filename;
};
mm_stream mystream;
mm_word stream(mm_word length, mm_addr dest, mm_stream_formats format);
bool initStream(char* rawfile);
void closeStream();




#endif // _SOUND_H
