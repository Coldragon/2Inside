#ifndef DEF_GRAPHICS
#define DEF_GRAPHICS
#include <SDL2/SDL.h>
#include "camera.h"

void afficher_clear(SDL_Renderer* render, int r, int g, int b);
void afficher_layer(CORE *game, unsigned short layer[100][100]);
void afficher_sprite(CORE *game, Texture *text, int x, int y, double angle);
void afficher_gui(SDL_Renderer *render, Texture *text, int x, int y);
void afficher_windows_interraction(CORE *game);


#endif
