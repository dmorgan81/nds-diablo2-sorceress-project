// Graphics converted using PAGfx by Mollusk.

#pragma once

#include <PA_BgStruct.h>

#ifdef __cplusplus
extern "C"{
#endif

// Sprites:
extern const unsigned char lvlfont_Sprite[10240] _GFX_ALIGN; // Palette: lvlfont_Pal
extern const unsigned char mana_Sprite[86016] _GFX_ALIGN; // Palette: mana_Pal
extern const unsigned char sorts_Sprite[9216] _GFX_ALIGN; // Palette: sorts_Pal
extern const unsigned char vie_Sprite[86016] _GFX_ALIGN; // Palette: vie_Pal

// Backgrounds:
extern const PA_BgStruct fond_haut;
extern const PA_BgStruct exocet;
extern const PA_BgStruct pasplash;
extern const PA_BgStruct d_Splash1;
extern const PA_BgStruct PA_TiledFont;

// Palettes:
extern const unsigned short lvlfont_Pal[256] _GFX_ALIGN;
extern const unsigned short mana_Pal[256] _GFX_ALIGN;
extern const unsigned short sorts_Pal[256] _GFX_ALIGN;
extern const unsigned short vie_Pal[256] _GFX_ALIGN;

#ifdef __cplusplus
}
#endif
