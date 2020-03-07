#include "SDL_Helper.h"

void Helper_CreateTextureFromText(SDL_Renderer *r, SDL_StructText *st, const char*text, const char*p, int size, int y, int x, SDL_Color color) {
	
	SDL_StructText pd;
	pd.txt_font = TTF_OpenFont(p, size);

	SDL_Surface * s = TTF_RenderText_Solid(pd.txt_font, text, color);
	pd.txt_texture = SDL_CreateTextureFromSurface(r, s);
	SDL_FreeSurface(s);
	
	TTF_SizeText(pd.txt_font, text, &pd.txt_rect.w, &pd.txt_rect.h);
	
	pd.txt_rect.y = y; // vertical point
	pd.txt_rect.x = x; // horizontal point
	
	memcpy(st, &pd, sizeof(pd));
	
	return;
}

void Helper_DestroyStructText(SDL_StructText * st) {
	SDL_DestroyTexture(st->txt_texture);
	TTF_CloseFont(st->txt_font);
	return;
}
