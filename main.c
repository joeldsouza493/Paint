#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "paint.h"


int main(int argc, char *argv[]) {
	
	Tool tool;
	SDL_Window *window = NULL;
	SDL_Surface *canvas = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *texture[NO_ICONS];

	//defining coordinates and dimensions for icons
	SDL_Rect dst[NO_ICONS];

	dst[undo].x = UNDO_X;
	dst[undo].y = UNDO_Y;
	dst[undo].w = UNDO_W;
	dst[undo].h = UNDO_H;

	dst[redo].x = REDO_X;
	dst[redo].y = REDO_Y;
	dst[redo].w = REDO_W;
	dst[redo].h = REDO_H;

	dst[hand].x = HAND_X;
	dst[hand].y = HAND_Y;
	dst[hand].w = HAND_W;
	dst[hand].h = HAND_H;
        
	dst[line].x = LINE_X;
	dst[line].y = LINE_Y;
	dst[line].w = LINE_W;
	dst[line].h = LINE_H;

	dst[rectangle].x = RECTANGLE_X;
	dst[rectangle].y = RECTANGLE_Y;
	dst[rectangle].w = RECTANGLE_W;
	dst[rectangle].h = RECTANGLE_H;

	dst[ellipse].x = ELLIPSE_X;
	dst[ellipse].y = ELLIPSE_Y;
	dst[ellipse].w = ELLIPSE_W;
	dst[ellipse].h = ELLIPSE_H;
	
	dst[polygon].x = POLYGON_X;
	dst[polygon].y = POLYGON_Y;
	dst[polygon].w = POLYGON_W;
	dst[polygon].h = POLYGON_H;

	dst[fillcolor].x = FILLCOLOR_X;
	dst[fillcolor].y = FILLCOLOR_Y;
	dst[fillcolor].w = FILLCOLOR_W;
	dst[fillcolor].h = FILLCOLOR_H;

	dst[brush].x = BRUSH_X;
	dst[brush].y = BRUSH_Y;
	dst[brush].w = BRUSH_W;
	dst[brush].h = BRUSH_H;

	dst[getcolor].x = GETCOLOR_X;
	dst[getcolor].y = GETCOLOR_Y;
	dst[getcolor].w = GETCOLOR_W;
	dst[getcolor].h = GETCOLOR_H;

	dst[spray].x = SPRAY_X;
	dst[spray].y = SPRAY_Y;
	dst[spray].w = SPRAY_W;
	dst[spray].h = SPRAY_H;
	
	dst[eraser].x = ERASER_X;
	dst[eraser].y = ERASER_Y;
	dst[eraser].w = ERASER_W;
	dst[eraser].h = ERASER_H;

	//initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
        
	//initialize window
	window = SDL_CreateWindow("Paint", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 960, SDL_WINDOW_SHOWN);
        if(window == NULL){
                printf("Could not create Window: %s\n", SDL_GetError());
                exit(1);
        }
	
	canvas = SDL_GetWindowSurface(window);
	//initialize renderer
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_RenderClear(renderer);

	//initialize texture
        texture[undo] = IMG_LoadTexture(renderer, "./bitmaps/undo.bmp");
        texture[redo] = IMG_LoadTexture(renderer, "./bitmaps/redo.bmp");
        texture[hand] = IMG_LoadTexture(renderer, "./bitmaps/hand.bmp");
        texture[line] = IMG_LoadTexture(renderer, "./bitmaps/line.bmp");
        texture[rectangle] = IMG_LoadTexture(renderer, "./bitmaps/rectangle.bmp");
        texture[ellipse] = IMG_LoadTexture(renderer, "./bitmaps/ellipse.bmp");
        texture[polygon] = IMG_LoadTexture(renderer, "./bitmaps/polygon.bmp");
        texture[fillcolor] = IMG_LoadTexture(renderer, "./bitmaps/fillcolor.bmp");
        texture[brush] = IMG_LoadTexture(renderer, "./bitmaps/brush.bmp");
        texture[getcolor] = IMG_LoadTexture(renderer, "./bitmaps/getcolor.bmp");
        texture[spray] = IMG_LoadTexture(renderer, "./bitmaps/spray.bmp");
        texture[eraser] = IMG_LoadTexture(renderer, "./bitmaps/eraser.bmp");

	//
	SDL_Event ev;
	int i, quitflag = 0;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);	
	SDL_RenderFillRect(renderer, NULL);
	
	//render toolbox
	for(i = undo; i <= eraser; i++) {
		SDL_RenderCopy(renderer, texture[i], NULL, &dst[i]);
		SDL_RenderPresent(renderer);
	}
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(renderer, CANVAS_X - 2, CANVAS_Y, CANVAS_X - 2, CANVAS_Y + CANVAS_H);

	while(1) {
		if(SDL_PollEvent(&ev)) {
			if(ev.type == SDL_QUIT)
				break;
			
			else if(ev.type == SDL_MOUSEBUTTONUP) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				if(x > LINE_X && x < LINE_X + LINE_W && y > LINE_Y && y < LINE_Y + LINE_Y) {
					drawLine(renderer, &ev, &dst[line]);
					
				}
					
				else if(x > HAND_X && x < HAND_X + HAND_W && y > HAND_Y && y < HAND_Y + HAND_H) {
					drawHand(renderer, &ev, &dst[hand]);
				}
			
						
				else if(x > dst[rectangle].x && x < dst[rectangle].x + dst[rectangle].w && y > dst[rectangle].y && y < dst[rectangle].y + dst[rectangle].h ) {
					drawRectangle(renderer, &ev, &dst[rectangle]);
				}
			
			}		
/*				else if(x > dst[ellipse].x && x < dst[ellipse].x + dst[ellipse].w && y > dst[ellipse].y && y < dst[ellipse].y + dst[ellipse].h ) {
					drawEllipse(renderer, &ev, &dst[ellipse]);
				}
			}	
				else if(x > dst[fillcolor].x && x < dst[fillcolor].x + dst[fillcolor].w && y > dst[fillcolor].y && y < dst[fillcolor].y + dst[fillcolor].h ){
				}
				
				else if(x > dst[brush].x && x < dst[brush].x + dst[brush].w && y > dst[brush].y && y < dst[brush].y + dst[brush].h) {	
				}

				else if(x > dst[getcolor].x && x < dst[getcolor].x + dst[getcolor].w && y > dst[getcolor].y && y < dst[getcolor].y + dst[getcolor].h ) {
				}

				else if(x > dst[spray].x && x < dst[spray].x + dst[spray].w && y > dst[spray].y && y < dst[spray].y + dst[spray].h ){
				}

				else if(x > dst[eraser].x && x < dst[eraser].x + dst[eraser].w && y > dst[eraser].y && y < dst[eraser].y + dst[eraser].h ){
				}

				else if(x > dst[undo].x && x < dst[undo].x + dst[undo].w && y > dst[undo].y && y < dst[undo].y + dst[undo].h ) {				}

				else if(x > dst[redo].x && x < dst[redo].x + dst[redo].w && y > dst[redo].y && y < dst[redo].y + dst[redo].h ) {
				}

			}*/
		}
		SDL_RenderPresent(renderer);
//		SDL_RenderClear(renderer);
	}

	for(i = undo; i <= eraser; i++) 
		SDL_DestroyTexture(texture[i]);
	SDL_FreeSurface(canvas);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void drawLine(SDL_Renderer *renderer, SDL_Event *ev, SDL_Rect *dst) {
	int x, y, x2, y2;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, dst);
	SDL_RenderPresent(renderer);
	while(1) {
		if(SDL_PollEvent(ev)) {
			if(ev->type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetMouseState(&x, &y);
				if(x < CANVAS_X) {
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderDrawRect(renderer, dst);
					SDL_RenderPresent(renderer);
					return;
				}
			}
		
			else if(ev->type == SDL_MOUSEBUTTONUP && x > CANVAS_X) {
				SDL_GetMouseState(&x2, &y2);
				SDL_RenderDrawLine(renderer, x, y, x2, y2);
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderDrawRect(renderer, dst);
				SDL_RenderPresent(renderer);
				return;
			}	
			else if(ev->type == SDL_MOUSEMOTION && x > CANVAS_X && x2 > CANVAS_X) {
				SDL_GetMouseState(&x2, &y2);
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawLine(renderer, x, y, x2, y2);
				SDL_RenderPresent(renderer);
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------

void drawHand(SDL_Renderer *renderer, SDL_Event *ev, SDL_Rect *dst) {
	int x1, y1, x2, y2;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, dst);
	SDL_RenderPresent(renderer);
	while(1) {
		if(SDL_PollEvent(ev)) {
			if(ev->type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetMouseState(&x1, &y1);
				if(x1 < CANVAS_X) {
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderDrawRect(renderer, dst);
					SDL_RenderPresent(renderer);
					return;
				}
			}
			else if(ev->type == SDL_MOUSEBUTTONUP && x2 > CANVAS_X) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderDrawRect(renderer, dst);
				SDL_RenderPresent(renderer);
				return;
			}	
			else if(ev->type == SDL_MOUSEMOTION && x1 > CANVAS_X && y1 > CANVAS_Y) {
				SDL_GetMouseState(&x2, &y2);	
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
				x1 = x2;
				y1 = y2;
				SDL_RenderPresent(renderer);
			}
		}
	}
}

//------------------------------------------------------------------------------------------------------------------

void drawRectangle(SDL_Renderer *renderer, SDL_Event *ev, SDL_Rect *dst) {
	dst->x = dst->x - 1;
	dst->w = dst->w + 2;
	dst->h = dst->h + 1;
	int x1, y1, x2, y2;
	SDL_Rect rect;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, dst);
	SDL_RenderPresent(renderer);
	while(1) {
		if(SDL_PollEvent(ev)) {
			if(ev->type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetMouseState(&x1, &y1);
				if(x1 < CANVAS_X) {
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderDrawRect(renderer, dst);
					SDL_RenderPresent(renderer);
					return;
				}
				rect.x = x1;
				rect.y = y1;
			}
			else if(ev->type == SDL_MOUSEBUTTONUP && x2 > CANVAS_X) {
				SDL_GetMouseState(&x2, &y2);
				rect.w = x2 - x1;
				rect.h = y2 - y1;
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(renderer, &rect);
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderDrawRect(renderer, dst);
				SDL_RenderPresent(renderer);
				return;
			}
			else if(ev->type == SDL_MOUSEMOTION && x1 > CANVAS_X && x2 > CANVAS_X) {
				SDL_GetMouseState(&x2, &y2);
				rect.w = x2 - x1;
				rect.h = y2 - y1;
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(renderer, &rect);
				SDL_RenderPresent(renderer);
			}
		}
		else 
			return;
	}
}

//------------------------------------------------------------------------------------------------------------------
/*
void drawEllipse(SDL_Renderer *renderer, SDL_Event *ev, SDL_Rect *dst) {
	int x1, y1, x2, y2, x, y, w, h;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, dst);
	SDL_RenderPresent(renderer);
	
	while(1) {
		if(SDL_PollEvent(ev)) {
			if(ev->type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetMouseState(&x1, &x2);
				if(x1 < CANVAS_X) {
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderDrawRect(renderer, dst);
					SDL_RenderPresent(renderer);
					return;
				}
			}
			else if(ev->type == SDL_MOUSEBUTTONUP && x2 > CANVAS_X) {
				SDL_GetMouseState(&x2, &y2);
				x = (x1 + x2) / 2;
				y = (y1 + y2) / 2;
				w = x2 - x1;
				h = y2 - y1;
				SDL_RenderDrawEllipse(renderer, x, y, w, h);
				SDL_RenderPresent(renderer);
				return;
			}
		}
		else
			return;
	}
}*/
				
