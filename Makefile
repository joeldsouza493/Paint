project: main.c paint.h
	gcc main.c -lSDL2 -lSDL2_image -lm -o project -g -Wall
clean:
	rm project
