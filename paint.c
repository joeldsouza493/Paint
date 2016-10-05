#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "paint.h"

/*void LoadTexture(char* filePath, SDL_Renderer *renderTarget, SDL_Texture *texture) {
        SDL_Surface *surface = SDL_LoadBMP(filePath);
        texture = NULL;
        if(!surface) {
                exit(2);
        }
        else {
                texture = SDL_CreateTextureFromSurface(renderTarget, surface);
                if(texture == NULL) {
                        exit(3);
                }
        }
        SDL_FreeSurface(surface);
}
*/
void initscr(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture) {

	SDL_Init(SDL_INIT_EVERYTHING);	
	window = SDL_CreateWindow("Paint", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 960, SDL_WINDOW_SHOWN);
	if(window == NULL){
		printf("Could not create Window: %s\n", SDL_GetError());
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderClear(renderer);
	texture = IMG_LoadTexture(renderer, "./bitmaps/line.bmp");
	
}

	





/*


	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	SDL_Surface *currentImage = NULL;
	currentImage = SDL_LoadBMP("./bitmaps/line.bmp");
	texture[0] = SDL_CreateTextureFromSurface(renderer, currentImage);
	SDL_Rect dst;
	dst.x = 10;
	dst.y = 10;
	dst.w = 10;
	dst.h = 10;
	doRender(renderer, texture);
}
void doRender(SDL_Renderer *renderer, SDL_Texture **texture) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderCopy(renderer, texture[0], NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_Delay(5000);

*/
