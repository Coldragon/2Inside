#include "hdr/entity.h"
#include "hdr/struct.h"
#include "hdr/graphics.h"

void create_entity(CORE *game, int x, int y, int speed, char* texturepath)
{

	game->entitysystem->entity[game->entitysystem->tofill].x = x;
	game->entitysystem->entity[game->entitysystem->tofill].y = y;
	game->entitysystem->entity[game->entitysystem->tofill].speed = speed;
	game->entitysystem->entity[game->entitysystem->tofill].texture = TextureCreate(game->render, texturepath, 255,255,0,255);
	game->entitysystem->entity[game->entitysystem->tofill].projectilespeed = 500;
	game->entitysystem->entity[game->entitysystem->tofill].attackspeed = 200;
	game->entitysystem->tofill++;
}

void draw_entity(CORE *game)
{
	for (int i = 0; i < game->entitysystem->tofill; i++)
		afficher_sprite(game,game->entitysystem->entity[i].texture, game->entitysystem->entity[i].x, game->entitysystem->entity[i].y, game->entitysystem->entity[i].angle);
}

void move_entity(CORE *game)
{
	for (int i = 0; i < game->entitysystem->tofill; i++)
	{
		if(game->entitysystem->entity[i].destX != 0 && game->entitysystem->entity[i].destY != 0)
		{
			game->entitysystem->entity[i].x += game->entitysystem->entity[i].destX * game->entitysystem->entity[i].speed * game->time.delta * 0.7071;
			game->entitysystem->entity[i].y += game->entitysystem->entity[i].destY * game->entitysystem->entity[i].speed * game->time.delta * 0.7071;
		}
		else
		{
			game->entitysystem->entity[i].x += game->entitysystem->entity[i].destX * game->entitysystem->entity[i].speed * game->time.delta;
			game->entitysystem->entity[i].y += game->entitysystem->entity[i].destY * game->entitysystem->entity[i].speed * game->time.delta;
		}
	}
}