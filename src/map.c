#include "hdr/core.h"
#include <stdio.h>

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
	printf("%s \n", path);

	file_go_to_char(fichier, '[');
	file_go_to_char(fichier, '[');

	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			fscanf(fichier, "%hu,", &map->water[i][j]);

	file_go_to_char(fichier, '[');

	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			fscanf(fichier, "%hu,", &map->sol[i][j]);
}