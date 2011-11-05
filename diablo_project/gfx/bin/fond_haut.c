#include <PA_BgStruct.h>

extern const char fond_haut_Tiles[];
extern const char fond_haut_Map[];
extern const char fond_haut_Pal[];

const PA_BgStruct fond_haut = {
	PA_BgNormal,
	256, 192,

	fond_haut_Tiles,
	fond_haut_Map,
	{fond_haut_Pal},

	42624,
	{1536}
};
