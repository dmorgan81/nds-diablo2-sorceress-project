#ifndef _PA_Math
#define _PA_Math

#include "misc.h"

#define PA_Cos(angle) PA_SIN[((angle) + 128)&511]
#define PA_Sin(angle) PA_SIN[((angle))&511]



extern u32 RandomValue;  // Seed pour la fonction random
extern const s16 PA_SIN[512];
static inline u32 PA_Rand() {
	u32 lo, hi;
	lo = 16807 * (RandomValue & 0xFFFF);
	hi = 16807 * (RandomValue >> 16);
	lo += (hi & 0x7FFF) << 16;
	lo += hi >> 15;
	if (lo > 0x7FFFFFFF)
		lo -= 0x7FFFFFFF;
	RandomValue = lo;
	return(RandomValue);
}

// Les fonctions randoms sont prises de Ham, je n'ai strictement AUCUN mérite ! Désolé ! Je l'ai un peu modifiée, elle doit etre plus rapide
static inline void PA_InitRand() {
	RandomValue = 1 + MY_RTC.Seconds + MY_RTC.Minutes*60 + MY_RTC.Hour*3600 + MY_RTC.Day*3600*24+MY_RTC.Month*3600*24*30;
	PA_Rand(); PA_Rand(); PA_Rand(); // On fait plusieurs fois de base
}

// Les fonctions randoms sont prises de Ham, je n'ai strictement AUCUN m?rite ! D?sol? ! Je l'ai un peu modifi?e, elle doit etre plus rapide
static inline void PA_SRand(s32 r) {
	if ((r==-2)||(r==0)||(r==2147483647))
		RandomValue = 1;
	else
		RandomValue = r;
}

static inline u32 PA_RandMax(u32 max){
	return PA_Rand()%(max + 1);
}

static inline u32 PA_RandMinMax(u32 min,u32 max){
	return ((PA_Rand()%((max + 1)-min)) + min);
}

static inline u64 PA_Distance(s32 x1, s32 y1, s32 x2, s32 y2) {
   s64 h = x1 - x2;
   s64 v = y1 - y2;
   return(h*h + v*v);
}

static inline u64 PA_TrueDistance(s32 x1, s32 y1, s32 x2, s32 y2) {
   s64 h = x1 - x2;
   s64 v = y1 - y2;
   return(swiSqrt(h*h + v*v));
}


u16 PA_AdjustAngle(u16 angle, s16 anglerot, s32 startx, s32 starty, s32 targetx, s32 targety);

static inline u16 PA_GetAngle(s32 startx, s32 starty, s32 targetx, s32 targety) {
	u16 angle = 0;
	u16 anglerot = 180;

	while(anglerot > 5) {
		angle = PA_AdjustAngle(angle, anglerot, startx, starty, targetx, targety);
		anglerot = (anglerot - ((3 * anglerot) >> 3)); // On diminue petit ? petit la rotation...
	}

	// Ajustement encore plus précis...
	anglerot = 4;
	angle = PA_AdjustAngle(angle, anglerot, startx, starty, targetx, targety);
	anglerot = 2;
	angle = PA_AdjustAngle(angle, anglerot, startx, starty, targetx, targety);
	anglerot = 1;
	angle = PA_AdjustAngle(angle, anglerot, startx, starty, targetx, targety);

	return angle;
}

// fincs additions

/// Simple point structure.
typedef struct{
	/// X value.
	int x;
	/// Y value.
	int y;
}PA_Point;

int PA_mulf32(int a, int b);

int PA_divf32(int a, int b);

int PA_modf32(int a, int b);

int PA_sqrtf32(int a);

static inline s32 PA_Modulo(s32 var, s32 modulo){
	while(var < 0) var += modulo;
	return (var%modulo);
}

#ifdef __cplusplus
}
#endif

#endif


