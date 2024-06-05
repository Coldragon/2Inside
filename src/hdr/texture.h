#ifndef DEF_TEXTURE
#define DEF_TEXTURE
#include <SDL.h>

struct Texture
{
	SDL_Texture* handle;
	unsigned int w;
	unsigned int h;
};
typedef struct Texture Texture;

Texture* TextureCreate(SDL_Renderer* renderer, const char* spriteName, int r, int g, int b, int a);
int TextureRenderEx(SDL_Renderer* renderer, Texture* tex, SDL_Rect* source, SDL_Rect* destination, double angle);
int TextureRender(SDL_Renderer* renderer, Texture* tex, SDL_Rect* pos, SDL_Rect* clip);
Texture* TextureCopy(SDL_Renderer* renderer, Texture* tex);
void TextureFree(Texture* tex);

#endif
