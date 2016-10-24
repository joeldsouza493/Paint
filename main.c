#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "paint.h"


int main(int argc, char *argv[]) {
	
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

	dst[palette].x = PALETTE_X;
	dst[palette].y = PALETTE_Y;
	dst[palette].w = PALETTE_W;
	dst[palette].h = PALETTE_H;
	

	//initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
        
	//initialize window
	window = SDL_CreateWindow("Paint", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 960, SDL_WINDOW_SHOWN);
        if(window == NULL){
                printf("Could not create Window: %s\n", SDL_GetError());
                exit(1);
        }
	
	canvas = SDL_GetWindowSurface(window);
	//if(canvas)
	//	printf("Boo YEAH!!\n");
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
	int i, x, y;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);	
	SDL_RenderFillRect(renderer, NULL);
	
	//render toolbox
	for(i = undo; i <= eraser; i++) {
		SDL_RenderCopy(renderer, texture[i], NULL, &dst[i]);
		SDL_RenderPresent(renderer);
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &dst[palette]);
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(renderer, CANVAS_X - 2, CANVAS_Y, CANVAS_X - 2, CANVAS_Y + CANVAS_H);

	SDL_Event ev;

	while(1) {
		if(SDL_PollEvent(&ev)) {
			if(ev.type == SDL_QUIT) {
				break;
			}
			
			else if(ev.type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetMouseState(&x, &y);
				if(x > LINE_X && x < LINE_X + LINE_W && y > LINE_Y && y < LINE_Y + LINE_Y) {
					if(drawLine(renderer,/* &ev,*/ dst[line]) == 0)
						break;
				}
					
				else if(x > HAND_X && x < HAND_X + HAND_W && y > HAND_Y && y < HAND_Y + HAND_H) {
					if(!drawHand(renderer,/* &ev,*/ dst[hand]))
						break;
				}
			
						
				else if(x > RECTANGLE_X && x < RECTANGLE_X + RECTANGLE_W && y > RECTANGLE_Y && y < RECTANGLE_Y + RECTANGLE_H ) {
					if(!drawRectangle(renderer,/* &ev,*/ dst[rectangle]))
						break;
				}
			
					
/*				else if(x > dst[ellipse].x && x < dst[ellipse].x + dst[ellipse].w && y > dst[ellipse].y && y < dst[ellipse].y + dst[ellipse].h ) {
					drawEllipse(renderer, &ev, &dst[ellipse]);
				}*/
				else if(x > POLYGON_X && x < POLYGON_X + POLYGON_W && y > POLYGON_Y && y < POLYGON_Y + POLYGON_H) {
					if(!drawPolygon(renderer,/* &ev,*/ dst[polygon]))
						break;
				}
			
/*					
				else if(x > dst[fillcolor].x && x < dst[fillcolor].x + dst[fillcolor].w && y > dst[fillcolor].y && y < dst[fillcolor].y + dst[fillcolor].h ){
				}
				*/
				else if(x > BRUSH_X && x < BRUSH_X + BRUSH_W && y > BRUSH_Y && y < BRUSH_Y + BRUSH_H) {	
					if(!drawBrush(renderer,/* &ev,*/ dst[brush]))
						break;
				}

				else if(x > GETCOLOR_X && x < GETCOLOR_X + GETCOLOR_W && y > GETCOLOR_Y && y < GETCOLOR_Y + GETCOLOR_H) {
					if(!getColor(renderer, dst[getcolor], dst[palette], canvas))
						break;
				}
/*
				else if(x > dst[spray].x && x < dst[spray].x + dst[spray].w && y > dst[spray].y && y < dst[spray].y + dst[spray].h ){
				}*/

				else if(x > ERASER_X && x < ERASER_X + ERASER_W && y > ERASER_Y && y < ERASER_Y + ERASER_H){
					if(!drawEraser(renderer,/* &ev,*/ dst[eraser]))
						break;
				}/*

				else if(x > dst[undo].x && x < dst[undo].x + dst[undo].w && y > dst[undo].y && y < dst[undo].y + dst[undo].h ) {				}

				else if(x > dst[redo].x && x < dst[redo].x + dst[redo].w && y > dst[redo].y && y < dst[redo].y + dst[redo].h ) {
				}*/
				
				else if(x > PALETTE_X && x < PALETTE_X + PALETTE_W && y > PALETTE_Y && y < PALETTE_Y + PALETTE_H) {
					Palette(renderer, dst[palette]);
				}
			}
		}
		SDL_RenderPresent(renderer);
	}
	printf("quit");

	for(i = undo; i <= eraser; i++) 
		SDL_DestroyTexture(texture[i]);
	SDL_FreeSurface(canvas);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int drawLine(SDL_Renderer *renderer,/* SDL_Event *ev,*/ SDL_Rect dst) {
	int x1, y1, x2, y2, flag = 0;
	SDL_Event ev;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &dst);
	SDL_RenderPresent(renderer);
	while(1) {
		if(SDL_PollEvent(&ev)) {
			if(ev.type == SDL_QUIT) {
				return 0;
			}	
			else if(ev.button.button == SDL_BUTTON_RIGHT) {
		                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    	                        SDL_RenderDrawRect(renderer, &dst);
       	                        SDL_RenderPresent(renderer);
                                return 1;
			}
			else if(ev.type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetMouseState(&x1, &y1);
				flag = 1;
				if(x1 < CANVAS_X) {
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderDrawRect(renderer, &dst);
					SDL_RenderPresent(renderer);
					return 1;
				}
			}
		
			else if(ev.type == SDL_MOUSEBUTTONUP && x1 > CANVAS_X) {
				SDL_GetMouseState(&x2, &y2);
				SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
				flag = 0;
			}	
			else if(ev.type == SDL_MOUSEMOTION && x1 > CANVAS_X && x2 > CANVAS_X && flag == 1) {
				SDL_GetMouseState(&x2, &y2);
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
				SDL_RenderPresent(renderer);
			}
		}
	}
	return 0;
}
//-------------------------------------------------------------------------------------------------------------------------------

int drawHand(SDL_Renderer *renderer,/* SDL_Event *ev, */SDL_Rect dst) {
	int x1, y1, x2, y2, flag = 0;
	SDL_Event ev;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &dst);
	SDL_RenderPresent(renderer);
	while(1) {
		if(SDL_PollEvent(&ev)) {
			if(ev.type == SDL_QUIT) {
				return 0;
			}	
			if(ev.button.button == SDL_BUTTON_RIGHT) {
		                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    	                        SDL_RenderDrawRect(renderer, &dst);
       	                        SDL_RenderPresent(renderer);
                                return 1;
			}
			if(ev.type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetMouseState(&x1, &y1);
				if(x1 < CANVAS_X || ev.button.button == SDL_BUTTON_RIGHT) {
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderDrawRect(renderer, &dst);
					SDL_RenderPresent(renderer);
					return 1;
				}
				flag = 1;
			}
			else if(ev.type == SDL_MOUSEBUTTONUP && x2 > CANVAS_X) {
				flag = 0;
			}	
			else if(ev.type == SDL_MOUSEMOTION && x1 > CANVAS_X && y1 > CANVAS_Y && flag == 1) {
				SDL_GetMouseState(&x2, &y2);	
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
				x1 = x2;
				y1 = y2;
				SDL_RenderPresent(renderer);
			}
		}
	}
	return 0;
}

//------------------------------------------------------------------------------------------------------------------

int drawRectangle(SDL_Renderer *renderer,/* SDL_Event *ev,*/ SDL_Rect dst) {
	SDL_Event ev;
	dst.x = dst.x - 1;
	dst.w = dst.w + 2;
	dst.h = dst.h + 1;
	int x1, y1, x2, y2, flag = 0;
	SDL_Rect rect;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &dst);
	SDL_RenderPresent(renderer);
	while(1) {
		if(SDL_PollEvent(&ev)) {
			if(ev.type == SDL_QUIT) {
				return 0;
			}	
			if(ev.button.button == SDL_BUTTON_RIGHT) {
		                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    	                        SDL_RenderDrawRect(renderer, &dst);
       	                        SDL_RenderPresent(renderer);
                                return 1;
			}
			if(ev.type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetMouseState(&x1, &y1);
				if(x1 < CANVAS_X || ev.button.button == SDL_BUTTON_RIGHT) {
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderDrawRect(renderer, &dst);
					SDL_RenderPresent(renderer);
					return 1;
				}
				rect.x = x1;
				rect.y = y1;
				flag = 1;
			}
			else if(ev.type == SDL_MOUSEBUTTONUP && x2 > CANVAS_X && flag == 1) {
				SDL_GetMouseState(&x2, &y2);
				rect.w = x2 - x1;
				rect.h = y2 - y1;
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(renderer, &rect);
				flag = 0;
			}
			else if(ev.type == SDL_MOUSEMOTION && flag == 1) {
				SDL_GetMouseState(&x2, &y2);
				rect.w = x2 - x1;
				rect.h = y2 - y1;
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(renderer, &rect);
				SDL_RenderPresent(renderer);
			}
		}
	}
	return 0;
}

//------------------------------------------------------------------------------------------------------------------
/*
int drawEllipse(SDL_Renderer *renderer, SDL_Event *ev, SDL_Rect *dst) {
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
					return 1;
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
				return 1;
			}
		}
		else
			return 1;
	}
}*/

//---------------------------------------------------------------------------------------------------------------

int drawPolygon(SDL_Renderer *renderer,/* SDL_Event *ev,*/ SDL_Rect dst) {
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	SDL_Event ev;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &dst);
	SDL_RenderPresent(renderer);
	while(1) {
		if(SDL_PollEvent(&ev)) {
			if(ev.type == SDL_QUIT) {
				return 0;
			}	
			if(ev.button.button == SDL_BUTTON_RIGHT) {
		                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    	                        SDL_RenderDrawRect(renderer, &dst);
       	                        SDL_RenderPresent(renderer);
                                return 1;
			}
			if(ev.type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetMouseState(&x2, &y2);
				if(x2 < CANVAS_X || ev.button.button == SDL_BUTTON_RIGHT) {
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderDrawRect(renderer, &dst);
					SDL_RenderPresent(renderer);
					return 1;
				}
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				if(x1 != 0 && y1 != 0) {
					SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
					SDL_RenderPresent(renderer);
				}
				x1 = x2;
				y1 = y2;
			}
			else if(ev.type == SDL_MOUSEMOTION && x1 > CANVAS_X && x2 > CANVAS_X) {
				SDL_GetMouseState(&x2, &y2);
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
				SDL_RenderPresent(renderer);
			}
		}
	}
	return 0;
}

//---------------------------------------------------------------------------------------------------------------------

int drawEraser(SDL_Renderer *renderer,/* SDL_Event *ev,*/ SDL_Rect dst) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &dst);
	SDL_RenderPresent(renderer);
	SDL_Event ev;
	int x, y, flag = 0;
	SDL_Rect r;
	while(1) {
		if(SDL_PollEvent(&ev)) {
			if(ev.type == SDL_QUIT) {
				return 0;
			}	
			if(ev.button.button == SDL_BUTTON_RIGHT) {
		                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    	                        SDL_RenderDrawRect(renderer, &dst);
       	                        SDL_RenderPresent(renderer);
                                return 1;
			}
			if(ev.type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetMouseState(&x, &y);
				if(x < CANVAS_X || ev.button.button == SDL_BUTTON_RIGHT) {
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderDrawRect(renderer, &dst);
					SDL_RenderPresent(renderer);
					return 1;
				}
				flag = 1;
			}
			else if(ev.type == SDL_MOUSEMOTION && flag == 1) {
				SDL_GetMouseState(&x, &y);
				r.x = x - 5;
				r.y = y - 5;
				if(x > CANVAS_X + 5) {
					r.w = 10;
					r.h = 10;
				}
				else if(x < CANVAS_X + 5) {
					r.w = 0;
					r.h = 0;
				}
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderFillRect(renderer, &r);
				SDL_RenderPresent(renderer);
			}
			else if(ev.type == SDL_MOUSEBUTTONUP && flag == 1) {	
				SDL_GetMouseState(&x, &y);
				r.x = x - 5;
				r.y = y - 5;
				if(x > CANVAS_X + 5) {
					r.w = 10;
					r.h = 10;
				}
				else if(x < CANVAS_X + 5) {
					r.w = 0;
					r.h = 0;
				}
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderFillRect(renderer, &r);
				SDL_RenderPresent(renderer);
				flag = 0;
			}
		}
	}
	return 0;
}

//-----------------------------------------------------------------------------------------------------------
int drawBrush(SDL_Renderer *renderer,/* SDL_Event *ev,*/ SDL_Rect dst) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &dst);
	SDL_RenderPresent(renderer);
	int x, y, flag = 0;
	SDL_Event ev;
	SDL_Rect r;
	while(1) {
		if(SDL_PollEvent(&ev)) {
			if(ev.type == SDL_QUIT) {
				return 0;
			}	
			if(ev.button.button == SDL_BUTTON_RIGHT) {
		                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    	                        SDL_RenderDrawRect(renderer, &dst);
       	                        SDL_RenderPresent(renderer);
                                return 1;
			}
			if(ev.type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetMouseState(&x, &y);
				if(x < CANVAS_X || ev.button.button == SDL_BUTTON_RIGHT) {
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderDrawRect(renderer, &dst);
					SDL_RenderPresent(renderer);
					return 1;
				}
				flag = 1;
			}
			else if(ev.type == SDL_MOUSEMOTION && flag == 1) {
				SDL_GetMouseState(&x, &y);
				r.x = x - 5;
				r.y = y - 5;
				if(x > CANVAS_X + 5) {
					r.w = 10;
					r.h = 3;
				}
				else if(x < CANVAS_X + 5) {
					r.w = 0;
					r.h = 0;
				}
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderFillRect(renderer, &r);
				SDL_RenderPresent(renderer);
			}
			else if(ev.type == SDL_MOUSEBUTTONUP && flag == 1) {
				SDL_GetMouseState(&x, &y);
				r.x = x - 5;
				r.y = y - 5;
				if(x > CANVAS_X + 5) {
					r.w = 10;
					r.h = 3;
				}
				else if(x < CANVAS_X + 5) {
					r.w = 0;
					r.h = 0;
				}
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderFillRect(renderer, &r);
				SDL_RenderPresent(renderer);
				
				flag = 0;
			}
		}
	}
	return 0;
}

//------------------------------------------------------------------------------------------------------

int getColor(SDL_Renderer *renderer, SDL_Rect dst1, SDL_Rect dst2, SDL_Surface *canvas) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &dst1);
	SDL_RenderPresent(renderer);
	int x, y;
	SDL_Event ev;
	while(1) {
		if(SDL_PollEvent(&ev)) {
			if(ev.type == SDL_QUIT) {
				return 0;	
			}
			if(ev.button.button == SDL_BUTTON_RIGHT) {
		                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    	                        SDL_RenderDrawRect(renderer, &dst1);
       	                        SDL_RenderPresent(renderer);
                                return 1;
			}
			if(ev.type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetMouseState(&x, &y);
				if(x < CANVAS_X || ev.button.button == SDL_BUTTON_RIGHT) {
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderDrawRect(renderer, &dst1);
					SDL_RenderPresent(renderer);
					return 1;
				}
				printf("Hello");
				SDL_GetRGBA(getPixel(canvas, x, y), canvas->format, &(Color.r), &(Color.g), &(Color.b), &(Color.a));
				SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, Color.a);
				SDL_RenderFillRect(renderer, &dst2);
				SDL_RenderPresent(renderer);
				
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderDrawRect(renderer, &dst1);
				SDL_RenderPresent(renderer);
			}
		}
	}
	return 0;
}
				
//--------------------------------------------------------------------------------------------------------------		
Uint32 getPixel( SDL_Surface *surface, int x, int y )
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;
    
    //Get the requested pixel
    return pixels[ ( y * surface->w ) + x ];
}

/*Uint32 getPixel(SDL_Surface *surface, int x, int y){
	int bpp = surface->format->BytesPerPixel;
	Uint32 *p = (Uint32 *)surface->pixels + y * surface->pitch + x * bpp;
	switch(bpp) {
		case 1:
			return *p;

		case 2:
			return *(Uint16 *)p;

		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;

		case 4:
			return *(Uint32 *)p;

		default:
			return 0;
	}
}*/

//--------------------------------------------------------------------------------------------------------------------

int Palette(SDL_Renderer *renderer, SDL_Rect dst) {

	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &dst);
	SDL_RenderPresent(renderer);
	
	SDL_Rect col[NO_COLORS];
	SDL_Color color[NO_COLORS];

	col[black].x = BLACK_X;
	col[black].y = BLACK_Y;
	col[black].w = BLACK_W;
	col[black].h = BLACK_H;

	col[white].x = WHITE_X;
	col[white].y = WHITE_Y;
	col[white].w = WHITE_W;
	col[white].h = WHITE_H;
	
	col[red].x = RED_X;
	col[red].y = RED_Y;
	col[red].w = RED_W;
	col[red].h = RED_H;

	col[lime].x = LIME_X;
	col[lime].y = LIME_Y;
	col[lime].w = LIME_W;
	col[lime].h = LIME_H;

	col[blue].x = BLUE_X;
	col[blue].y = BLUE_Y;
	col[blue].w = BLUE_W;
	col[blue].h = BLUE_H;	
	
	col[yellow].x = YELLOW_X;
	col[yellow].y = YELLOW_Y;
	col[yellow].w = YELLOW_W;
	col[yellow].h = YELLOW_H;

	col[aqua].x = AQUA_X;
	col[aqua].y = AQUA_Y;
	col[aqua].w = AQUA_W;
	col[aqua].h = AQUA_H;

	col[magenta].x = MAGENTA_X;
	col[magenta].y = MAGENTA_Y;
	col[magenta].w = MAGENTA_W;
	col[magenta].h = MAGENTA_H;

	col[silver].x = SILVER_X;
	col[silver].y = SILVER_Y;
	col[silver].w = SILVER_W;
	col[silver].h = SILVER_H;

	col[gray].x = GRAY_X;
	col[gray].y = GRAY_Y;
	col[gray].w = GRAY_W;
	col[gray].h = GRAY_H;
	
	col[maroon].x = MAROON_X;
	col[maroon].y = MAROON_Y;
	col[maroon].w = MAROON_W;
	col[maroon].h = MAROON_H;

	col[olive].x = OLIVE_X;
	col[olive].y = OLIVE_Y;
	col[olive].w = OLIVE_W;
	col[olive].h = OLIVE_H;

	col[green].x = GREEN_X;
	col[green].y = GREEN_Y;
	col[green].w = GREEN_W;
	col[green].h = GREEN_H;

	col[purple].x = PURPLE_X;
	col[purple].y = PURPLE_Y;
	col[purple].w = PURPLE_W;
	col[purple].h = PURPLE_H;

	col[teal].x = TEAL_X;
	col[teal].y = TEAL_Y;
	col[teal].w = TEAL_W;
	col[teal].h = TEAL_H;

	col[white].x = NAVY_X;
	col[white].y = NAVY_Y;
	col[white].w = NAVY_W;
	col[white].h = NAVY_H;
//-------------------------------------------------------

	color[black].r = BLACK_R;
	color[black].g = BLACK_G;
	color[black].b = BLACK_B;
	color[black].a = BLACK_A;
	
	color[white].r = WHITE_R;
	color[white].g = WHITE_G;
	color[white].b = WHITE_B;
	color[white].a = WHITE_A;

	color[red].r = RED_R;
	color[red].g = RED_G;
	color[red].b = RED_B;
	color[red].a = RED_A;

	color[lime].r = LIME_R;
	color[lime].g = LIME_G;
	color[lime].b = LIME_B;
	color[lime].a = LIME_A;

	color[blue].r = BLUE_R;
	color[blue].g = BLUE_G;
	color[blue].b = BLUE_B;
	color[blue].a = BLUE_A;

	color[yellow].r = YELLOW_R;
	color[yellow].g = YELLOW_G;
	color[yellow].b = YELLOW_B;
	color[yellow].a = YELLOW_A;

	color[aqua].r = AQUA_R;
	color[aqua].g = AQUA_G;
	color[aqua].b = AQUA_B;
	color[aqua].a = AQUA_A;

	color[magenta].r = MAGENTA_R;
	color[magenta].g = MAGENTA_G;
	color[magenta].b = MAGENTA_B;
	color[magenta].a = MAGENTA_A;
	
	color[silver].r = SILVER_R;
	color[silver].g = SILVER_G;
	color[silver].b = SILVER_B;
	color[silver].a = SILVER_A;

	color[gray].r = GRAY_R;
	color[gray].g = GRAY_G;
	color[gray].b = GRAY_B;
	color[gray].a = GRAY_A;

	color[maroon].r = MAROON_R;
	color[maroon].g = MAROON_G;
	color[maroon].b = MAROON_B;
	color[maroon].a = MAROON_A;

	color[olive].r = OLIVE_R;
	color[olive].g = OLIVE_G;
	color[olive].b = OLIVE_B;
	color[olive].a = OLIVE_A;
	
	color[green].r = GREEN_R;
	color[green].g = GREEN_G;
	color[green].b = GREEN_B;
	color[green].a = GREEN_A;
	
	color[purple].r = PURPLE_R;
	color[purple].g = PURPLE_G;
	color[purple].b = PURPLE_B;
	color[purple].a = PURPLE_A;

	color[teal].r = TEAL_R;
	color[teal].g = TEAL_G;
	color[teal].b = TEAL_B;
	color[teal].a = TEAL_A;

	color[navy].r = NAVY_R;
	color[navy].g = NAVY_G;
	color[navy].b = NAVY_B;
	color[navy].a = NAVY_A;

	int i, x, y;
	SDL_Window *window = NULL;
	SDL_Renderer *r = NULL;

	window = SDL_CreateWindow("Color Palette", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 240, SDL_WINDOW_SHOWN);
        if(window == NULL){
                printf("Could not create Window: %s\n", SDL_GetError());
                exit(1);
        }
        r = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderClear(r);

	SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
	SDL_RenderFillRect(r, NULL);

	for(i = 0; i < NO_COLORS; i++) {
		SDL_SetRenderDrawColor(r, color[i].r, color[i].g, color[i].b, color[i].a);
		SDL_RenderFillRect(r, &col[i]);
		SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
		SDL_RenderDrawRect(r, &col[i]);
	}
						
	SDL_Event ev;
	
	while(1) {
		if(SDL_PollEvent(&ev)) {
			if(ev.type == SDL_QUIT)
				break;
			else if(ev.type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetMouseState(&x, &y);
				if(x > WHITE_X && x < WHITE_X + WHITE_W && y > WHITE_Y && y < WHITE_Y + WHITE_H) {
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					break;
				}
//				SDL_GetRGBA(getPixel(csurface, x, y), csurface->format, &(Color.r), &(Color.g), &(Color.b), &(Color.a));
				if(Color.r == 255 && Color.g == 255 && Color.b == 255)
					continue;
				SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, Color.a);
				break;
			}
		}
	}

        SDL_DestroyRenderer(r);
        SDL_DestroyWindow(window);
	SDL_Quit();

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &dst);
	SDL_RenderPresent(renderer);
	
	return 0;
}

//-----------------------------------------------------------------------------------------------------------
/*
int fillColor(SDL_Renderer *renderer, SDL_Rect dst) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &dst);
	SDL_RenderPresent(renderer);

	SDL_Event ev;
	int x, y;

	while(1) {
		if(SDL_PollEvent(ev)) {
			if(ev.type == SDL_QUIT)
				return 0;
			else if(ev.button.button == SDL_BUTTON_RIGHT) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderDrawColor(renderer, &dst);
				SDL_RenderPresent(renderer);
				return 1;
			}
			else if(ev.type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetMouseState(&x, &y);
				if(x < CANVAS_X || ev.button.button == SDL_BUTTON_RIGHT) {
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderDrawRect(renderer, &dst);
					SDL_RenderPresent(renderer);
					return 1;
				}
				floodFill();
			}
		}
	}
	return 0;
}
*/
//-------------------------------------------------------------------------------


