#include "hdr/camera.h"
#include "hdr/graphics.h"
#include "hdr/projectile.h"
#include "hdr/map.h"
#include "hdr/define.h"
#include "hdr/sound.h"

void create_projectile(PROJECTILESYSTEM *projectilesystem, ENTITY origin, int x_dest, int y_dest, int texture_index, int owner)
{
	projectilesystem->projectile[projectilesystem->tofill].owner = owner;
	projectilesystem->projectile[projectilesystem->tofill].x = origin.x;
	projectilesystem->projectile[projectilesystem->tofill].y = origin.y;
	projectilesystem->projectile[projectilesystem->tofill].destX = x_dest;
	projectilesystem->projectile[projectilesystem->tofill].destY = y_dest;
	projectilesystem->projectile[projectilesystem->tofill].speed = origin.projectilespeed;
	if(owner)
		projectilesystem->projectile[projectilesystem->tofill].speed = origin.projectilespeed*1.3;
	projectilesystem->projectile[projectilesystem->tofill].texture_index = texture_index;
	projectilesystem->projectile[projectilesystem->tofill].exist = 1;
	projectilesystem->projectile[projectilesystem->tofill].angle =
		angle_calculate_radiant(projectilesystem->projectile[projectilesystem->tofill].x,
			projectilesystem->projectile[projectilesystem->tofill].y,
			projectilesystem->projectile[projectilesystem->tofill].destX,
			projectilesystem->projectile[projectilesystem->tofill].destY);

	projectilesystem->tofill++;

	if (projectilesystem->tofill >= 100)
		projectilesystem->tofill = 0;
}

void afficher_projectile(CORE *game)
{
	SDL_Rect dstTile, srcTile;
	int temp = game->tcase;

	srcTile.w = game->tcase;
	srcTile.h = game->tcase;
	dstTile.w = temp;
	dstTile.h = temp;

	int wtileset = game->texpack.projectileset->w / game->tcase;

	for (int i = 0; i < 100; i++)
	{
		if (game->projectilesystem->projectile[i].exist)
		{
			srcTile.x = game->tcase * ((game->projectilesystem->projectile[i].texture_index) % (wtileset));
			srcTile.y = game->tcase * ((game->projectilesystem->projectile[i].texture_index) / (wtileset));

			SDL_Rect proj_pos = { 0 }; proj_pos.x = game->projectilesystem->projectile[i].x; proj_pos.y = game->projectilesystem->projectile[i].y;
			SDL_Rect proj_pos_screen = position_to_screen(proj_pos, &game->camera);

			dstTile.x = proj_pos_screen.x - 16;
			dstTile.y = proj_pos_screen.y - 16;

			TextureRender(game->render, game->texpack.projectileset, &srcTile, &dstTile);
		}
	}

}

void move_projectile(CORE *game)
{
	for (int i = 0; i < 100; i++)
	{
		if (game->projectilesystem->projectile[i].exist)
		{
			move_from_angle(&game->projectilesystem->projectile[i].x,
				&game->projectilesystem->projectile[i].y,
				game->projectilesystem->projectile[i].angle,
				game->projectilesystem->projectile[i].speed * game->time.delta);
		}
	}
}

int distancepoint(int x1, int y1, int x2, int y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

void destroy_projectile(CORE *game)
{
	for (int i = 0; i < MAX_PROJECTILE; i++)
	{
		if (game->projectilesystem->projectile[i].exist && !game->projectilesystem->projectile[i].owner)
		{
			const int tile_type = tile_on_this_pos(game->projectilesystem->projectile[i].x, game->projectilesystem->projectile[i].y, game->map);
			if ( tile_type == 2 || tile_type == 4)
			{
				game->projectilesystem->projectile[i].exist = 0;
				const int tile_nb_x = (game->projectilesystem->projectile[i].x + (MAP_WIDTH / 2 * TCASE)) / TCASE;
				const int tile_nb_y = (game->projectilesystem->projectile[i].y + (MAP_HEIGHT / 2 * TCASE)) / TCASE;
				
				if(game->map->tile[tile_nb_y][tile_nb_x]==2) 
					game->map->tile[tile_nb_y][tile_nb_x] = 4;
				chunk_play(game->soundsystem, 1, 13);

			}
			for (int j = 0; j < game->entitysystem->tofill; j++)
			{
				if (game->entitysystem->entity[j].identity == 2)
					if (game->entitysystem->entity[j].exist)
					if (distancepoint(game->entitysystem->entity[j].x, game->entitysystem->entity[j].y, game->projectilesystem->projectile[i].x, game->projectilesystem->projectile[i].y) <= 17)
					{
						game->projectilesystem->projectile[i].exist = 0;
						chunk_play(game->soundsystem, 1, 13);
						game->entitysystem->entity[j].life--;
					}



			}
		}


	}
}