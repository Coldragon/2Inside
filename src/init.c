#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string.h>
#include "hdr/init.h"
#include "hdr/input.h"
#include "hdr/map.h"
#include "hdr/entity.h"
#include "hdr/sound.h"
#include <time.h>
#include <stdlib.h>
#include "hdr/spawner.h"

void open_sdl_shit()
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
}

void close_sdl_shit()
{
	TTF_Quit();
	SDL_Quit();
}

void time_init(TIME *time)
{
	memset(time, 0, sizeof(TIME));
	time->fps = 120;	time->ticks = 1000 / time->fps;
}

void state_init(STATE *state)
{
	state->game_continue = 1; state->game_restarter = 1;
}

void camera_init(CAMERA *camera)
{
	camera->h = 720; camera->w = 1280; camera->y = 0; camera->x = 0;
	camera->speed = 200;
}

void map_init(MAP *map)
{
	memset(map->terminalspawner, 0, sizeof(MAP));
}

void core_init(CORE *game)
{
	srand((unsigned int)time(NULL));

	game->timer_life = 120000; 

	// Camera
	camera_init(&game->camera);

	// Window
	game->zoom_level = 1; game->tcase = 32;
	game->window = SDL_CreateWindow("2Inside GameJam Build", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, game->camera.w, game->camera.h, SDL_RENDERER_PRESENTVSYNC | SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_BORDERLESS);
	game->render = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");


	// Input
	input_init(&game->input);

	// Limiter
	time_init(&game->time);

	// State
	state_init(&game->state);

	// Map
	game->map = calloc(1, sizeof(MAP));
	map_load(game->map, "res/map/map.json");

	// Texture
	game->texpack.tileset = TextureCreate(game->render, "res/img/tileset.png", 255, 0, 255, 255);
	game->texpack.gui = TextureCreate(game->render, "res/img/gui3.png", 255, 0, 255, 255);
	game->texpack.gui2 = TextureCreate(game->render, "res/img/gui2.png", 255, 0, 255, 255);
	game->texpack.gui5 = TextureCreate(game->render, "res/img/gui5.png", 255, 0, 255, 255);
	game->texpack.cursor = TextureCreate(game->render, "res/img/cursor.png", 255, 0, 255, 255);
	game->texpack.player = TextureCreate(game->render, "res/img/player.png", 255, 0, 255, 255);
	game->texpack.guibutton = TextureCreate(game->render, "res/img/guibutton.png", 255, 0, 255, 255);
	game->texpack.background = TextureCreate(game->render, "res/img/background.png", 255, 0, 255, 255);
	game->texpack.projectileset = TextureCreate(game->render, "res/img/projectileset.png", 255, 0, 255, 255);
	game->texpack.shield = TextureCreate(game->render, "res/img/shield.png", 255, 0, 255, 255);
	game->texpack.start = TextureCreate(game->render, "res/img/start.png", 255, 0, 255, 255);
	game->texpack.end = TextureCreate(game->render, "res/img/end.png", 255, 0, 255, 255);




	// Font
	game->font = TTF_OpenFont("res/ttf/8-bit pusab.ttf", 11);

	// Entity System
	game->entitysystem = calloc(1, sizeof(ENTITYSYSTEM));
	memset(game->entitysystem, 0, sizeof(ENTITYSYSTEM));

	// Projectilesystem
	game->projectilesystem = calloc(1, sizeof(PROJECTILESYSTEM));
	memset(game->projectilesystem, 0, sizeof(PROJECTILESYSTEM));

	// Soundsystem
	game->soundsystem = calloc(1, sizeof(SOUNDSYSTEM));
	memset(game->soundsystem, 0, sizeof(SOUNDSYSTEM));
	
	init_soundsystem(game->soundsystem);
	
	music_load(game->soundsystem, "res/snd/synthwave.ogg");
	
	game->soundsystem->music = Mix_LoadMUS("res/snd/synthwave.ogg");
	
	music_volume(game->soundsystem, 50);

	chunk_load(game->soundsystem, "res/snd/laser.wav"); // 0
	chunk_load(game->soundsystem, "res/snd/explosion.wav"); // 1
	chunk_load(game->soundsystem, "res/snd/explosion2.wav"); // 2
	chunk_load(game->soundsystem, "res/snd/hack_complete.wav"); // 3
	chunk_load(game->soundsystem, "res/snd/hack_start.wav"); // 4
	chunk_load(game->soundsystem, "res/snd/hack_failed.wav"); // 5




	create_entity(game, 0, 0, 200, 0,"res/img/player.png");
	spawn_terminal(game->map, game);
	spawn_ennemies(game->map, game);

}