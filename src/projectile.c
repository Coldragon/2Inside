#include "hdr/camera.h"
#include "hdr/graphics.h"

void create_projectile(PROJECTILESYSTEM *projectilesystem, ENTITY origin, int x_dest, int y_dest, int texture_index)
{
	projectilesystem->projectile[projectilesystem->tofill].x = origin.x;
	projectilesystem->projectile[projectilesystem->tofill].y = origin.y;
	projectilesystem->projectile[projectilesystem->tofill].destX = x_dest;
	projectilesystem->projectile[projectilesystem->tofill].destY = y_dest;
	projectilesystem->projectile[projectilesystem->tofill].speed = origin.projectilespeed;
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

				dstTile.x = proj_pos_screen.x-16;
				dstTile.y = proj_pos_screen.y-16;

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

void destroy_projectile()
{
	
}