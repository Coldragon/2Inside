#include <SDL2/SDL_ttf.h>
#include "hdr/struct.h"
#include "hdr/input.h"
#include "hdr/camera.h"
#include "hdr/graphics.h"
#include "hdr/entity.h"
#include "hdr/projectile.h"
#include "hdr/gui.h"
#include "hdr/text.h"

void graph_loop(CORE *game)
{
	afficher_clear(game->render, 120, 120, 120); // Clear screen

	SDL_Rect back = { 0 }; back.w = game->camera.w; back.h = game->camera.h;
	TextureRender(game->render, game->texpack.background, NULL, &back);

	afficher_layer(game, game->map->water); // Layer water
	afficher_layer(game, game->map->sol); // Layer sol
										  //afficher_sprite(game, game->texpack.player, 0, 0);
	move_position_r(&game->camera.x, &game->camera.y, game->entitysystem->entity[0].x, game->entitysystem->entity[0].y, game->entitysystem->entity[0].speed);

	afficher_projectile(game);
	draw_entity(game);

	// GUI
	afficher_gui(game->render, game->texpack.dot, game->camera.w / 2 - (game->texpack.dot->w / 2), game->camera.h / 2 - (game->texpack.dot->h / 2)); // Center Dot

																																					 //#ifdef _DEBUG
	debug_text(game); // Top gui with debug test
					  //#endif

	SDL_Rect rect = { 0,game->camera.h - 50,200, 50 }; // Bot Rect
	gui_rectangle(game->render, game->texpack.gui, rect); // Bot Gui
	afficher_windows_interraction(game);
	afficher_gui(game->render, game->texpack.cursor, game->input.mousex, game->input.mousey); // Mouse cursor
	SDL_RenderPresent(game->render);
}

void core_loop(CORE *game)
{
	input_return(&game->input, game->window, &game->camera);
	camera_move(game);
	camera_space(game);
	input_window_interraction(&game->input, &game->camera, game->window);
	move_position_r(&game->camera.x, &game->camera.y, game->entitysystem->entity[0].x, game->entitysystem->entity[0].y, game->entitysystem->entity[0].speed*game->time.delta);
	move_entity(game);
	move_player(game);
	move_projectile(game);
	attack_player(game);
}

void limiter_loop(CORE *game)
{
	while (!game->input.quit)
	{
		game->time.actual = SDL_GetTicks(); // ticks since start of software at the start of loop
		game->time.ticksEllapsed = game->time.actual - game->time.last; // calculate nb of ticks ellapsed
		game->time.delta = (float)game->time.ticksEllapsed / 1000; // update the time.delta
		if (game->time.ticksEllapsed > game->time.ticks) // if the ticks ellapsed is superiore to the ticks for a frame it run the loop
		{
			game->fps = 1000 / game->time.ticksEllapsed;
			core_loop(game);
			graph_loop(game);
			game->time.last = game->time.actual;
		}
		else // else it wait until the nb of ticks is enough to fix fps to max fps
			SDL_Delay(game->time.ticks - (game->time.actual - game->time.last));
	}
}