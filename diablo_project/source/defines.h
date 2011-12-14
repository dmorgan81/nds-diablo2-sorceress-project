#ifndef _DEFINES_H
#define _DEFINES_H
/////////////////
/////////////////
/////Defines/////
/////////////////
/////////////////

#define MUSIC_OFF

#define PATEXT_ALL_COL_WHITE	PA_SetTextCol(1,31,31,31);
#define PATEXT_ALL_COL_BLACK	PA_SetTextCol(screen, 0, 0, 0);
#define PATEXT_ALL_COL_GREY		PA_SetTextCol(screen, 22, 22, 22);
#define PATEXT_ALL_COL_BLUE		PA_SetTextCol(screen, 0, 0, 31);
#define PATEXT_ALL_COL_RED		PA_SetTextCol(screen, 31, 0, 0);



#define norm_fix(x)			((x)<<8)
#define fix_norm(x)			((x)>>8)
#define dir_angle(x)		(((x)<<6)-160)
#define angle_dir(x)		( ((x+160)&511)>>6 )
#define mdir_angle(x)		(((x)<<5)-144)
#define mangle_dir(x)		( ((x+144)&511)>>5 )
#define fix_mult(x,y)		(((x)*(y))>>8)
#define ratio_fix(x,y)		((256*(x))/(y))
#define fixed_fraction(x)	((x)&&0xff)
#define SOUND(x)            (SoundInfo){(u8*)x,(u32)x##_size,0,16384,127,64,false,0,0}

#define VITESSE				256
#define VITESSE2			181
#define CAMERA_X        	112
#define CAMERA_Y	        60
#define CHARMID_X           128
#define CHARMID_Y           86
#define CHARFEET_X          128
#define CHARFEET_Y          107

#define SKILLNUMBER         8
#define BGOBJ_AB            25
#define NWALKABLETILE       8
#define TILENB              16
#define VOIDTILE            10
//#define MAPSIZE_X           59 //size in number of tiles
//#define MAPSIZE_Y           47
int MAPSIZE_X; //no more a define, we have more than one map
int MAPSIZE_Y;

#define MAX_DATA			3
#define MAX_BGDATA			5
#define MAX_DATASPRITES     19
#define MAX_MDATA			6
#define MAX_OBJECT			100
#define MAX_BGOBJECT        100
#define MAX_MISSILE			100
#define MAX_FX 				200
#define MAX_FXDATA 			11
#define MAX_SPRITES 		300
#define MAX_AURAS           1



//status, bitmasks

#define S_ALARMED           1
#define S_ATTACKED          2
#define S_DEAD              4
#define S_COLD              8
#define S_FROZEN            16
#define S_INFIRE            32
#define S_POISONNED         64
#define S_STUNNED           128

#endif
