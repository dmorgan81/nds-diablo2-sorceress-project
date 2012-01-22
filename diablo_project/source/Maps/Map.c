//map.png
//Converti avec GBA Graphics par Brünni
//Map ("","map.til.c",0,ffffffff)
//Taille: 8*8 * 60*45
//Mémoire: 5400 octets

#include "../ulScreenDisplay.h"
#include "../uldata.h"
#include "../objects.h"
#include "../interface.h"
#include "Map.h"

int currentMap;
u16* map_col=NULL;
short *map=NULL;
bool loadmap(char* name,int sizemap,int sizecol);

void changemap(u8 mapnb)
{
    int i;
    switch(mapnb)
    {
    case 0:
        //map_col=tilescollision_map;
        ulDeleteImage(mapTiles);
        ulDeleteMap(Mymap);
        for (i=0; i<MAX_OBJECT; i++)
        {
            deleteobject(i);
        }
        for (i=0; i<MAX_BGOBJECT; i++)
        {
            deleteBgObject(i);
        }
        MAPSIZE_X=59;
        MAPSIZE_Y=47;
        curMaxObject=0;
        curMaxBgObject=0;
        hero.x=norm_fix(63);
        hero.y=norm_fix(5);
        currentMap=0;

        if(!loadmap("rogue",45*60,47*59))
            while(1)
            {
                ulStartDrawing2D();
                ulDrawTextBox(3,171,253,190,"Error loading map",0);
                ulEndDrawing();
                WaitForVBL();
            }
        mapTiles = ulLoadImageFilePNG((void*)map_png, (int)map_png_size, UL_IN_VRAM, UL_PF_PAL4);
        if(map!=NULL && map_col!=NULL)Mymap = ulCreateMap(mapTiles,/*Tileset*/map,8,8,/*Tiles size*/60,45,/*Map size*/UL_MF_U16);//Map format
        else while(1);//error


        if (hero.stats.lvl>=5)
        {
            int objectnb;
            objectnb=getUnusedBgObject();
            newObject((46<<3)+4, (39<<3)+8, &bgobjects[objectnb],objectnb, &bgdata[2] ,1);
            for (i=0; i<MAX_BGOBJECT; i++)
            {
                if(bgobjects[i].datanb==2)bgobjects[i].ai=&waypointmenu;
            }
        }
        SpawnObjects();
        break;


    case 1:
        ulDeleteImage(mapTiles);
        ulDeleteMap(Mymap);
        for (i=0; i<MAX_OBJECT; i++)
        {
            deleteobject(i);
        }
        for (i=0; i<MAX_BGOBJECT; i++)
        {
            deleteBgObject(i);
        }
        MAPSIZE_X=129;
        MAPSIZE_Y=102;
        curMaxObject=0;
        curMaxBgObject=0;

        if(!loadmap("sand",129*102,129*102))
            while(1)
            {
                ulStartDrawing2D();
                ulDrawTextBox(3,171,253,190,"Error loading map",0);
                ulEndDrawing();
                WaitForVBL();
            }
        mapTiles = ulLoadImageFilePNG((void*)dudu_png, (int)dudu_png_size, UL_IN_VRAM, UL_PF_PAL4);
        Mymap = ulCreateMap(mapTiles,/*Tileset*/map,8,8,/*Tiles size*/129,102,/*Map size*/UL_MF_U16);//Map format
        hero.x=norm_fix(240);
        hero.y=norm_fix(430);
        currentMap=1;
        for (i=0; i<MAX_BGOBJECT; i++)
        {
            if(bgobjects[i].datanb==2)bgobjects[i].ai=&waypointmenu;
        }
        SpawnObjects();

        break;
    }
    for (i=1; i<MAX_DATASPRITES; i++)
    {
        ulUnrealizeImage(spritedatabase[i].image);
    }
}


bool loadmap(char* name,int sizemap,int sizecol)
{
    FILE* file=NULL;
    char buffer[30];

    sprintf(buffer,"/maps/%s.map.bin",name);
    file=fopen(buffer, "rb");
    if(map!=NULL)free(map);
    map=malloc(sizemap*sizeof(short));
    if(map!=NULL && file!=NULL)fread(map,sizeof(short), sizemap, file);
    else return 0;
    fclose(file);

    sprintf(buffer,"/maps/%s.col.bin",name);
    if (map_col!=NULL)free(map_col);
    map_col=malloc(sizecol*sizeof(short));
    file=fopen(buffer, "rb");
    if(map_col!=NULL && file!=NULL)fread(map_col,sizeof(short), sizecol, file);
    else return 0;
    fclose(file);

    return 1;
}
