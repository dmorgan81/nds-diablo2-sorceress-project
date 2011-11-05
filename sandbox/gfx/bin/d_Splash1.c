#include <PA_BgStruct.h>

extern const char d_Splash1_Tiles[];
extern const char d_Splash1_Map[];
extern const char d_Splash1_Pal[];

const PA_BgStruct d_Splash1 = {
	PA_BgNormal,
	256, 192,

	d_Splash1_Tiles,
	d_Splash1_Map,
	{d_Splash1_Pal},

	42112,
	{1536}
};
