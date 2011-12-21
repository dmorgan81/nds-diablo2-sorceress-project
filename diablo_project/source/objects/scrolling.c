#include "../objects.h"


extern objectdata data[MAX_DATA];
extern objectdata mdata[MAX_MDATA];
extern objectinfo objects[MAX_OBJECT];
extern objectinfo missiles[MAX_MISSILE];
extern fx_data fxdata[MAX_FXDATA];
extern fx_info fxinfo[MAX_FX];
extern aurainfo auras[MAX_AURAS];

extern bool objectused[MAX_OBJECT];
extern bool missileused[MAX_MISSILE];


void objectscroll(objectinfo* mover)
{

    //check if mover is onscreen
    if((fix_norm(mover->x-hero.x)+mover->hitbox.left.x<=256-CAMERA_X && fix_norm(mover->x-hero.x)+mover->hitbox.right.x >=-CAMERA_X)&&(fix_norm(mover->y-hero.y)+mover->hitbox.up.y<=192-CAMERA_Y && fix_norm(mover->y-hero.y)+mover->hitbox.down.y>=-CAMERA_Y))
    {
        //if it is then move it to the correct position
        if(mover->sprite!=-1)
        {
            myulSetSpriteXY(mover->sprite,fix_norm(mover->x-hero.x)+CAMERA_X,fix_norm(mover->y-hero.y)+CAMERA_Y);
        }
        //if it's not then create a sprite for it
        else
        {

            mover->sprite=myulCreateSprite(mover->spritedata, fix_norm(mover->x-hero.x)+CAMERA_X, fix_norm(mover->y-hero.y)+CAMERA_Y,fix_norm(mover->y-hero.y)+CAMERA_Y+mover->hitbox.down.y);
        }
        u8 columnaddaction;

        if (!mover->action)
        {
            myulSetAnim (mover->sprite,0,2,25,0);    //change
            columnaddaction= mover->action*5;
        }
        else
        {
            myulDefaultAnim(mover->sprite);    //change
            columnaddaction= (mover->action-1)*5;
        }

        switch (mover->dir)
        {
        case 0 :
            myulImageColumn (mover->sprite,columnaddaction);
            myulImageFlip(mover->sprite,0,0); mover->hitbox.flipped=0;

            break;

        case 1 :
            myulImageColumn (mover->sprite,1+columnaddaction);
            myulImageFlip(mover->sprite,0,0); mover->hitbox.flipped=0;
            break;

        case 2 :
            myulImageColumn (mover->sprite,2+columnaddaction);
            myulImageFlip(mover->sprite,0,0); mover->hitbox.flipped=0;
            break;

        case 3 :
            myulImageColumn (mover->sprite,3+columnaddaction);
            myulImageFlip(mover->sprite,0,0); mover->hitbox.flipped=0;
            break;

        case 4 :
            myulImageColumn (mover->sprite,4+columnaddaction);
            break;

        case 5 :
            myulImageColumn (mover->sprite,3+columnaddaction);
            myulImageFlip(mover->sprite,1,0); mover->hitbox.flipped=1;;
            break;

        case 6 :
            myulImageColumn (mover->sprite,2+columnaddaction);
            myulImageFlip(mover->sprite,1,0); mover->hitbox.flipped=1;;
            break;

        case 7 :
            myulImageColumn (mover->sprite,1+columnaddaction);
            myulImageFlip(mover->sprite,1,0); mover->hitbox.flipped=1;;
            break;

        }



        //s16 y = myulGetSpriteY(mover->sprite)+mover->hitbox.down.y;
        myulmyulSetSpritePrio(mover->sprite,myulGetSpriteY(mover->sprite)+mover->hitbox.down.y);
        myulSetSpriteColor(mover->sprite,mover->color);

    }

    //if the object is offscreen delete it
    else
    {
        //don't delete already gone stuff
        if(mover->sprite!=-1)
        {
            myulDeleteSprite(mover->sprite);
            mover->sprite=-1;
        }
    }



    if (mover->fx[0] != -1)
    {

        (fxinfo[mover->fx[0]].scroll)(mover,0);
        if (mover->fx[1] != -1)
        {
            (fxinfo[mover->fx[1]].scroll)(mover,1);
        }

    }
}

void ScrollFXonly(objectinfo* mover)
{
    if (mover->fx[0] != -1)
    {

        (fxinfo[mover->fx[0]].scroll)(mover,0);
        if (mover->fx[1] != -1)
        {
            (fxinfo[mover->fx[1]].scroll)(mover,1);
        }

    }
}


void onemDirScroll(objectinfo* mover)
{

    //check if mover is onscreen
    if((fix_norm(mover->x-hero.x)+mover->hitbox.left.x<=256-CAMERA_X && fix_norm(mover->x-hero.x)+mover->hitbox.right.x >=-CAMERA_X)&&(fix_norm(mover->y-hero.y)+mover->hitbox.up.y<=192-CAMERA_Y && fix_norm(mover->y-hero.y)+mover->hitbox.down.y>=-CAMERA_Y))
    {
        //if it is then move it to the correct position
        if(mover->sprite!=-1)
        {
            myulSetSpriteXY(mover->sprite,fix_norm(mover->x-hero.x)+CAMERA_X,fix_norm(mover->y-hero.y)+CAMERA_Y);

        }
        //if it's not then create a sprite for it
        else
        {

            mover->sprite=myulCreateSprite(mover->spritedata, fix_norm(mover->x-hero.x)+CAMERA_X, fix_norm(mover->y-hero.y)+CAMERA_Y,fix_norm(mover->y-hero.y)+CAMERA_Y+mover->hitbox.down.y);
            if(mover->sprite!=-1)
            {

                myulImageColumn (mover->sprite,0);
                myulImageFlip(mover->sprite,0,0); mover->hitbox.flipped=0;
            }
        }
        //s16 y = myulGetSpriteY(mover->sprite)+mover->hitbox.down.y;
        myulmyulSetSpritePrio(mover->sprite,myulGetSpriteY(mover->sprite)+mover->hitbox.down.y+10);
        myulSetSpriteColor(mover->sprite,mover->color);

    }

    //if the object is offscreen delete it
    else
    {
        //don't delete already gone stuff
        if(mover->sprite!=-1)
        {
            myulDeleteSprite(mover->sprite);
            mover->sprite=-1;
        }
    }



    if (mover->fx[0] != -1)
    {

        (fxinfo[mover->fx[0]].scroll)(mover,0);
        if (mover->fx[1] != -1)
        {
            (fxinfo[mover->fx[1]].scroll)(mover,1);
        }

    }
}


void deadScroll(objectinfo* mover)
{
    //check if mover is onscreen
    if((fix_norm(mover->x-hero.x)+mover->hitbox.left.x<=256-CAMERA_X && fix_norm(mover->x-hero.x)+mover->hitbox.right.x >=-CAMERA_X)&&(fix_norm(mover->y-hero.y)+mover->hitbox.up.y<=192-CAMERA_Y && fix_norm(mover->y-hero.y)+mover->hitbox.down.y>=-CAMERA_Y))
    {
        //if it is then move it to the correct position
        if(mover->sprite!=-1)
        {
            myulSetSpriteXY(mover->sprite,fix_norm(mover->x-hero.x)+CAMERA_X,fix_norm(mover->y-hero.y)+CAMERA_Y);
        }
        //if it's not then create a sprite for it
        else
        {
            mover->sprite=myulCreateSprite(mover->spritedata, fix_norm(mover->x-hero.x)+CAMERA_X, fix_norm(mover->y-hero.y)+CAMERA_Y,fix_norm(mover->y-hero.y)+CAMERA_Y+mover->hitbox.down.y);
            if(mover->sprite!=-1)
            {
                myulImageColumn (mover->sprite,0);
                myulImageFlip(mover->sprite,0,0); mover->hitbox.flipped=0;
            }
            myulSetAnim (mover->sprite,spritedatabase[mover->spritedata].nbframe-1,spritedatabase[mover->spritedata].nbframe-1,0,1);

        }
        myulSetSpriteColor(mover->sprite,mover->color);
        myulmyulSetSpritePrio(mover->sprite,myulGetSpriteY(mover->sprite)+mover->hitbox.down.y);
    }

    //if the object is offscreen delete it
    else
    {
        //don't delete already gone stuff
        if(mover->sprite!=-1)
        {
            myulDeleteSprite(mover->sprite);
            mover->sprite=-1;
        }
    }



    if (mover->fx[0] != -1)
    {

        (fxinfo[mover->fx[0]].scroll)(mover,0);
        if (mover->fx[1] != -1)
        {
            (fxinfo[mover->fx[1]].scroll)(mover,1);
        }

    }
}

void missilescroll(objectinfo* mover)
{

    //check if mover is onscreen
    if((fix_norm(mover->x-hero.x)+mover->hitbox.left.x<=256-CAMERA_X && fix_norm(mover->x-hero.x)+mover->hitbox.right.x >=-CAMERA_X)
            &&(fix_norm(mover->y-hero.y)+mover->hitbox.up.y<=192-CAMERA_Y && fix_norm(mover->y-hero.y)+mover->hitbox.down.y>=-CAMERA_Y))
    {
        //if it is then move it to the correct position
        if(mover->sprite!=-1)
        {
            myulSetSpriteXY(mover->sprite,fix_norm(mover->x-hero.x)+CAMERA_X,fix_norm(mover->y-hero.y)+CAMERA_Y);

        }
        //if it's not then create a sprite for it
        else
        {

            mover->sprite=myulCreateSprite(mover->spritedata, fix_norm(mover->x-hero.x)+CAMERA_X, fix_norm(mover->y-hero.y)+CAMERA_Y,fix_norm(mover->y-hero.y)+CAMERA_Y+mover->hitbox.down.y);
        }

        u8 columnaddaction;
        if (mover->action>0) columnaddaction= (mover->action-1)*5;
        else columnaddaction= 0;
        switch (mover->dir)
        {
        case 0 :
            myulImageColumn (mover->sprite,columnaddaction);
            myulImageFlip(mover->sprite,0,0); mover->hitbox.flipped=0;
            break;

        case 1 :
            myulImageColumn (mover->sprite,1+columnaddaction);
            myulImageFlip(mover->sprite,0,0); mover->hitbox.flipped=0;
            break;

        case 2 :
            myulImageColumn (mover->sprite,2+columnaddaction);
            myulImageFlip(mover->sprite,0,0); mover->hitbox.flipped=0;
            break;

        case 3 :
            myulImageColumn (mover->sprite,3+columnaddaction);
            myulImageFlip(mover->sprite,0,0); mover->hitbox.flipped=0;
            break;

        case 4 :
            myulImageColumn (mover->sprite,4+columnaddaction);
            myulImageFlip(mover->sprite,0,0); mover->hitbox.flipped=0;
            break;

        case 5 :
            myulImageColumn (mover->sprite,3+columnaddaction);
            myulImageFlip(mover->sprite,0,1);
            break;

        case 6 :
            myulImageColumn (mover->sprite,2+columnaddaction);
            myulImageFlip(mover->sprite,0,1);
            break;

        case 7 :
            myulImageColumn (mover->sprite,1+columnaddaction);
            myulImageFlip(mover->sprite,0,1);
            break;

        case 8 :
            myulImageColumn (mover->sprite,columnaddaction);
            myulImageFlip(mover->sprite,0,1);
            break;

        case 9 :
            myulImageColumn (mover->sprite,1+columnaddaction);
            myulImageFlip(mover->sprite,1,1); mover->hitbox.flipped=1;
            break;


        case 10 :
            myulImageColumn (mover->sprite,2+columnaddaction);
            myulImageFlip(mover->sprite,1,1); mover->hitbox.flipped=1;
            break;

        case 11 :
            myulImageColumn (mover->sprite,3+columnaddaction);
            myulImageFlip(mover->sprite,1,1); mover->hitbox.flipped=1;
            break;

        case 12 :
            myulImageColumn (mover->sprite,4+columnaddaction);
            myulImageFlip(mover->sprite,1,0); mover->hitbox.flipped=1;;
            break;

        case 13 :
            myulImageColumn (mover->sprite,3+columnaddaction);
            myulImageFlip(mover->sprite,1,0); mover->hitbox.flipped=1;;
            break;

        case 14 :
            myulImageColumn (mover->sprite,2+columnaddaction);
            myulImageFlip(mover->sprite,1,0); mover->hitbox.flipped=1;;
            break;

        case 15 :
            myulImageColumn (mover->sprite,1+columnaddaction);
            myulImageFlip(mover->sprite,1,0); mover->hitbox.flipped=1;;
            break;
        }

        //s16 y = myulGetSpriteY(mover->sprite)+mover->hitbox.down.y;
        myulmyulSetSpritePrio(mover->sprite,myulGetSpriteY(mover->sprite)+mover->hitbox.down.y+10);


    }

    //if the object is offscreen delete it
    else
    {
        //don't delete already gone stuff
        if(mover->sprite!=-1)
        {
            myulDeleteSprite(mover->sprite);
            mover->sprite=-1;
        }
    }



    if (mover->fx[0] != -1)
    {

        (fxinfo[mover->fx[0]].scroll)(mover,0);
        if (mover->fx[1] != -1)
        {
            (fxinfo[mover->fx[1]].scroll)(mover,1);
        }

    }
}

void FXscroll(objectinfo* mover, bool nb)
{

    //check if fx is onscreen
    if((fix_norm(mover->x-hero.x) + fxinfo[ mover->fx[nb] ].x + fxinfo[ mover->fx[nb] ].hitbox.left.x<=256-CAMERA_X && fix_norm(mover->x-hero.x) + fxinfo[ mover->fx[nb] ].x + fxinfo[ mover->fx[nb] ].hitbox.right.x >=-CAMERA_X)
            &&(fix_norm(mover->y-hero.y) + fxinfo[ mover->fx[nb] ].y + fxinfo[ mover->fx[nb] ].hitbox.up.y<=192-CAMERA_Y && fix_norm(mover->y-hero.y) + fxinfo[ mover->fx[nb] ].y + fxinfo[ mover->fx[nb] ].hitbox.down.y>=-CAMERA_Y))
    {
        //if it is then move it to the correct position
        if(fxinfo[ mover->fx[nb] ].sprite!=-1)
        {
            myulSetSpriteXY(fxinfo[ mover->fx[nb] ].sprite,fix_norm(mover->x-hero.x) + fxinfo[ mover->fx[nb] ].x + CAMERA_X,fix_norm(mover->y-hero.y) + fxinfo[ mover->fx[nb] ].y + CAMERA_Y);
            myulImageFlip (fxinfo[ mover->fx[nb] ].sprite, fxinfo[mover->fx[nb]].flippedh,fxinfo[mover->fx[nb]].flippedv);
        }
        //if it's not then create a sprite for it
        else
        {
            fxinfo[ mover->fx[nb] ].sprite=myulCreateSprite(fxinfo[ mover->fx[nb] ].spritedata, fix_norm(mover->x-hero.x) + fxinfo[ mover->fx[nb] ].x + CAMERA_X, fix_norm(mover->y-hero.y)+ fxinfo[ mover->fx[nb] ].y + CAMERA_Y,fix_norm(mover->y-hero.y)+ fxinfo[ mover->fx[nb] ].y + CAMERA_Y + fxinfo[ mover->fx[nb] ].hitbox.down.y);
            myulImageFlip (fxinfo[ mover->fx[nb] ].sprite, fxinfo[mover->fx[nb]].flippedh,fxinfo[mover->fx[nb]].flippedv);
        }
        /*
                s16 y = myulGetSpriteY(fxinfo[ mover->fx[nb] ].sprite)-fxinfo[mover->fx[nb]].y+mover->hitbox.down.y;
                if (y<1) y=1;*/   /// to use if the point.down.y of object isnt the same as the fx
        myulmyulSetSpritePrio(fxinfo[ mover->fx[nb] ].sprite,myulGetSpriteY(fxinfo[ mover->fx[nb] ].sprite)-fxinfo[mover->fx[nb]].y+mover->hitbox.down.y);



    }

    //if the object is offscreen delete it
    else
    {
        //don't delete already gone stuff
        if(fxinfo[ mover->fx[nb] ].sprite!=-1)
        {
            myulDeleteSprite(fxinfo[ mover->fx[nb] ].sprite);
            fxinfo[ mover->fx[nb] ].sprite=-1;
        }
    }
}
