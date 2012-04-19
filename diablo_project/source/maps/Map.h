#ifndef _MAP_H
#define _MAP_H
#define currentMapStrLength 30
char currentMap[currentMapStrLength];
u16* map_col;
extern box spawnArea;
void changemap(char* mapname);

#endif
