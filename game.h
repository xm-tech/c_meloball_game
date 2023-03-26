#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <SDL2/SDL.h>

#define GAME_NAME "MELOBALL"
#define WIDTH 380
#define HEIGHT 640
#define FRAME_RATE 50 // 1秒 50 帧
#define MOVE_SPEED 10

#define BG_COLOR 0xffffffff
#define RECT_WIDTH 80
#define RECT_HEIGHT 10
#define RECT_COLOR 0x00885533

typedef struct {
	SDL_Window *win;
	SDL_Surface *scene;
	int x;
	int y;
} game;

void start_game();

#endif
