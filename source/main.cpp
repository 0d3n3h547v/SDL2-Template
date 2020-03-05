#include <stdio.h>
#include <stdlib.h>
#include <switch.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

SDL_Window * window;
SDL_Renderer * renderer;
SDL_Surface * surface;
SDL_Texture * texture;
//TTF_Font * font;
//SDL_Texture * txt_texture;
//SDL_Rect rect;

SDL_Color white = {255, 255, 255, 255};

typedef struct {
	
	TTF_Font 	* txt_font;
	SDL_Texture * txt_texture;
	SDL_Rect 	txt_rect;
	
} SDL_StructText;

SDL_StructText * Helper_CreateTextureFromText(SDL_Renderer*r, const char*text, const char*p, int size, int y, int x, SDL_Color color) {
	
	SDL_StructText * pd;
	pd->txt_font = TTF_OpenFont(p, size);
	
	SDL_Surface * s = TTF_RenderText_Solid(pd->txt_font, text, color);
	pd->txt_texture = SDL_CreateTextureFromSurface(r, s);
	SDL_FreeSurface(s);
	
	TTF_SizeText(pd->txt_font, text, &pd->txt_rect.w, &pd->txt_rect.h);
	
	pd->txt_rect.y = y; // vertical point
	pd->txt_rect.x = x; // horizontal point
	
	return (pd);
}

int main(void) {
	
	romfsInit();
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	
	window = SDL_CreateWindow("n/a", 0, 0, 1280, 720, 0);
	renderer = SDL_CreateRenderer(window, 0 , SDL_RENDERER_ACCELERATED);
	
	texture = IMG_LoadTexture(renderer, "romfs:/background.png");
	
	/*
	font = TTF_OpenFont("romfs:/aquawax.ttf", 36);
	
	surface = TTF_RenderText_Solid(font, "hello there!", white);
	txt_texture = SDL_CreateTextureFromSurface(renderer, surface);
	
	TTF_SizeText(font, "hello there!", &rect.w, &rect.h);
	
	rect.x = 10;
	rect.y = 10;
	*/
	
	SDL_StructText text;
	
	&text = Helper_CreateTextureFromText(renderer, "hello there!", "romfs:/aquawax.ttf", 36, 10, 10, white);
	
	while(appletMainLoop()) {
		
		hidScanInput();
		u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
		if (kDown & KEY_PLUS) break;
		
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderCopy(renderer, text.txt_texture, NULL, &text.txt_rect);
		SDL_RenderPresent(renderer);
	}
	
	//SDL_FreeSurface(surface);
	//SDL_DestroyTexture(txt_texture);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	romfsExit();
	
	return (EXIT_SUCCESS);	
}