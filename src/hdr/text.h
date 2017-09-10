#ifndef DEF_TEXT
#define DEF_TEXT
#include <SDL2/SDL_ttf.h>

typedef struct {
	SDL_Texture* text;
	SDL_Texture* outline;
	SDL_Rect positionText;
	SDL_Rect positionOutline;
} BoldTextTexture;

BoldTextTexture text_update(SDL_Renderer *render, TTF_Font *font, char* string, int x, int y);
void text_affichage(SDL_Renderer *render, BoldTextTexture* btt);
void debug_text(CORE* game);
void timer_text(CORE* game);
void timer_bar(CORE* game);
void text_score(CORE *game);
void shield_text(CORE* game);
void end_text(CORE* game);



#endif