#include <ulib/ulib.h>			// Include for µLib
#include <filesystem.h>

#include "../ulScreenDisplay.h"
#include "../defines.h"
#include "../misc.h"
#include "../top_screen.h"
#include "map.h"
#include "../sound.h"
char* WPactivated=NULL;//string containing names of activated waypoint

int curLineSize(char buffer[],int charPos)
{
    //doesnt count the '\n' character
    int i=0;
    while(buffer[i+charPos]!='\n')i++;
    return i;
}

bool isWaypointActivated(char* name)
{
    return strstr(WPactivated,name)!=NULL;
}

void activateWaypoint(char* name)
{
    char* buffer=NULL;
    buffer=malloc( (strlen(WPactivated)+strlen(name)+2)*sizeof(char) );
    if(buffer)
    {
        sprintf(buffer,"%s%s",WPactivated,name);
        if(WPactivated)free(WPactivated);
        WPactivated=buffer;
    }
}
void showWPMenu()
{
    WaitForVBL();
    myulUnrealizeSprites();
    myulDrawBlackScreen();

    VIRTUAL_FILE *f;
    f = VirtualFileOpen("/Exocet22.oft", 0, ul_loadUtilActiveSource, VF_O_READ);
    UL_FONT* exocet=NULL;
    if (f)
    {
        exocet=ulLoadFont(f);
        ulSetFont(exocet);
        VirtualFileClose(f);
    }
    UL_IMAGE *bg = ulLoadImageFilePNG("/gfx/waypointmenu_png.png",0, UL_IN_RAM, UL_PF_PAL8);
    UL_IMAGE *arrow = ulLoadImageFilePNG("/gfx/bigarrow_png.png",0,UL_IN_RAM,UL_PF_PAL4);
    UL_IMAGE *icon = ulLoadImageFilePNG("/gfx/waypointicon_png.png",0,UL_IN_RAM,UL_PF_PAL8);
    FILE* file=NULL;
    file=fopen("/maps/waypoints.dat","r");
    char buffer[300]= {0};
    char** mapNames=NULL;

    bool activated[5]= {0};


    int i=0,j=0,lines=0,page=0,curChar=0;
    bool menu=1;
    char c=1;
    //copy names of waypoints from file
    do
    {
        c=fgetc(file);
        switch (c)
        {
        case 13 :
            break;//remove "end of line" characters

        case 255 ://EOF
            buffer[i]='\0';
            i=300;
            break;

        case '\n':
            lines++;
        default:
            buffer[i++]=c;
            break;
        }
    }
    while(i<300);

    fclose(file);

    mapNames=malloc( sizeof(*mapNames) * lines);
    if(mapNames==NULL) ERROR("no more memory");
    else
    {

        for (i=0; i<lines; i++)
        {
            mapNames[i]=malloc( sizeof(char) * (curLineSize(buffer,curChar)+1) );
            if(mapNames[i])
            {
                for (j=0; j<curLineSize(buffer,curChar) ; j++ )
                {
                    mapNames[i][j]=buffer[curChar+j];
                }
                mapNames[i][j]='\0';//do not forget termination string value
            }
            curChar+=curLineSize(buffer,curChar)+1;
        }
#define checkActivated() for (i=0; i< (lines-5*page>=5 ? 5 : lines-5*page); i++ )\
        {\
            activated[i]=isWaypointActivated(mapNames[i+page*5]);\
        }
        checkActivated();
        while(menu)
        {
            ulStartDrawing2D();
            ulSetDepth(0);
            ulDrawImage(bg);
            ulSetDepth(1);

            for (i=0; i< (lines-5*page>=5 ? 5 : lines-5*page); i++ )  // if more than 5lines then draw only 5, else draw the right number of lines
            {
                if(!activated[i])ulSetTextColor(RGB15(20,20,20));
                else
                {
                    icon->x=13;
                    icon->y=3+29*i;
                    if(strcmp(mapNames[i+page*5],currentMap))ulSetImageTileSize(icon,0,0,26,26);
                    else ulSetImageTileSize(icon,0,26,26,26);
                    ulDrawImage(icon);
                }
                ulDrawTextBox(40,2+29*i,242,30+29*i,mapNames[i+page*5],0);
                ulSetTextColor(RGB15(31,31,31));
            }
            ulSetDepth(2);

            //draw previous/next page arrows
            #define ARROWS_Y    151
            #define ARROWB_X    4
            #define ARROWF_X    34

            arrow->y=ARROWS_Y;
            //previous page arrow
            if(page==0)glPolyFmt(POLY_ALPHA(20) | POLY_CULL_NONE | POLY_ID(0));//fade arrow if unusable
            else glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_ID(0));
            arrow->x=ARROWB_X;
            ulMirrorImageH(arrow,0);
            ulDrawImage(arrow);
            //next page arrow
            if((lines-5*(page+1))<=0)glPolyFmt(POLY_ALPHA(20) | POLY_CULL_NONE | POLY_ID(1));//fade arrow if unusable
            else glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_ID(1));
            arrow->x=ARROWF_X;
            ulMirrorImageH(arrow,1);
            ulDrawImage(arrow);
            glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_ID(2));


            //check for selection
            if(ul_keys.touch.click)
            {
                //display menu and check if need to change map
                for (i=0; i< (lines-5*page>=5 ? 5 : lines-5*page); i++ )
                {
                    if(STYLUSBOX(13,3+29*i,232,25))
                    {
                        if(activated[i])
                        {
                            changemap(mapNames[i+page*5]);
                            i=5;//end for statement
                            menu=0;//quit menu
                        }
                        else if (Counter[TALKING]>60) //this waypoint isnt activated, and so cant use it
                        {
                            CounterStart(TALKING);
                            playSound(SFX_SOR_CANTUSEYET);
                        }

                    }
                }
                if(STYLUSBOX(218,149,26,26)) menu=0;        //quit menu icon
                if(STYLUSBOX(ARROWB_X,ARROWS_Y,26,30) && page !=0) //previous page
                {
                    page--;
                    checkActivated();
                }
                if(STYLUSBOX(ARROWF_X,ARROWS_Y,26,30) && (lines-5*(page+1))>0) //next page
                {
                    page++;
                    checkActivated();
                }

            }
            ulEndDrawing();
            WaitForVBL();
        }

        for (i=0; i<lines; i++)
        {
            if(mapNames[i] != NULL )free(mapNames[i]);
        }
        free(mapNames);
    }
    ulDeleteImage(bg);
    ulDeleteImage(arrow);
    ulDeleteImage(icon);
    ulSetFont(ul_lcdFont);
    ulDeleteFont(exocet);

    myulDrawBlackScreen();
}

