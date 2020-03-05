#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

SDL_Window * window;
SDL_Renderer * renderer;
SDL_Surface * surface;
SDL_Texture * texture;

SDL_Color white = {255, 255, 255, 255};

typedef struct {
	
	TTF_Font 	* txt_font;
	SDL_Texture * txt_texture;
	SDL_Rect 	txt_rect;
	
} SDL_StructText;

void Helper_DebugLogs(const char*text);
void Helper_DebugPrint(const char*text);

void Helper_CreateTextureFromText(SDL_Window *w, SDL_StructText *st, const char*text, const char*p, int size, int y, int x, SDL_Color color);
void Helper_DestroyStructText(SDL_StructText * st);

int main(void) {
	
	romfsInit();
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	
	window = SDL_CreateWindow("n/a", 0, 0, 1280, 720, 0);
	renderer = SDL_CreateRenderer(window, 0 , SDL_RENDERER_ACCELERATED);
	
	texture = IMG_LoadTexture(renderer, "romfs:/background.png");
	
	SDL_StructText Title = {0};
	Helper_CreateTextureFromText(window, &Title, "hello there!", "romfs:/aquawax.ttf", 36, 10, 10, white);
	
	SDL_StructText comment = {0};
	Helper_CreateTextureFromText(window, &comment, "This is a test to see if its working!", "romfs:/aquawax.ttf", 36, 150, 150, white);
	
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

void Helper_DebugLogs(const char*text) {
	FILE * fd = fopen("sdmc:/sdl2-log", "a");
	fprintf(fd, "sdl2-log: %s\n", text);
	fclose(fd);
}

void Helper_DebugPrint(const char*text) {
    consoleInit(NULL);

    printf("Helper: %s", text);

    while(appletMainLoop())
    {
        hidScanInput();
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS) break;

        consoleUpdate(NULL);
    }

    consoleExit(NULL);
    return;
}

void Helper_CreateTextureFromText(SDL_Window w, SDL_StructText *st, const char*text, const char*p, int size, int y, int x, SDL_Color color) {
	
	SDL_StructText pd;
	pd.txt_font = TTF_OpenFont(p, size);
	
	SDL_Renderer * r = SDL_CreateRenderer(&w, 0 , SDL_RENDERER_ACCELERATED);
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