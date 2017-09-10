#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "hdr/camera.h"
#include "hdr/gui.h"
#include "hdr/text.h"

const SDL_Color WHITE = { 255, 255, 255, 255 };
const SDL_Color BLACK = { 0, 0, 0, 0 };

BoldTextTexture text_update(SDL_Renderer *render, TTF_Font *font, char* string, int x, int y) {
	SDL_Surface* surf;

	BoldTextTexture btt;
	TTF_SetFontOutline(font, 2);
	surf = TTF_RenderText_Blended(font, string, BLACK);
	btt.positionOutline.x = x - 2; btt.positionOutline.y = y - 2;
	btt.positionOutline.h = surf->h; btt.positionOutline.w = surf->w;
	btt.outline = SDL_CreateTextureFromSurface(render, surf);
	SDL_FreeSurface(surf);
	TTF_SetFontOutline(font, 0);
	surf = TTF_RenderText_Blended(font, string, WHITE);
	
	btt.positionText.x = x; btt.positionText.y = y;
	btt.positionText.h = surf->h; btt.positionText.w = surf->w;
	btt.text = SDL_CreateTextureFromSurface(render, surf);
	SDL_RenderCopy(render, btt.text, NULL, &btt.positionText);
	SDL_FreeSurface(surf);

	return btt;
}

void text_affichage(SDL_Renderer *render, BoldTextTexture* btt) {
	SDL_RenderCopy(render, btt->outline, NULL, &btt->positionOutline);
	SDL_RenderCopy(render, btt->text, NULL, &btt->positionText);
}

void debug_text(CORE* game)
{
	static long lasttime = 0;
	static char tempchar[500] = "0";
	static BoldTextTexture btt = {0};

	SDL_Rect rect = { 0,0,game->camera.w,32 };
	gui_rectangle(game->render, game->texpack.gui2, rect);

	if (SDL_GetTicks() - lasttime > 50) {
		lasttime = SDL_GetTicks();
		SDL_DestroyTexture(btt.outline);
		SDL_DestroyTexture(btt.text);
		//sprintf(tempchar, "FPS: [%d] CAMERA-> Position : [%f, %f] Size : [%u, %u] Zoom : [%f] Input grabed : [%i]", game->fps, game->camera.x, game->camera.y, game->camera.w, game->camera.h, game->zoom_level, SDL_GetWindowGrab(game->window));
		sprintf(tempchar, "WaveHacking GameJam Build");
		btt = text_update(game->render, game->font, tempchar, 11, 7);
	}

	text_affichage(game->render, &btt);

}

void timer_text(CORE* game)
{
	static long lasttime = 0;
	static long lasttime2 = 0;
	static char tempchar[30] = "0";
	static BoldTextTexture btt = { 0 };


	if (SDL_GetTicks() - lasttime > 50) 
	{
		if (SDL_GetTicks() - lasttime2 > 1000)
		{
			game->timer_life -= 1000;
			lasttime2 = SDL_GetTicks();
		}
			
		lasttime = SDL_GetTicks();
		SDL_DestroyTexture(btt.outline);
		SDL_DestroyTexture(btt.text);
		sprintf(tempchar, "Timeleft : [%d]", game->timer_life/1000);
		//sprintf(tempchar, "FPS: [%d] :: Terminal", game->fps);
		btt = text_update(game->render, game->font, tempchar, 20, game->camera.h-34);
	}

	text_affichage(game->render, &btt);
}
