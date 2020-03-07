#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>

#include "SDL_Helper.h"

SDL_Window * window;
SDL_Renderer * renderer;
SDL_Texture * texture;

SDL_Color h_white = {255, 255, 255, 255};

int main(void) {
	
	romfsInit();
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	
	window = SDL_CreateWindow("n/a", 0, 0, 1280, 720, 0);
	renderer = SDL_CreateRenderer(window, 0 , SDL_RENDERER_ACCELERATED);
	
	texture = IMG_LoadTexture(renderer, "romfs:/background.png");
	
	SDL_StructText Title;
	Helper_CreateTextureFromText(renderer, &Title, "hello there!", "romfs:/aquawax.ttf", 36, 10, 10, h_white);
	
	SDL_StructText comment;
	Helper_CreateTextureFromText(renderer, &comment, "This is a test to see if its working!", "romfs:/aquawax.ttf", 36, 150, 150, h_white);
	
	while(appletMainLoop()) {
		
		hidScanInput();
		u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
		if (kDown & KEY_PLUS) break;
		
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderCopy(renderer, Title.txt_texture, NULL, &Title.txt_rect);
		SDL_RenderCopy(renderer, comment.txt_texture, NULL, &comment.txt_rect);
		SDL_RenderPresent(renderer);
	}
	
	Helper_DestroyStructText(&Title);
	Helper_DestroyStructText(&comment);
	
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	romfsExit();
	
	return (EXIT_SUCCESS);	
}