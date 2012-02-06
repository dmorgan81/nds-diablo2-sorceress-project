#include <PA_BgStruct.h>

extern const char exocet_Tiles[];
extern const char exocet_Map[];
extern const char exocet_Pal[];

const PA_BgStruct exocet = {
	PA_BgNormal,
	256, 192,

	exocet_Tiles,
	exocet_Map,
	{exocet_Pal},

	4288,
	{1536}
};
