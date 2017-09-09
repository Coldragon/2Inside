#ifndef DEF_INPUT
#define DEF_INPUT
#include "core.h"

void input_return(INPUT *input, SDL_Window *window, CAMERA *camera);

void input_init(INPUT *input);

void input_window_interraction(INPUT *input, CAMERA *camera, SDL_Window *window);

void move_player(CORE *game);

void attack_player(CORE *game);


#endif