#include <SDL.h>
#include "hdr/graphics.h"
#include "hdr/camera.h"
#include "hdr/gui.h"
#include "hdr/entity.h"

void afficher_clear(SDL_Renderer* render, int r, int g, int b)
{
	SDL_SetRenderDrawColor(render, r, g, b, 255);
	SDL_RenderClear(render);
}

void afficher_layer(CORE *game, unsigned short layer[100][100])
{
	SDL_Rect dstTile, srcTile;
	int temp = game->zoom_level * game->tcase;

	srcTile.w = game->tcase;
	srcTile.h = game->tcase;
	dstTile.w = temp;
	dstTile.h = temp;

	int wtileset = game->texpack.tileset->w / game->tcase;

	for (int i = 0; i<100; i++)
	{
		for (int j = 0; j<100; j++)
		{
			srcTile.x = game->tcase * ((layer[i][j] - 1) % (wtileset));
			srcTile.y = game->tcase * ((layer[i][j] - 1) / (wtileset));

			dstTile.x = -game->camera.x + (game->camera.w / 2) - 1600 + j * (temp);
			dstTile.y = -game->camera.y + (game->camera.h / 2) - 1600 + i * (temp);
			TextureRender(game->render, game->texpack.tileset, &srcTile, &dstTile);
		}
	}
}

void afficher_sprite(CORE *game, Texture *text, int x, int y, double angle)
{
	SDL_Rect rect = { x-(text->w/2), y - (text->h / 2), text->w, text->h };
	rect = position_to_screen(rect, &game->camera);
	TextureRenderEx(game->render, text, NULL, &rect, angle);
}

void afficher_gui(SDL_Renderer *render, Texture *text, int x, int y)
{
	SDL_Rect rect = { x, y, text->w, text->h };
	TextureRender(render, text, NULL, &rect);
}

void afficher_windows_interraction(CORE *game)
{
	SDL_Rect src = { 27*2, 0, 27, 27  };
	SDL_Rect dst = { game->camera.w-29, 2, 27, 27 };
	TextureRender(game->render, game->texpack.guibutton, &src, &dst); // quit

	src.x -= 27;
	dst.x -= 27;

	TextureRender(game->render, game->texpack.guibutton, &src, &dst); // maximize

	src.x -= 27;
	dst.x -= 27;

	TextureRender(game->render, game->texpack.guibutton, &src, &dst); // minimize
}