#include "hdr/ai.h"
#include "hdr/projectile.h"
#include "hdr/sound.h"

void hack_terminal(CORE *game)
{
	for(int i = 1; i<game->entitysystem->tofill; i++)
		if (game->entitysystem->entity[i].identity == 1)
		{
			if (distancepoint(game->entitysystem->entity[0].x, game->entitysystem->entity[0].y, game->entitysystem->entity[i].x, game->entitysystem->entity[i].y) <= 20)
			{
				game->entitysystem->entity[i].is_hacking=1;
				game->entitysystem->entity[i].accumulator++;
				if (game->entitysystem->entity[i].accumulator > 200)
					hack_complete(game, &game->entitysystem->entity[i]);

			}
			else
			{
				game->entitysystem->entity[i].accumulator = 0;
				if (game->entitysystem->entity[i].is_hacking)
				{
					chunk_play(game->soundsystem, 5, 20);
					game->entitysystem->entity[i].is_hacking = 0;
				}

			}

			if(game->entitysystem->entity[i].accumulator == 1)
			{
				chunk_play(game->soundsystem, 4, 20);
			}
		}
			
			
}

void hack_complete (CORE *game, ENTITY *terminal)
{
	game->score += 50;
	game->timer_life += 7000;

	terminal->identity = 3;
	
	const int tile_nb_x = (terminal->x + (MAP_WIDTH / 2 * TCASE)) / TCASE;
	const int tile_nb_y = (terminal->y + (MAP_HEIGHT / 2 * TCASE)) / TCASE;
	game->map->tile[tile_nb_y][tile_nb_x] = 3;
	game->map->tile[tile_nb_y+1][tile_nb_x] = 3;
	game->map->tile[tile_nb_y - 1][tile_nb_x] = 3;
	game->map->tile[tile_nb_y][tile_nb_x+1] = 3;
	game->map->tile[tile_nb_y][tile_nb_x -1] = 3;
	game->nb_term_hacked++;
	chunk_play(game->soundsystem, 3, 20);
	TextureFree(terminal->texture);
	terminal->texture = TextureCreate(game->render, "res/img/terminal._hacked.png", 255,0,255,255);

}


