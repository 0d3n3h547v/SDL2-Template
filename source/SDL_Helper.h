#ifndef SDL_HELPER_H
#define SDL_HELPER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct {
	
	TTF_Font 	* txt_font;
	SDL_Texture * txt_texture;
	SDL_Rect 	txt_rect;
	
} SDL_StructText;

void Helper_CreateTextureFromText(SDL_Renderer *r, SDL_StructText *st, const char*text, const char*p, int size, int y, int x, SDL_Color color);
void Helper_DestroyStructText(SDL_StructText * st);

#endif