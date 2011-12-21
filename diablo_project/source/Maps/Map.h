#ifndef _MAP_H
#define _MAP_H

int currentMap;
u16* map_col;
extern const unsigned short map[45][60];
extern const unsigned short tilescollision_map[47][59];
extern const unsigned short dudu_map[102][129];
extern const unsigned short duducol_map[102][129];
void changemap(u8 mapnb,bool reset);
#endif
