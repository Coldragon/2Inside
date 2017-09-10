#include "hdr/spawner.h"
#include "hdr/struct.h"
#include "hdr/entity.h"
#include <stdlib.h>
#include <stdio.h>

void spawn_terminal(MAP *map, CORE *game)
{
	for (int i=0; i < 40; i++)
	{
		SDL_Rect rand_spawn ={0};
		do
		{
			rand_spawn.x = rand() % (100); rand_spawn.y = rand() % (100);
		} while (map->terminalspawner[rand_spawn.y][rand_spawn.x] != 21);

		create_entity(game, (rand_spawn.x*32)-1600+16, (rand_spawn.y * 32 )-1600+16, 0, 1,"res/img/terminal.png");
		map->terminalspawner[rand_spawn.y][rand_spawn.x] = 0;
	}
	printf("Terminal spawned\n");
}

void spawn_ennemies(MAP *map, CORE *game)
{
	for (int i = 0; i < 65; i++)
	{
		SDL_Rect rand_spawn = { 0 };
		do
		{
			rand_spawn.x = rand() % (100); rand_spawn.y = rand() % (100);
		} while (map->enmspawner[rand_spawn.y][rand_spawn.x] != 22);

		create_entity(game, (rand_spawn.x * 32) - 1600+16, (rand_spawn.y * 32) - 1600+16, 0, 2, "res/img/ennemy.png");
		map->enmspawner[rand_spawn.y][rand_spawn.x] = 0;

	}
	printf("Ennemies spawned\n");
}
