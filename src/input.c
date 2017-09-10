#include "hdr/input.h"
#include "hdr/core.h"
#include <string.h>
#include "hdr/camera.h"
#include "hdr/projectile.h"
#include "hdr/sound.h"

void input_return(INPUT *input, SDL_Window *window, CAMERA *camera)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			input->quit = 1;
			break;
		case SDL_KEYDOWN:
			input->key[event.key.keysym.scancode] = 1;
			break;
		case SDL_KEYUP:
			input->key[event.key.keysym.scancode] = 0;
			break;
		case SDL_MOUSEWHEEL:
			if (event.wheel.y > 0)
				input->wheelup = 1;
			if (event.wheel.y < 0)
				input->wheeldown = 1;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				input->leftclic = 1;
				input->leftclic_position_x = event.motion.x;
				input->leftclic_position_y = event.motion.y;
			}
			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				input->rightclic = 1;
				input->rightclic_position_x = event.motion.x;
				input->rightclic_position_y = event.motion.y;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				input->leftclic = 0;
			}
			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				input->rightclic = 0;
			}
			break;
		case SDL_MOUSEMOTION:
			input->mousex = event.motion.x;
			input->mousey = event.motion.y;
			break;
		case SDL_DROPFILE:
			input->filedrop = event.drop.file;
			break;
		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				input->focus = 1;
				break;
			case SDL_WINDOWEVENT_FOCUS_LOST:
				input->focus = 0;
				break;
			case SDL_WINDOWEVENT_RESIZED:
				SDL_GetWindowSize(window, &camera->w, &camera->h);
			default:
				break;
			}
		default:
			break;
		}
		if (event.wheel.y == 0)
		{
			input->wheelup = 0;
			input->wheeldown = 0;
		}

		if (input->leftclic && !input->leftclic_trigger)
		{
			input->leftclic_trigger = 1;
			input->leftclic_position_x_old = input->leftclic_position_x;
			input->leftclic_position_y_old = input->leftclic_position_y;
		}

		if(!input->leftclic && input->leftclic_trigger)
		{
			input->leftclic_trigger = 0;
		}

	}
}

void input_init(INPUT *input)
{
	int temp = input->focus;
	memset(input, 0, sizeof(INPUT));
	input->focus = temp;
}


void input_window_interraction(INPUT *input, CAMERA *camera ,SDL_Window *window)
{
	//int grabbed = SDL_GetWindowGrab(window);
	// Quit
	if (input->leftclic && input->leftclic_position_x >= camera->w - 27 + 2 && input->leftclic_position_y < 32) // QUIT
	{
		input->quit = 1;
		input->leftclic = 0;
	}

	// Fullscreen toggle
	if (input->leftclic && input->leftclic_position_x >= camera->w - (27*2+2) && input->leftclic_position_x <= camera->w - (27+2) && input->leftclic_position_y < 32)
	{
		if (input->window_maximize)
		{

			SDL_SetWindowSize(window, input->window_maximize_old.w, input->window_maximize_old.h);
			SDL_SetWindowPosition(window, input->window_maximize_old.x, input->window_maximize_old.y);
			camera->w = input->window_maximize_old.w; camera->h = input->window_maximize_old.h;
			input->window_maximize = 0;
		}
		else
		{
			/*SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
			//SDL_MaximizeWindow(window);
			SDL_SetWindowGrab(window, 1);*/

			SDL_GetWindowSize(window, &input->window_maximize_old.w, &input->window_maximize_old.h);
			SDL_GetWindowPosition(window, &input->window_maximize_old.x, &input->window_maximize_old.y);

			int display_index = SDL_GetWindowDisplayIndex(window);
			if (display_index < 0) {
				SDL_Log("error getting window display");
				return;
			}

			SDL_Rect usable_bounds;
			if (0 != SDL_GetDisplayUsableBounds(display_index, &usable_bounds)) {
				SDL_Log("error getting usable bounds");
				return;
			}

			SDL_SetWindowPosition(window, usable_bounds.x, usable_bounds.y);
			SDL_SetWindowSize(window, usable_bounds.w, usable_bounds.h);
			camera->w = usable_bounds.w; camera->h = usable_bounds.h;
			input->window_maximize = 1;
		}
			

		input->leftclic = 0;
	}

	// Minimize Window
	if (input->leftclic && input->leftclic_position_x >= camera->w - (27 * 3 + 2) && input->leftclic_position_x <= camera->w - (27 * 2 + 2) && input->leftclic_position_y < 32)
	{
		SDL_MinimizeWindow(window);
		input->leftclic = 0;
	}

	// Move Window
	if(input->leftclic && input->leftclic_position_y < 32 && input->leftclic_position_x < camera->w - 83 && !input->window_maximize)
	{
			SDL_SetWindowGrab(window, 0);
			
			int x_mouse_screen; int y_mouse_screen;
			SDL_GetGlobalMouseState(&x_mouse_screen, &y_mouse_screen);
			SDL_SetWindowPosition(window, x_mouse_screen - input->leftclic_position_x, y_mouse_screen - input->leftclic_position_y);

			SDL_SetWindowGrab(window, 1);
			
	}
	
	// Window Resize
	/*
	if(grabbed && input->leftclic && input->leftclic_position_x > camera->w-5)
	{
		SDL_SetWindowSize(window, camera->w, camera->h);
	}
	*/
}

void move_player(CORE *game)
{
	game->entitysystem->entity[0].destY = 0;
	game->entitysystem->entity[0].destX = 0;

	if (game->input.key[SDL_SCANCODE_W])
		game->entitysystem->entity[0].destY -= 1;
	if (game->input.key[SDL_SCANCODE_S])
		game->entitysystem->entity[0].destY += 1;
	if (game->input.key[SDL_SCANCODE_A])
		game->entitysystem->entity[0].destX -= 1;
	if (game->input.key[SDL_SCANCODE_D])
		game->entitysystem->entity[0].destX += 1;

	SDL_Rect pos_player = {0}; pos_player.x = game->entitysystem->entity[0].x; pos_player.y = game->entitysystem->entity[0].y;
	SDL_Rect pos_player_screen = position_to_screen(pos_player, &game->camera);
	game->entitysystem->entity[0].angle = angle_calculate_degree(game->input.mousex, game->input.mousey, pos_player_screen.x, pos_player_screen.y);

}

void attack_player(CORE *game)
{
	static TIMER attack = {0};
	attack.ticks = game->entitysystem->entity[0].attackspeed;
	attack.actual = SDL_GetTicks();

	if(game->input.leftclic)
	{
		if (attack.actual - attack.last > attack.ticks) // if the ticks ellapsed is superiore to the ticks for a frame it run the loop
		{
			SDL_Rect cursor_pos = { 0 }; cursor_pos.x = game->input.mousex; cursor_pos.y = game->input.mousey;
			SDL_Rect cursor_pos_in_game = screen_to_position(cursor_pos, &game->camera);
			create_projectile(game->projectilesystem, game->entitysystem->entity[0], cursor_pos_in_game.x, cursor_pos_in_game.y, 0);
			chunk_play(game->soundsystem, 0, 20);
			attack.last = attack.actual;
		}
	}
}