#include "hdr/core.h"
#include "hdr/map.h"
#include <stdio.h>
#include "hdr/define.h"
#include "hdr/gui.h"


void file_go_to_char(FILE* fichier, int character)
{
	int charactuel = 0;
	do
	{
		charactuel = fgetc(fichier);
	} while (charactuel != character);
}

void map_load(MAP *map, char *path)
{
	FILE* fichier = fopen(path, "r");

	file_go_to_char(fichier, '[');
	file_go_to_char(fichier, '[');

	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			fscanf(fichier, "%hu,", &map->tile[i][j]);

	file_go_to_char(fichier, '[');

	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			fscanf(fichier, "%hu,", &map->terminalspawner[i][j]);

	file_go_to_char(fichier, '[');

	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			fscanf(fichier, "%hu,", &map->enmspawner[i][j]);
}

int tile_on_this_pos(int x, int y, MAP *map)
{
	const int tile_nb_x = (x + (MAP_WIDTH/2*TCASE))/TCASE;
	const int tile_nb_y = (y + (MAP_HEIGHT/2*TCASE))/TCASE;

	return map->tile[tile_nb_y][tile_nb_x];
}