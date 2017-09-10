#include "hdr/ennemy.h"
#include "hdr/projectile.h"
#include "hdr/camera.h"
#include "hdr/sound.h"
#include "hdr/map.h"

void ennemy_aim(CORE* game)
{
	for (int i = 1; i < game->entitysystem->tofill; i++)
	{
		if (game->entitysystem->entity[i].identity == 2)
			if (1000 > distancepoint(game->entitysystem->entity[i].x, game->entitysystem->entity[i].y, game->entitysystem->entity[0].x, game->entitysystem->entity[0].y))
			{
				game->entitysystem->entity[i].angle = 180 + angle_calculate_degree(game->entitysystem->entity[i].x, game->entitysystem->entity[i].y, game->entitysystem->entity[0].x, game->entitysystem->entity[0].y);

			}
	}
}

void ennemy_attack(CORE* game)
{
	for (int i = 1; i < game->entitysystem->tofill; i++)
	{
		if (game->entitysystem->entity[i].identity == 2 && game->entitysystem->entity[i].exist)
		{
			game->entitysystem->entity[i].attacktimer.ticks = 800;
			game->entitysystem->entity[i].attacktimer.actual = SDL_GetTicks();

			if (1000 > distancepoint(game->entitysystem->entity[i].x, game->entitysystem->entity[i].y, game->entitysystem->entity[0].x, game->entitysystem->entity[0].y))
				if (game->entitysystem->entity[i].attacktimer.actual - game->entitysystem->entity[i].attacktimer.last > game->entitysystem->entity[i].attacktimer.ticks) // if the ticks ellapsed is superiore to the ticks for a frame it run the loop
				{
					create_projectile(game->projectilesystem, game->entitysystem->entity[i], game->entitysystem->entity[0].x, game->entitysystem->entity[0].y, 1, 1);
					//chunk_play(game->soundsystem, 0, 10);
					game->entitysystem->entity[i].attacktimer.last = game->entitysystem->entity[i].attacktimer.actual;
				}

		}
	}
}

void ennemy_projectile_destroy(CORE* game)
{
	for (int i = 0; i < MAX_PROJECTILE; i++)
	{
		if (game->projectilesystem->projectile[i].exist && game->projectilesystem->projectile[i].owner)
		{
			const int tile_type = tile_on_this_pos(game->projectilesystem->projectile[i].x, game->projectilesystem->projectile[i].y, game->map);
			if (tile_type == 2 || tile_type == 4)
			{
				game->projectilesystem->projectile[i].exist = 0;
				//chunk_play(game->soundsystem, 1, 13);

			}
			if (game->entitysystem->entity[0].exist)
			{
				int distance;
				if (game->entitysystem->entity[0].shield_active)
					distance = 45;
				else
					distance = 17;
				if (distancepoint(game->entitysystem->entity[0].x, game->entitysystem->entity[0].y, game->projectilesystem->projectile[i].x, game->projectilesystem->projectile[i].y) <= distance)
				{
					game->projectilesystem->projectile[i].exist = 0;
					chunk_play(game->soundsystem, 1, 13);
					if(!game->entitysystem->entity[0].shield_active)
					{
						game->timer_life -= 3000;
						game->nb_shot_took++;
					}
					else
					{
						game->nb_shot_stoped++;
					}
					
				}

			}

		}



	}
}
