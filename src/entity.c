#include "hdr/entity.h"
#include "hdr/struct.h"
#include "hdr/graphics.h"
#include "hdr/map.h"
#include "hdr/sound.h"

void create_entity(CORE *game, int x, int y, int speed, int identity,char* texturepath)
{

	game->entitysystem->entity[game->entitysystem->tofill].x = x;
	game->entitysystem->entity[game->entitysystem->tofill].y = y;
	game->entitysystem->entity[game->entitysystem->tofill].destX = 0;
	game->entitysystem->entity[game->entitysystem->tofill].destY = 0;
	game->entitysystem->entity[game->entitysystem->tofill].exist = 1;
	game->entitysystem->entity[game->entitysystem->tofill].shield_time_max = 300;
	game->entitysystem->entity[game->entitysystem->tofill].shield_time = game->entitysystem->entity[game->entitysystem->tofill].shield_time_max;
	;

	game->entitysystem->entity[game->entitysystem->tofill].life_max = 5;
	game->entitysystem->entity[game->entitysystem->tofill].life = 5;
	game->entitysystem->entity[game->entitysystem->tofill].identity = identity;
	game->entitysystem->entity[game->entitysystem->tofill].speed = speed;
	game->entitysystem->entity[game->entitysystem->tofill].texture = TextureCreate(game->render, texturepath, 255,255,0,255);
	game->entitysystem->entity[game->entitysystem->tofill].projectilespeed = 500;
	game->entitysystem->entity[game->entitysystem->tofill].attackspeed = 200;
	game->entitysystem->tofill++;
}

void draw_entity(CORE *game)
{
	for (int i = 1; i < game->entitysystem->tofill; i++)
	{
		if(game->entitysystem->entity[i].exist)
			afficher_sprite(game, game->entitysystem->entity[i].texture, game->entitysystem->entity[i].x, game->entitysystem->entity[i].y, game->entitysystem->entity[i].angle);
	}
		
	afficher_sprite(game, game->entitysystem->entity[0].texture, game->entitysystem->entity[0].x, game->entitysystem->entity[0].y, game->entitysystem->entity[0].angle);

}

void move_entity(CORE *game)
{
	for (int i = 0; i < game->entitysystem->tofill; i++)
	{
		int tile_x = 0, tile_y = 0;
		int const x_temp = game->entitysystem->entity[i].x;
		int const y_temp = game->entitysystem->entity[i].y;

		if(game->entitysystem->entity[i].destX != 0 && game->entitysystem->entity[i].destY != 0)
		{
			game->entitysystem->entity[i].x += game->entitysystem->entity[i].destX * game->entitysystem->entity[i].speed * game->time.delta * 0.7071;
			tile_x = tile_on_this_pos(game->entitysystem->entity[i].x, game->entitysystem->entity[i].y, game->map);
			game->entitysystem->entity[i].y += game->entitysystem->entity[i].destY * game->entitysystem->entity[i].speed * game->time.delta * 0.7071;
			tile_y = tile_on_this_pos(game->entitysystem->entity[i].x, game->entitysystem->entity[i].y, game->map);
		}
		else
		{
			game->entitysystem->entity[i].x += game->entitysystem->entity[i].destX * game->entitysystem->entity[i].speed * game->time.delta;
			tile_x = tile_on_this_pos(game->entitysystem->entity[i].x, game->entitysystem->entity[i].y, game->map);
			game->entitysystem->entity[i].y += game->entitysystem->entity[i].destY * game->entitysystem->entity[i].speed * game->time.delta;
			tile_y = tile_on_this_pos(game->entitysystem->entity[i].x, game->entitysystem->entity[i].y, game->map);
		}

		
		if (tile_x == 2 || tile_x == 4)
			game->entitysystem->entity[i].x = x_temp;
		if (tile_y == 2 || tile_y == 4)
			game->entitysystem->entity[i].y = y_temp;



	}
}

void destroy_entity(CORE *game)
{
	for (int i = 0; i < game->entitysystem->tofill; i++)
	{
		if (game->entitysystem->entity[i].life <= 0)
		{
			game->entitysystem->entity[i].exist = 0;
			if (game->entitysystem->entity[i].identity == 2)
			{
				const int tile_nb_x = (game->entitysystem->entity[i].x + (MAP_WIDTH / 2 * TCASE)) / TCASE;
				const int tile_nb_y = (game->entitysystem->entity[i].y + (MAP_HEIGHT / 2 * TCASE)) / TCASE;
				game->map->tile[tile_nb_y][tile_nb_x] = 3;
				game->map->tile[tile_nb_y + 1][tile_nb_x] = 3;
				game->map->tile[tile_nb_y - 1][tile_nb_x] = 3;
				game->map->tile[tile_nb_y][tile_nb_x + 1] = 3;
				game->map->tile[tile_nb_y][tile_nb_x - 1] = 3;
			}
				create_entity(game, game->entitysystem->entity[i].x, game->entitysystem->entity[i].y, 0, 4, "res/img/ennemy_dead.png");

			chunk_play(game->soundsystem, 2, 20);
			game->score += 20;
			game->nb_turret_destroyed++;
			game->entitysystem->entity[i].life = 1;

		}
	}
}