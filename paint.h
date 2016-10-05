#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef _PAINT_H
#define _PAINT_H

#define NO_ICONS 12

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

#endif


	

typedef enum Tool{
	undo, redo, hand, line, rectangle, ellipse, polygon, fillcolor, brush, getcolor, spray, eraser
}Tool;

typedef struct Tools {
	int x, y, w, h;
}Icon;

void initscr(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture);
void drawLine(SDL_Renderer *renderer, SDL_Event *ev, SDL_Rect *dst);
void drawHand(SDL_Renderer *renderer, SDL_Event *ev, SDL_Rect *dst);
void drawRectangle(SDL_Renderer *renderer, SDL_Event *ev, SDL_Rect *dst);
