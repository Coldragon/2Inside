#include <SDL2/SDL.h>
#include "hdr/core.h"
#include "hdr/input.h"
#include "hdr/camera.h"


SDL_Rect position_to_screen(SDL_Rect rect, CAMERA *camera)
{
	SDL_Rect rect2;
	rect2.w = rect.w; rect2.h = rect.h;
	rect2.x = (camera->w / 2) + rect.x-camera->x;
	rect2.y = (camera->h / 2) + rect.y-camera->y;
	return rect2;
}

SDL_Rect screen_to_position(SDL_Rect rect, CAMERA *camera)
{
	SDL_Rect rect2;
	rect2.w = rect.w; rect2.h = rect.h;

	rect2.x = -camera->w/2 + camera->x + rect.x;
	rect2.y = -camera->h/2 + camera->y + rect.y;
	return rect2;
}

void move_position_r(float *x1, float *y1, float x2, float y2, float r)
{
	float xdif = x2 - *x1; float ydif = y2 - *y1;
	float angle = atan2(ydif, xdif);
	float distance_r_r = xdif*xdif + ydif*ydif;
	*x1 += r * cos(angle); *y1 += r * sin(angle);
	if (distance_r_r < r*r)
	{
		*x1 = x2;
		*y1 = y2;
	}
}

void move_from_angle(float *x, float *y, double angle, float r)
{
	*x += r * cos(angle); *y += r * sin(angle);
}

double angle_calculate_degree(float x1, float y1, float x2, float y2) // RETURN IN DEGREE
{
	float xdif = x2 - x1; float ydif = y2 - y1;
	return 57.29*atan2(ydif, xdif);
}

double angle_calculate_radiant(float x1, float y1, float x2, float y2) // RETURN IN RADIANT
{
	float xdif = x2 - x1; float ydif = y2 - y1;
	return atan2(ydif, xdif);
}

void camera_move(CORE *game)
{
	//int grabbed = SDL_GetWindowGrab(game->window);
	// Camera Speed
	if (game->input.key[SDL_SCANCODE_LSHIFT])
		game->camera.speed = 700;
	else
		game->camera.speed = 450;

	/* Camera Movement
	if (game->input.key[SDL_SCANCODE_D] || game->input.key[SDL_SCANCODE_RIGHT] || (game->input.mousex >= game->camera.w - 5 && grabbed && !game->input.leftclic))
		game->camera.x += game->camera.speed * game->time.delta;
	if (game->input.key[SDL_SCANCODE_A] || game->input.key[SDL_SCANCODE_LEFT] || (game->input.mousex <= 5 && grabbed && !game->input.leftclic))
		game->camera.x -= game->camera.speed * game->time.delta;
	if (game->input.key[SDL_SCANCODE_W] || game->input.key[SDL_SCANCODE_UP] || (game->input.mousey <= 5 && grabbed && !game->input.leftclic))
		game->camera.y -= game->camera.speed * game->time.delta;
	if (game->input.key[SDL_SCANCODE_S] || game->input.key[SDL_SCANCODE_DOWN] || (game->input.mousey >= game->camera.h - 5 && grabbed && !game->input.leftclic))
		game->camera.y += game->camera.speed * game->time.delta; */

	// Map collide
	if (game->camera.x > 1600 - (game->camera.w / 2))
		game->camera.x = 1600 - (game->camera.w / 2);
	if (game->camera.x < -1600 + (game->camera.w / 2))
		game->camera.x = -1600 + (game->camera.w / 2);
	if (game->camera.y > 1600 - (game->camera.h / 2))
		game->camera.y = 1600 - (game->camera.h / 2);
	if (game->camera.y < -1600 + (game->camera.h / 2))
		game->camera.y = -1600 + (game->camera.h / 2);

	// Remove focus
	if (game->input.key[SDL_SCANCODE_ESCAPE])
	{
		if (SDL_GetWindowGrab(game->window))
			SDL_SetWindowGrab(game->window, 0);
		else
			SDL_SetWindowGrab(game->window, 1);
		game->input.key[SDL_SCANCODE_ESCAPE] = 0;
	}
}

void camera_zoom(CORE *game)
{
	if (game->input.key[SDL_SCANCODE_X] || game->input.wheeldown)
	{
		game->zoom_level-=0.02f;
		if (game->zoom_level < 0.02f)
			game->zoom_level = 0.02f;

		input_init(&game->input);
	}
	if (game->input.key[SDL_SCANCODE_C] || game->input.wheelup)
	{
		game->zoom_level+=0.02f;
		input_init(&game->input);
	}

	if (game->input.key[SDL_SCANCODE_RETURN])
		game->zoom_level = 1.0f;
}

void camera_space(CORE *game)
{
	if(game->input.key[SDL_SCANCODE_SPACE])
		move_position_r(&game->camera.x, &game->camera.y, 0, 0, 500*game->time.delta);
}