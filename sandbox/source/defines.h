#ifndef _DEFINES_H
#define _DEFINES_H
/////////////////
/////////////////
/////Defines/////
/////////////////
/////////////////
//#define Test
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
#define VITESSE				256
#define VITESSE2			181
#define CAMERA_X        	112
#define CAMERA_Y	        60
#define CHARMID_X           128
#define CHARMID_Y           86
#define CHARFEET_X           128
#define CHARFEET_Y           107

#define BGOBJ_AB            20
#define NWALKABLETILE       3
#define TILENB              6
//#define MAPSIZE_X           59 //size in number of tiles
//#define MAPSIZE_Y           47
int MAPSIZE_X; //no more a define, we have more than one map
int MAPSIZE_Y;

#define MAXDATA				6
#define MAX_DATASPRITES     15
#define MAXM_DATA			6
#define MAX_OBJECT			300
#define MAX_MISSILE			150
#define MAX_FX 				200
#define MAX_FXDATA 			9
#define MAX_SPRITES 		450
#define MAX_AURAS           1

#define S_COLD              1

#endif
