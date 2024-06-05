#include <SDL.h>
#include "hdr/gui.h"
#include "hdr/texture.h"

void gui_rectangle(SDL_Renderer *render, Texture *text, SDL_Rect rect)
{
	SDL_Rect src, dst;
	int wtext3 = text->w / 3;
	int htext3 = text->h / 3;

	src.w = wtext3; src.h = htext3;

	// CENTER

	src.x = wtext3; src.y = htext3;
	dst.x = rect.x + wtext3; dst.y = rect.y + htext3;
	dst.w = rect.w - (wtext3) * 2; dst.h = rect.h - (htext3) * 2;

	TextureRender(render, text, &src, &dst);

	dst.w = wtext3; dst.h = htext3;

	// UPMID

	src.x = wtext3; src.y = 0; dst.y = rect.y; dst.x = rect.x+wtext3;
	dst.w = rect.w - (wtext3 * 2);

	TextureRender(render, text, &src, &dst);

	dst.w = wtext3; dst.h = htext3;

	// LEFTMID

	src.x = 0; src.y = htext3;
	dst.x = rect.x; dst.y = rect.y+htext3;
	dst.h = rect.h - (htext3 * 2);

	TextureRender(render, text, &src, &dst);

	dst.w = wtext3; dst.h = htext3;

	// RIGHT MID

	src.x = wtext3 * 2; src.y = htext3;
	dst.x = rect.x+rect.w - wtext3; dst.y = rect.y+ htext3;
	dst.h = rect.h - (htext3 * 2);

	TextureRender(render, text, &src, &dst);

	dst.w = wtext3; dst.h = htext3;


	// DOWNMID

	src.x = wtext3; src.y = htext3 * 2; dst.y = rect.y+rect.h - htext3; dst.x = rect.x+wtext3;
	dst.w = rect.w - (wtext3 * 2);

	TextureRender(render, text, &src, &dst);

	dst.w = wtext3; dst.h = htext3;

	// UPLEFT

	src.x = 0; src.y = 0; 
	dst.x = rect.x; dst.y = rect.y;

	TextureRender(render, text, &src, &dst);

	dst.w = wtext3;

	// UPRIGHT

	src.x = wtext3*2; src.y = 0;
	dst.x = rect.x+rect.w-wtext3; dst.y = rect.y;

	TextureRender(render, text, &src, &dst);

	dst.h = htext3;

	// DOWNLEFT

	src.x = 0; src.y = htext3 *2;
	dst.x = rect.x; dst.y = rect.y+rect.h- htext3;

	TextureRender(render, text, &src, &dst);

	// DOWNRIGHT

	src.x = wtext3 * 2; src.y = htext3 * 2;
	dst.x = rect.x + rect.w - wtext3; dst.y = rect.y+rect.h - htext3;

	TextureRender(render, text, &src, &dst);
}
