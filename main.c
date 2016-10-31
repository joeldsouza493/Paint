#include "paint.h"

stack a, b;

int main(int argc, char *argv[]) {
	
	SDL_Window *window = NULL;
	SDL_Texture *screen= NULL;
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

	dst[palettetool].x = PALETTE_X;
	dst[palettetool].y = PALETTE_Y;
	dst[palettetool].w = PALETTE_W;
	dst[palettetool].h = PALETTE_H;
	
	dst[save].x = SAVE_X;
	dst[save].y = SAVE_Y;
	dst[save].w = SAVE_W;
	dst[save].h = SAVE_H;

	//initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
        
	//initialize window
	window = SDL_CreateWindow("Paint", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 960, SDL_WINDOW_SHOWN);
        if(window == NULL){
                printf("Could not create Window: %s\n", SDL_GetError());
                exit(1);
        }
	
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_RenderClear(renderer);
	
	screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_RENDERER_TARGETTEXTURE, 1280, 960);
	SDL_RenderCopy(renderer, screen, NULL, NULL);

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
	texture[save] = IMG_LoadTexture(renderer, "./bitmaps/save.png");

	SDL_SetRenderTarget(renderer, screen);
	int i, x, y;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, NULL);
	
	//render toolbox
	for(i = undo; i <= save; i++) {
		SDL_RenderCopy(renderer, texture[i], NULL, &dst[i]);
		SDL_RenderPresent(renderer);
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &dst[palettetool]);
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(renderer, CANVAS_X - 1, CANVAS_Y, CANVAS_X - 1, CANVAS_Y + CANVAS_H);

	SDL_Event ev;
	
	init(&a);
	init(&b);
	push(&a, renderer);

	while(1) {
		if(SDL_PollEvent(&ev)) {
			if(ev.type == SDL_QUIT) {
				break;
			}
			
			else if(ev.type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetMouseState(&x, &y);
				if(x > LINE_X && x < LINE_X + LINE_W && y > LINE_Y && y < LINE_Y + LINE_Y) {
					if(!drawLine(renderer, dst[line], screen))
						break;
				}
					
				else if(x > HAND_X && x < HAND_X + HAND_W && y > HAND_Y && y < HAND_Y + HAND_H) {
					if(!drawHand(renderer, dst[hand]))
						break;
				}
			
						
				else if(x > RECTANGLE_X && x < RECTANGLE_X + RECTANGLE_W && y > RECTANGLE_Y && y < RECTANGLE_Y + RECTANGLE_H ) {
					if(!drawRectangle(renderer, dst[rectangle], screen))
						break;
				}
			
					
/*				else if(x > ELLIPSE_X  && x < ELLIPSE_X + ELLIPSE_W && y > ELLIPSE_Y && y < ELLIPSE_Y + ELLIPSE_H) {
					if(!drawEllipse(renderer, dst[ellipse], screen))
						break;
				}*/
				else if(x > POLYGON_X && x < POLYGON_X + POLYGON_W && y > POLYGON_Y && y < POLYGON_Y + POLYGON_H) {
					if(!drawPolygon(renderer, dst[polygon], screen))
						break;
				}
			
					
				else if(x > FILLCOLOR_X && x < FILLCOLOR_X + FILLCOLOR_W && y > FILLCOLOR_Y && y < FILLCOLOR_Y + FILLCOLOR_H ){
					if(!fillColor(renderer, dst[fillcolor]))
						break;
				}
				
				else if(x > BRUSH_X && x < BRUSH_X + BRUSH_W && y > BRUSH_Y && y < BRUSH_Y + BRUSH_H) {	
					if(!drawBrush(renderer, dst[brush]))
						break;
				}

				else if(x > GETCOLOR_X && x < GETCOLOR_X + GETCOLOR_W && y > GETCOLOR_Y && y < GETCOLOR_Y + GETCOLOR_H) {
					if(!getColor(renderer, dst[getcolor], dst[palettetool], screen))
						break;
				}

				else if(x > SPRAY_X && x < SPRAY_X + SPRAY_W && y > SPRAY_Y && y < SPRAY_Y + SPRAY_H){
					if(!drawSpray(renderer, dst[spray]))
						break;
				}

				else if(x > ERASER_X && x < ERASER_X + ERASER_W && y > ERASER_Y && y < ERASER_Y + ERASER_H){
					if(!drawEraser(renderer, dst[eraser]))
						break;
				}

				else if(x > UNDO_X && x < UNDO_X + UNDO_W && y > UNDO_Y && y < UNDO_Y + UNDO_H) {
					doUndo(renderer, screen, dst[undo]);
				}

				else if(x > REDO_X && x < REDO_X + REDO_W && y > REDO_Y && y < REDO_Y + REDO_H) {
					doRedo(renderer, screen, dst[redo]);
				}
				
				else if(x > PALETTE_X && x < PALETTE_X + PALETTE_W && y > PALETTE_Y && y < PALETTE_Y + PALETTE_H) {
					Palette(renderer, dst[palettetool]);
				}
				
				else if(x > SAVE_X && x < SAVE_X + SAVE_W && y > SAVE_Y && y < SAVE_Y + SAVE_H) {
					saveTexture(renderer, dst[save]);
				}
			}
		}
		SDL_RenderPresent(renderer);
	}
	printf("quit");

	SDL_DestroyTexture(screen);
	for(i = undo; i <= eraser; i++) 
		SDL_DestroyTexture(texture[i]);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	clear(&a);
	clear(&b);
		
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int drawLine(SDL_Renderer *renderer, SDL_Rect dst, SDL_Texture *screen) {
	int x1, y1, x2, y2, flag = 0;
	SDL_Event ev;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &dst);
	SDL_RenderPresent(renderer);

	SDL_Texture *temp = NULL;
	SDL_Surface *s = SDL_CreateRGBSurface(0, 1280, 960, 32, 0, 0, 0, 0);
	
	SDL_RenderReadPixels(renderer, NULL, 0, pix, 1280 * 4);
	s->pixels = pix;

	while(1) {
		if(SDL_PollEvent(&ev)) {
			if(ev.type == SDL_QUIT) {
				return 0;
			}	
			else if(ev.button.button == SDL_BUTTON_RIGHT) {
				screen = SDL_CreateTextureFromSurface(renderer, s);
				SDL_RenderCopy(renderer, screen, NULL, NULL);
				SDL_SetRenderTarget(renderer, screen);
		                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    	                        SDL_RenderDrawRect(renderer, &dst);
       	                        SDL_RenderPresent(renderer);
                                return 1;
			}
			else if(ev.type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetMouseState(&x1, &y1);
				if(x1 < CANVAS_X) {
					screen = SDL_CreateTextureFromSurface(renderer, s);
					SDL_RenderCopy(renderer, screen, NULL, NULL);
					SDL_SetRenderTarget(renderer, screen);
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderDrawRect(renderer, &dst);
					SDL_RenderPresent(renderer);
					return 1;
				}
				flag = 1;
			}
		
			else if(ev.type == SDL_MOUSEMOTION && flag == 1) {
				temp = SDL_CreateTextureFromSurface(renderer, s);
				SDL_RenderCopy(renderer, temp, NULL, NULL);
				SDL_SetRenderTarget(renderer, temp);

				SDL_GetMouseState(&x2, &y2);
				if(x2 < CANVAS_X)
					continue;

				SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, 255);
				SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
				SDL_RenderPresent(renderer);

				SDL_SetRenderTarget(renderer, screen);
				SDL_DestroyTexture(temp);
			}

			else if(ev.type == SDL_MOUSEBUTTONUP && flag == 1) {
				screen = SDL_CreateTextureFromSurface(renderer, s);
				SDL_RenderCopy(renderer, screen, NULL, NULL);
				SDL_SetRenderTarget(renderer, screen);

				SDL_GetMouseState(&x2, &y2);
				if(x2 < CANVAS_X)
					continue;

				SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, 255);
				SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
				SDL_RenderPresent(renderer);
				
				SDL_RenderReadPixels(renderer, NULL, 0, pix, 1280 * 4);
				s->pixels = pix;
				
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderDrawRect(renderer, &dst);
				SDL_RenderPresent(renderer);

				push(&a, renderer);
					
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(renderer, &dst);
				SDL_RenderPresent(renderer);

				flag = 0;
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------

int drawHand(SDL_Renderer *renderer, SDL_Rect dst) {
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
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderDrawRect(renderer, &dst);
				SDL_RenderPresent(renderer);

				push(&a, renderer);
					
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(renderer, &dst);
				SDL_RenderPresent(renderer);

				flag = 0;
			}	
			else if(ev.type == SDL_MOUSEMOTION && x1 > CANVAS_X && y1 > CANVAS_Y && flag == 1) {
				SDL_GetMouseState(&x2, &y2);	
				SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, 255);
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

int drawRectangle(SDL_Renderer *renderer, SDL_Rect dst, SDL_Texture *screen) {
	SDL_Event ev;
	dst.x = dst.x - 1;
	dst.w = dst.w + 2;
	dst.h = dst.h + 1;
	int x1, y1, x2, y2, flag = 0;
	SDL_Rect rect;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &dst);
	SDL_RenderPresent(renderer);

	SDL_Texture *temp = NULL;
	SDL_Surface *s = SDL_CreateRGBSurface(0, 1280, 960, 32, 0, 0, 0, 0);
	
	SDL_RenderReadPixels(renderer, NULL, 0, pix, 1280 * 4);
	s->pixels = pix;

	while(1) {
		if(SDL_PollEvent(&ev)) {
			if(ev.type == SDL_QUIT) {
				return 0;
			}	
			if(ev.button.button == SDL_BUTTON_RIGHT) {
				screen = SDL_CreateTextureFromSurface(renderer, s);
				SDL_RenderCopy(renderer, screen, NULL, NULL);
				SDL_SetRenderTarget(renderer, screen);

		                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    	                        SDL_RenderDrawRect(renderer, &dst);
       	                        SDL_RenderPresent(renderer);
                                return 1;
			}
			if(ev.type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetMouseState(&x1, &y1);
				if(x1 < CANVAS_X || ev.button.button == SDL_BUTTON_RIGHT) {	
					screen = SDL_CreateTextureFromSurface(renderer, s);
					SDL_RenderCopy(renderer, screen, NULL, NULL);
					SDL_SetRenderTarget(renderer, screen);

					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderDrawRect(renderer, &dst);
					SDL_RenderPresent(renderer);
					return 1;
				}
				rect.x = x1;
				rect.y = y1;
				flag = 1;
			}
		
			else if(ev.type == SDL_MOUSEMOTION && flag == 1 ) {
				temp = SDL_CreateTextureFromSurface(renderer, s);
				SDL_RenderCopy(renderer, temp, NULL, NULL);
				SDL_SetRenderTarget(renderer, temp);

				SDL_GetMouseState(&x2, &y2);
				if(x2 < CANVAS_X)
					continue;
				rect.w = x2 - x1;
				rect.h = y2 - y1;
				SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, 200);
				SDL_RenderDrawRect(renderer, &rect);
				SDL_RenderPresent(renderer);

				SDL_SetRenderTarget(renderer, screen);
				SDL_DestroyTexture(temp);
			}

			else if(ev.type == SDL_MOUSEBUTTONUP && flag == 1) {
				screen = SDL_CreateTextureFromSurface(renderer, s);
				SDL_RenderCopy(renderer, screen, NULL, NULL);
				SDL_SetRenderTarget(renderer, screen);

				SDL_GetMouseState(&x2, &y2);
				if(x2 < CANVAS_X)
					continue;

				rect.w = x2 - x1;
				rect.h = y2 - y1;
				SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, 255);
				SDL_RenderDrawRect(renderer, &rect);

				SDL_RenderReadPixels(renderer, NULL, 0, pix, 1280 * 4);
				s->pixels = pix;
				
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderDrawRect(renderer, &dst);
				SDL_RenderPresent(renderer);

				push(&a, renderer);
					
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(renderer, &dst);
				SDL_RenderPresent(renderer);

				flag = 0;
			}
		}
	}
	return 0;
}

//------------------------------------------------------------------------------------------------------------------
/*
int drawEllipse(SDL_Renderer *renderer, SDL_Rect dst, SDL_Texture *screen) {
	SDL_Event ev;
	int x1, y1, x2, y2, flag = 0;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &dst);
	SDL_RenderPresent(renderer);

	SDL_Texture *temp = NULL;
	SDL_Surface *s = NULL;
	
	SDL_RenderReadPixels(renderer, NULL, 0, pix, 1280 * 4);

	while(1) {
		if(SDL_PollEvent(&ev)) {
			if(ev.type == SDL_QUIT) {
				return 0;
			}	
			if(ev.button.button == SDL_BUTTON_RIGHT) {
				screen = SDL_CreateTextureFromSurface(renderer, s);
				SDL_RenderCopy(renderer, screen, NULL, NULL);
				SDL_SetRenderTarget(renderer, screen);

		                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    	                        SDL_RenderDrawRect(renderer, &dst);
       	                        SDL_RenderPresent(renderer);
                                return 1;
			}
			if(ev.type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetMouseState(&x1, &y1);
				if(x1 < CANVAS_X || ev.button.button == SDL_BUTTON_RIGHT) {	
					screen = SDL_CreateTextureFromSurface(renderer, s);
					SDL_RenderCopy(renderer, screen, NULL, NULL);
					SDL_SetRenderTarget(renderer, screen);

					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderDrawRect(renderer, &dst);
					SDL_RenderPresent(renderer);
					return 1;
				}
				flag = 1;
			}
		
			else if(ev.type == SDL_MOUSEMOTION && flag == 1 ) {
				s = SDL_CreateRGBSurface(0, 1280, 960, 32, 0, 0, 0, 0);
				s->pixels = pix;
				
				SDL_GetMouseState(&x2, &y2);
				if(x2 < CANVAS_X)
					continue;
				Draw_Ellipse(s, (x1 + x2) / 2, (y2 + y1) / 2, abs(x1 - x2), abs(y1 - y2), Color.r, Color.g, Color. b, 255);
				temp = SDL_CreateTextureFromSurface(renderer, s);
				SDL_RenderCopy(renderer, temp, NULL, NULL);
				SDL_SetRenderTarget(renderer, temp);
				SDL_RenderPresent(renderer);
				SDL_DestroyTexture(temp);
				SDL_FreeSurface(s);
			}

			else if(ev.type == SDL_MOUSEBUTTONUP && flag == 1) {
				s = SDL_CreateRGBSurface(0, 1280, 960, 32, 0, 0, 0, 0);
				s->pixels = pix;
				
				SDL_GetMouseState(&x2, &y2);
				if(x2 < CANVAS_X)
					continue;
				Draw_Ellipse(s, (x1 + x2) / 2, (y2 + y1) / 2, abs(x1 - x2), abs(y1 - y2), Color.r, Color.g, Color. b, 255);
				SDL_DestroyTexture(screen);
				screen = SDL_CreateTextureFromSurface(renderer, s);
				SDL_RenderCopy(renderer, screen, NULL, NULL);
				SDL_SetRenderTarget(renderer, screen);
				SDL_RenderPresent(renderer);
				SDL_FreeSurface(s);

				SDL_RenderReadPixels(renderer, NULL, 0, pix, 1280 * 4);
				
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderDrawRect(renderer, &dst);
				SDL_RenderPresent(renderer);

				push(&a, renderer);
					
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(renderer, &dst);
				SDL_RenderPresent(renderer);

				flag = 0;
			}
		}
	}
	return 0;
}
*/
//---------------------------------------------------------------------------------------------------------------

int drawPolygon(SDL_Renderer *renderer, SDL_Rect dst, SDL_Texture *screen) {
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	SDL_Event ev;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &dst);
	SDL_RenderPresent(renderer);

	SDL_Texture *temp = NULL;
	SDL_Surface *s = SDL_CreateRGBSurface(0, 1280, 960, 32, 0, 0, 0, 0);
	
	SDL_RenderReadPixels(renderer, NULL, 0, pix, 1280 * 4);
	s->pixels = pix;

	while(1) {
		if(SDL_PollEvent(&ev)) {
			if(ev.type == SDL_QUIT) {
				return 0;
			}	
			if(ev.button.button == SDL_BUTTON_RIGHT) {
				screen = SDL_CreateTextureFromSurface(renderer, s);
				SDL_RenderCopy(renderer, screen, NULL, NULL);
				SDL_SetRenderTarget(renderer, screen);
		  				
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderDrawRect(renderer, &dst);
				SDL_RenderPresent(renderer);

				push(&a, renderer);
					
			        return 1;
			}

			if(ev.type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetMouseState(&x2, &y2);
				if(x2 < CANVAS_X || ev.button.button == SDL_BUTTON_RIGHT) {
					screen = SDL_CreateTextureFromSurface(renderer, s);
					SDL_RenderCopy(renderer, screen, NULL, NULL);
					SDL_SetRenderTarget(renderer, screen);

					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderDrawRect(renderer, &dst);
					SDL_RenderPresent(renderer);
					return 1;
				}
				SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, 255);
				if(x1 != 0 && y1 != 0) {
					SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
					SDL_RenderPresent(renderer);
				}
				x1 = x2;
				y1 = y2;
				
				SDL_RenderReadPixels(renderer, NULL, 0, pix, 1280 * 4);
				s->pixels = pix;
			}

			else if(ev.type == SDL_MOUSEMOTION && x1 > CANVAS_X && x2 > CANVAS_X) {
				temp = SDL_CreateTextureFromSurface(renderer, s);
				SDL_RenderCopy(renderer, temp, NULL, NULL);
				SDL_SetRenderTarget(renderer, temp);

				SDL_GetMouseState(&x2, &y2);
				SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, 255);
				SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
				SDL_RenderPresent(renderer);
				
				SDL_SetRenderTarget(renderer, screen);
				SDL_DestroyTexture(temp);
			}
		}
	}
	return 0;
}

//---------------------------------------------------------------------------------------------------------------------

int drawEraser(SDL_Renderer *renderer, SDL_Rect dst) {
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

				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderDrawRect(renderer, &dst);
				SDL_RenderPresent(renderer);

				push(&a, renderer);
					
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(renderer, &dst);
				SDL_RenderPresent(renderer);

				flag = 0;
			}
		}
	}
	return 0;
}

//-----------------------------------------------------------------------------------------------------------
int drawBrush(SDL_Renderer *renderer, SDL_Rect dst) {
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
				SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, 255);
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
				SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, 255);
				SDL_RenderFillRect(renderer, &r);
				SDL_RenderPresent(renderer);
				
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderDrawRect(renderer, &dst);
				SDL_RenderPresent(renderer);

				push(&a, renderer);
					
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(renderer, &dst);
				SDL_RenderPresent(renderer);

				flag = 0;
			}
		}
	}
	return 0;
}

//------------------------------------------------------------------------------------------------------

int getColor(SDL_Renderer *renderer, SDL_Rect dst1, SDL_Rect dst2, SDL_Texture *canvas) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &dst1);
	SDL_RenderPresent(renderer);
	SDL_Rect rect;
	Uint32 pixels;
	Uint8 *p;
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
				rect.x = x;
				rect.y = y;
				rect.w = 1;
				rect.h = 1;
				
				SDL_RenderReadPixels(renderer, &rect, 0, &pixels, 1280*4);
				p = (Uint8 *)&pixels;
				
				Color.b = *p;
				Color.g = *(p+1);
				Color.r = *(p+2);
				SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, Color.a);
				SDL_RenderFillRect(renderer, &dst2);
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(renderer, &dst2);
				SDL_RenderPresent(renderer);
				
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderDrawRect(renderer, &dst1);
				SDL_RenderPresent(renderer);

				push(&a, renderer);
					
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(renderer, &dst1);
				SDL_RenderPresent(renderer);

			}
		}
	}
	return 0;
}
				
//--------------------------------------------------------------------------------------------------------------		

int Palette(SDL_Renderer *renderer, SDL_Rect dst) {

	
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

	int i, j, x, y;
	SDL_Window *win = NULL;
	SDL_Renderer *r = NULL;
	SDL_Texture *cscreen = NULL;

	win = SDL_CreateWindow("Color Palette", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 440, 330, SDL_WINDOW_SHOWN);
        if(win == NULL){
                printf("Could not create Window: %s\n", SDL_GetError());
                exit(1);
        }

	cscreen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_RENDERER_TARGETTEXTURE, 440, 330);
	r = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderTarget(r, cscreen);
	
	SDL_RenderClear(r);

	SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
	SDL_RenderFillRect(r, NULL);

	for(i = 0; i < NO_COLORS; i++) {
		SDL_SetRenderDrawColor(r, color[i].r, color[i].g, color[i].b, color[i].a);
		SDL_RenderFillRect(r, &col[i]);
		SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
		SDL_RenderDrawRect(r, &col[i]);
	}

	SDL_Rect custom;
	custom.x = CUSTOM1_X;
	custom.y = CUSTOM1_Y;
	custom.w = CUSTOM1_W;
	custom.h = 1;
	for(i = 0; i < 255; i++) {
		SDL_SetRenderDrawColor(r, i, 0, 0, 255);
		(custom.y)++;
		SDL_RenderFillRect(r, &custom);
	}

	custom.y = CUSTOM2_Y;
	custom.w = 1;
	custom.h = 1;
	for(i = 0; i < 255; i++) {
		custom.x = CUSTOM2_X;
		(custom.y)++;
		for(j = 0; j < 255; j++) {
			SDL_SetRenderDrawColor(r, 0, i, j, 255);
			(custom.x)++;
			SDL_RenderFillRect(r, &custom);
		}
	}

	SDL_RenderPresent(r);
	
	SDL_Rect rect;
	Uint32 pixels;
	Uint8 *p;
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
				
				if(x > CUSTOM1_X && x < CUSTOM1_X + CUSTOM1_W && y > CUSTOM1_Y && y < CUSTOM1_Y + CUSTOM1_H + 1) {
					rect.x = x;
					rect.y = y;
					rect.w = 1;
					rect.h = 1;

					SDL_RenderReadPixels(r, &rect, 0, &pixels, 1280*4);
					p = (Uint8 *)&pixels;

					Color.r = p[2];

					custom.y = CUSTOM2_Y;
					for(i = 0; i < 255; i++) {
						custom.x = CUSTOM2_X;
						(custom.y)++;
						for(j = 0; j < 255; j++) {
							SDL_SetRenderDrawColor(r, Color.r, i, j, 255);
							(custom.x)++;
							SDL_RenderFillRect(r, &custom);
						}
					}
					SDL_RenderPresent(r);
					continue;
				}

				rect.x = x;
				rect.y = y;
				rect.w = 1;
				rect.h = 1;
				
				SDL_RenderReadPixels(r, &rect, 0, &pixels, 1280*4);
				p = (Uint8 *)&pixels;
				
				Color.b = *(p);
				Color.g = *(p + 1);
				Color.r = *(p + 2);
				if(Color.r == 255 && Color.g == 255 && Color.b == 255)
					continue;
				break;
			}
		}
	}

        SDL_DestroyRenderer(r);
        SDL_DestroyTexture(cscreen);
	SDL_DestroyWindow(win);

	SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, 255);
	SDL_RenderFillRect(renderer, &dst);
	SDL_RenderPresent(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &dst);
	SDL_RenderPresent(renderer);

	push(&a, renderer);

	return 0;
}

//-----------------------------------------------------------------------------------------------------------
int fillColor(SDL_Renderer *renderer, SDL_Rect dst) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &dst);
	SDL_RenderPresent(renderer);
	SDL_Event ev;
	Uint32 p;
	int x, y;
	SDL_Rect rect;
	rect.w = 1;
	rect.h = 1;

	while(1) {
		if(SDL_PollEvent(&ev)) {
			if(ev.type == SDL_QUIT)
				return 0;
			else if(ev.button.button == SDL_BUTTON_RIGHT) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderFillRect(renderer, &dst);
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
				
				rect.x = x;
				rect.y = y;
				SDL_RenderReadPixels(renderer, &rect, 0, &p, 1280 * 4);
				SDL_RenderReadPixels(renderer, NULL, 0, pix, 1280 * 4);
				SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, 255);
				floodFill(renderer, x, y, p);
				SDL_RenderPresent(renderer);
			
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderDrawRect(renderer, &dst);
				SDL_RenderPresent(renderer);

				push(&a, renderer);
					
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(renderer, &dst);
				SDL_RenderPresent(renderer);
			}
		}
	}
	return 0;
}

//-------------------------------------------------------------------------------

void floodFill(SDL_Renderer *renderer, int x, int y, Uint32 p) {
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	rect.w = 1;
	rect.h = 1;

	if(x < CANVAS_X)
		return;
	
	if(p == ((Color.b << 24) | (Color.g << 16) | (Color.r << 8)))
		return; 

	if(((x + y * 1280) < 0) || ((x + y * 1280) >= 1280 * 960))
		return;
	
	if(pix[x + y * 1280] != p)
		return;		

	SDL_RenderFillRect(renderer, &rect);
	pix[x + y * 1280] = (Color.b << 24) | (Color.g << 16) | (Color.r << 8);

	floodFill(renderer, x + 1, y, p);
	floodFill(renderer, x, y - 1, p);
	floodFill(renderer, x - 1, y, p);
	floodFill(renderer, x, y + 1, p);

}

//----------------------------------------------------------------------------

int drawSpray(SDL_Renderer *renderer, SDL_Rect dst) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &dst);
	SDL_RenderPresent(renderer);
	int x, y, i, j, flag = 0;
	SDL_Event ev;
	
	while(1) {
		if(SDL_PollEvent(&ev)) {
			if(ev.type == SDL_QUIT)
				return 0;
			else if(ev.button.button == SDL_BUTTON_RIGHT) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderDrawRect(renderer, &dst);
				SDL_RenderPresent(renderer);
				return 1;
			}
			else if(ev.type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetMouseState(&x, &y);
				if(x < CANVAS_X) {
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderDrawRect(renderer, &dst);
					SDL_RenderPresent(renderer);
					return 1;
				}
				SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, 255);
				for(i = x - 3; i <= x + 3; i = i + 2) {
					for(j = y - 3; j <= y + 3; j = j + 2)
						SDL_RenderDrawPoint(renderer, i, j);
				}
				SDL_RenderDrawPoint(renderer, x - 5, y - 3);
				SDL_RenderDrawPoint(renderer, x - 5, y + 1);
				SDL_RenderDrawPoint(renderer, x - 3, y - 5);
				SDL_RenderDrawPoint(renderer, x - 3, y + 5);
				SDL_RenderDrawPoint(renderer, x + 1, y - 5);
				SDL_RenderDrawPoint(renderer, x + 1, y + 5);
				SDL_RenderDrawPoint(renderer, x + 5, y - 3);
				SDL_RenderDrawPoint(renderer, x + 5, y + 1);
				SDL_RenderPresent(renderer);
				flag = 1;
			}
			else if(ev.type == SDL_MOUSEMOTION && flag == 1) {
				SDL_GetMouseState(&x, &y);
				if(x < CANVAS_X)
					continue;
				for(i = -5; i <= 5; i = i + 2) {
					for(j = -3; j <= 3; j = j + 2)
						SDL_RenderDrawPoint(renderer, x + i, y + j);
				}
				SDL_RenderDrawPoint(renderer, x - 5, y - 3);
				SDL_RenderDrawPoint(renderer, x - 5, y + 1);
				SDL_RenderDrawPoint(renderer, x - 3, y - 5);
				SDL_RenderDrawPoint(renderer, x - 3, y + 5);
				SDL_RenderDrawPoint(renderer, x + 1, y - 5);
				SDL_RenderDrawPoint(renderer, x + 1, y + 5);
				SDL_RenderDrawPoint(renderer, x + 5, y - 3);
				SDL_RenderDrawPoint(renderer, x + 5, y + 1);
				SDL_RenderPresent(renderer);
			}
			else if(ev.type == SDL_MOUSEBUTTONUP && flag == 1) {
				flag = 0;
			
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderDrawRect(renderer, &dst);
				SDL_RenderPresent(renderer);

				push(&a, renderer);
					
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(renderer, &dst);
				SDL_RenderPresent(renderer);

			}
		}
	}
	return 0;
}

//-----------------------------------------------------------------------------------------------------

int saveTexture(SDL_Renderer *renderer, SDL_Rect dst) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &dst);
	SDL_RenderPresent(renderer);
	SDL_Rect rect;
	
	rect.x = CANVAS_X;
	rect.y = CANVAS_Y;
	rect.w = CANVAS_W;
	rect.h = CANVAS_H;

	SDL_Surface *s = NULL;	
	/*create surface and get pixels from texture*/
	s = SDL_CreateRGBSurface(0, CANVAS_W, CANVAS_H, 32, 0, 0, 0, 0);
	if (s) {
    		SDL_RenderReadPixels(renderer, &rect, s->format->format, s->pixels, s->pitch);
    		IMG_SavePNG(s, "image.png");
	}

	SDL_FreeSurface(s);
	SDL_Delay(1000);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &dst);
	SDL_RenderPresent(renderer);
	
	return 1;
}

//-------------------------------------------------------------------------------------------

int doUndo(SDL_Renderer *renderer, SDL_Texture *screen, SDL_Rect dst) {
	if(empty(&a))
		return 1;

	push(&b, renderer);
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &dst);
	SDL_RenderPresent(renderer);

	SDL_Surface *s = SDL_CreateRGBSurface(0, 1280, 960, 32, 0, 0, 0, 0);
	s->pixels = pop(&a);
	SDL_DestroyTexture(screen);
	screen = SDL_CreateTextureFromSurface(renderer, s);
	SDL_RenderCopy(renderer, screen, NULL, NULL);
	SDL_SetRenderTarget(renderer, screen);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &dst);
	SDL_RenderPresent(renderer);
	
	SDL_Rect rect;
	rect.x = PALETTE_X + 2;
	rect.y = PALETTE_Y + 2;
	rect.w = 1;
	rect.h = 1;
	Uint8 p[4];
	SDL_RenderReadPixels(renderer, &rect, 0, p, 1280 * 4);
	Color.b = p[0];
	Color.g = p[1];
	Color.r = p[2];

	return 1;
}

//--------------------------------------------------------------------------------------------

int doRedo(SDL_Renderer *renderer, SDL_Texture *screen, SDL_Rect dst) {
	if(empty(&b))
		return 1;
	
        push(&a, renderer);
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &dst);
        SDL_RenderPresent(renderer);

        SDL_Surface *s = SDL_CreateRGBSurface(0, 1280, 960, 32, 0, 0, 0, 0);
        s->pixels = pop(&b);
        SDL_DestroyTexture(screen);
        screen = SDL_CreateTextureFromSurface(renderer, s);
        SDL_RenderCopy(renderer, screen, NULL, NULL);
        SDL_SetRenderTarget(renderer, screen);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &dst);
        SDL_RenderPresent(renderer);

	SDL_Rect rect;
	rect.x = PALETTE_X + 2;
	rect.y = PALETTE_Y + 2;
	rect.w = 1;
	rect.h = 1;
	Uint8 p[4];
	SDL_RenderReadPixels(renderer, &rect, 0, p, 1280 * 4);
	Color.b = p[0];
	Color.g = p[1];
	Color.r = p[2];
	
	return 1;
}
