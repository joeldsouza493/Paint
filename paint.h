#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef _PAINT_H
#define _PAINT_H

#define NO_ICONS 13

#define UNDO_X 5
#define UNDO_Y 5
#define UNDO_W 25
#define UNDO_H 25

#define REDO_X 35
#define REDO_Y 5
#define REDO_W 25
#define REDO_H 25

#define HAND_X 5
#define HAND_Y 35
#define HAND_W 25
#define HAND_H 25

#define LINE_X 35
#define LINE_Y 35
#define LINE_W 25
#define LINE_H 25

#define RECTANGLE_X 5
#define RECTANGLE_Y 65
#define RECTANGLE_W 25
#define RECTANGLE_H 25

#define ELLIPSE_X 35
#define ELLIPSE_Y 65
#define ELLIPSE_W 25
#define ELLIPSE_H 25

#define POLYGON_X 5
#define POLYGON_Y 95
#define POLYGON_W 25
#define POLYGON_H 25

#define FILLCOLOR_X 35
#define FILLCOLOR_Y 95
#define FILLCOLOR_W 25
#define FILLCOLOR_H 25

#define BRUSH_X 5
#define BRUSH_Y 125
#define BRUSH_W 25
#define BRUSH_H 25

#define GETCOLOR_X 35
#define GETCOLOR_Y 125
#define GETCOLOR_W 25
#define GETCOLOR_H 25

#define SPRAY_X 5
#define SPRAY_Y 155
#define SPRAY_W 25
#define SPRAY_H 25

#define ERASER_X 35
#define ERASER_Y 155
#define ERASER_W 25
#define ERASER_H 25

#define CANVAS_X 65
#define CANVAS_Y 0
#define CANAVS_W 1240
#define CANVAS_H 960

#define PALETTE_X 5
#define PALETTE_Y 185
#define PALETTE_W 25
#define PALETTE_H 25


//----------------------------------------------------------------------------------

#define NO_COLORS 16

#define BLACK_X 5
#define BLACK_Y 5
#define BLACK_W 20
#define BLACK_H 20

#define WHITE_X 30
#define WHITE_Y 5
#define WHITE_W 20
#define WHITE_H 20

#define RED_X 55
#define RED_Y 5
#define RED_W 20
#define RED_H 20

#define LIME_X 80
#define LIME_Y 5
#define LIME_W 20
#define LIME_H 20

#define BLUE_X 105
#define BLUE_Y 5
#define BLUE_W 20
#define BLUE_H 20

#define YELLOW_X 130
#define YELLOW_Y 5
#define YELLOW_W 20
#define YELLOW_H 20

#define AQUA_X 155
#define AQUA_Y 5
#define AQUA_W 20
#define AQUA_H 20

#define MAGENTA_X 180
#define MAGENTA_Y 5
#define MAGENTA_W 20
#define MAGENTA_H 20

#define SILVER_X 180
#define SILVER_Y 30
#define SILVER_W 20
#define SILVER_H 20

#define GRAY_X 5
#define GRAY_Y 30
#define GRAY_W 20
#define GRAY_H 20

#define MAROON_X 30
#define MAROON_Y 30
#define MAROON_W 20
#define MAROON_H 20

#define OLIVE_X 55
#define OLIVE_Y 30
#define OLIVE_W 20
#define OLIVE_H 20

#define GREEN_X 80
#define GREEN_Y 30
#define GREEN_W 20
#define GREEN_H 20

#define PURPLE_X 105
#define PURPLE_Y 30
#define PURPLE_W 20
#define PURPLE_H 20

#define TEAL_X 130
#define TEAL_Y 30
#define TEAL_H 20
#define TEAL_W 20

#define NAVY_X 155
#define NAVY_Y 30
#define NAVY_W 20
#define NAVY_H 20
//-----------------------------------------------------
#define BLACK_R 0
#define BLACK_G 0
#define BLACK_B 0
#define BLACK_A 255

#define WHITE_R 255
#define WHITE_G 255
#define WHITE_B 255
#define WHITE_A 255

#define RED_R 255
#define RED_G 0
#define RED_B 0
#define RED_A 255

#define LIME_R 0
#define LIME_G 255
#define LIME_B 0
#define LIME_A 255

#define BLUE_R 0
#define BLUE_G 0
#define BLUE_B 255
#define BLUE_A 255

#define YELLOW_R 255
#define YELLOW_G 255
#define YELLOW_B 0
#define YELLOW_A 255

#define AQUA_R 0
#define AQUA_G 255
#define AQUA_B 255
#define AQUA_A 255

#define MAGENTA_R 255
#define MAGENTA_G 0
#define MAGENTA_B 255
#define MAGENTA_A 255

#define SILVER_R 192
#define SILVER_G 192
#define SILVER_B 192
#define SILVER_A 255

#define GRAY_R 128
#define GRAY_G 128
#define GRAY_B 128
#define GRAY_A 255

#define MAROON_R 128
#define MAROON_G 0
#define MAROON_B 0
#define MAROON_A 255

#define OLIVE_R 128
#define OLIVE_G 128
#define OLIVE_B 0
#define OLIVE_A 255

#define GREEN_R 0
#define GREEN_G 128
#define GREEN_B 0
#define GREEN_A 255

#define PURPLE_R 128
#define PURPLE_G 0
#define PURPLE_B 128
#define PURPLE_A 255

#define TEAL_R 0
#define TEAL_G 128
#define TEAL_B 128
#define TEAL_A 255

#define NAVY_R 0
#define NAVY_G 0
#define NAVY_B 128
#define NAVY_A 255


#endif

SDL_Color Color;	

typedef enum Tool{
	undo, redo, hand, line, rectangle, ellipse, polygon, fillcolor, brush, getcolor, spray, eraser, palette
}Tool;

typedef enum Colors{
	black, white, red, lime, blue, yellow, aqua, magenta, silver, gray, maroon, olive, green, purple, teal, navy
}Colors;

/*typedef struct Tools {
	int x, y, w, h;
}Icon;*/

int initscr(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture);
int drawLine(SDL_Renderer *renderer,/* SDL_Event *ev,*/ SDL_Rect dst);
int drawHand(SDL_Renderer *renderer,/* SDL_Event *ev,*/ SDL_Rect dst);
int drawRectangle(SDL_Renderer *renderer,/* SDL_Event *ev,*/ SDL_Rect dst);
int drawPolygon(SDL_Renderer *renderer,/* SDL_Event *ev,*/ SDL_Rect dst);
int drawEraser(SDL_Renderer *renderer,/* SDL_Event *ev,*/ SDL_Rect dst);
int drawBrush(SDL_Renderer *renderer,/* SDL_Event *ev,*/ SDL_Rect dst);
int getColor(SDL_Renderer *renderer, SDL_Rect dst1, SDL_Rect dst2, SDL_Surface *canvas);
Uint32 getPixel(SDL_Surface *surface, int x, int y);
int Palette(SDL_Renderer *renderer, SDL_Rect dst);

