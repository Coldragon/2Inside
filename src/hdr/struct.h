#ifndef DEF_STRUCT
#define DEF_STRUCT
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "texture.h"

typedef struct
{
	float ticks;
	long last;
	long actual;

} TIMER;


typedef struct
{
	float x, y;
	int destX, destY;
	double angle;
	float speed;
	Texture* texture;
	int texturepos;
	int attackspeed;
	int projectilespeed;

} ENTITY;

typedef struct
{
	Mix_Music *music;
	Mix_Chunk *sound[25];
	int tofill;
	int channel_to_use;
	int max_channel;


} SOUNDSYSTEM;

typedef struct
{
	float x, y;
	float destX, destY;
	double angle;
	int speed;
	int texture_index;
	int exist;


} PROJECTILE;

typedef struct
{
	PROJECTILE projectile[100];
	int tofill;
	int nbprojectile;
	

} PROJECTILESYSTEM;

typedef struct
{
	ENTITY entity[100];
	int tofill;
	int nbentity;

} ENTITYSYSTEM;

typedef struct
{
	float x,y;
	int w,h;
	float speed;

} CAMERA;

typedef struct
{
	int fps;
	float ticks;
	long last;
	long actual;
	float delta;
	unsigned int ticksEllapsed;

} TIME;

typedef struct
{
	int game_continue;
	int game_restarter;

} STATE;

typedef struct
{
	char key[SDL_NUM_SCANCODES];
	int wheelup;
	int wheeldown;
	int quit;
	int leftclic;
	int leftclic_position_x;
	int leftclic_position_y;
	int leftclic_position_x_old;
	int leftclic_position_y_old;
	int leftclic_trigger;
	int rightclic;
	int rightclic_position_x;
	int rightclic_position_y;
	int rightclic_position_x_old;
	int rightclic_position_y_old;
	int rightclic_trigger;
	int mousex;
	int mousey;
	int focus;
	int window_maximize;
	SDL_Rect window_maximize_old;
	char *filedrop;

} INPUT;

typedef struct
{
	int width;
	int height;
	int nbLayer;
	unsigned short sol[100][100];
	unsigned short water[100][100];

} MAP;

typedef struct
{
	Texture *tileset;
	Texture *dot;
	Texture *gui;
	Texture *gui2;
	Texture *guibutton;
	Texture *cursor;
	Texture *player;
	Texture *background;
	Texture *projectileset;

} TEXPACK;

typedef struct
{
	int score;
	int fps;
	float zoom_level;
	int tcase;
	long timer_life;
	SDL_Window* window;
	SDL_Renderer* render;
	TTF_Font* font;
	CAMERA camera;
	TIME time;
	STATE state;
	INPUT input;
	MAP *map;
	TEXPACK texpack;
	ENTITYSYSTEM *entitysystem;
	SOUNDSYSTEM *soundsystem;
	PROJECTILESYSTEM *projectilesystem;

} CORE;

#endif
