#ifndef _STRUCTURES_H
#define _STRUCTURES_H
#include <ulib/ulib.h>

typedef struct objectinfo objectinfo;
typedef struct objectdata objectdata;

typedef struct pointinfo pointinfo;
typedef struct hitboxinfo hitboxinfo;
typedef struct frame frame;
typedef struct statistiques statistiques;
typedef struct charstruct charstruct;
typedef struct spriteinfo spriteinfo;
typedef struct spritedata spritedata;
typedef struct spritestruct spritestruct;

typedef struct fx_info fx_info;
typedef struct fx_data fx_data;

typedef struct aurainfo aurainfo;

extern charstruct hero;

struct aurainfo
{
    void (*fonction)(aurainfo*);
    int life;
    int variable;
};

struct pointinfo
{
    s8 x, y, flipx;
};

struct hitboxinfo
{
    pointinfo left, right, up, down, middle;
    u8 flipped;
};

struct frame
{
    u8 start, end;
    bool flipped;
};

struct statistiques
{
    u8 force;
    u8 dexterite;
    u8 vitalite;
    u8 energie;
    u8 lvl ;


    s8 resfire;
    s8 resice;
    s8 reslight;
    s8 respsn;

    u16 vie_max;
    u16 vie_restante;
    u16 mana_max;
    u16 mana_restante;
    u16 dmg;

    u32 experience;
    u32 nextlvl;

}  ;




struct objectinfo
{
    void (*ai)(objectinfo*);
    void (*scroll)(objectinfo*);
    void (*collision)(objectinfo*);

    u8 spritedata; //numero data sprite
    u8 lastdir,dir,status;
    u8 datanb;

    s8 action,lastaction;
    u16 color;
    s16 fx[2];

    bool update;
    int arrayID;
    int x,y,cd;
    int life,level,exp;
    s16 sprite; //numero sprite system(info)
    s16 vx, vy;
    s16 angle;
    s16 variables;
    s16 dommages;
    hitboxinfo hitbox;
};


struct objectdata
{
    void (*ai)(objectinfo*);
    void (*scroll)(objectinfo*);
    void (*collision)(objectinfo*);
    frame frames_dir[25];
    int life,exp;
    s16 dommages;
    s16 vx, vy;
    u8 tile,status;//dont need negative, 0 is enough because its basic tile so wont be called in spawn function
    u8 spritedata,deathspritedata; //numero data sprite
    u8 datanb;
    s8 fxdata[2]; //numero data des FX, -1 signifie pas de fx
    s8 variables;

    hitboxinfo hitbox;


};

struct fx_info
{
    void (*scroll)(objectinfo*, bool);
    s16 sprite;
    u8 spritedata; //numero data sprite
    bool used,flippedh,flippedv;
    s8 x,y;
    hitboxinfo hitbox;
};

struct fx_data
{
    void (*scroll)(objectinfo*, bool);
    u8 spritedata; //numero data sprite
    bool used,flippedh,flippedv;
    s8 x,y;
    hitboxinfo hitbox;
};


struct spritedata
{
    UL_IMAGE *image;
    u8 sizex, sizey;
    u8 nbframe, framerate;
    int abcoeff;
    hitboxinfo hitbox;

};

struct spritestruct
{

    u8 startframe, endframe, framerate, column;
    u16 color;
    int sprite;//data number
    int x,y,midx,midy,prio,abcoeff;//,angle;
    int animStage, frameNumber;

    bool /*alphablended,*/ flippedh,flippedv, used;

};

struct charstruct
{
    int x,y,lastx,lasty;
    u16 vitesse, vitesse2;
    u8 action, stop_action, direction, skillperiod, cooldown, sprite;
    statistiques stats;
    hitboxinfo hitbox;
};
#endif
