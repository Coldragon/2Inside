#ifndef DEF_MAP
#define DEF_MAP
#include <stdio.h>

void file_go_to_char(FILE* fichier, int character);
void map_load(MAP *map, char *path);
int tile_on_this_pos(int x, int y, MAP *map);

#endif
