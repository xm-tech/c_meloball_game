#include "game.h"
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

static game *g = NULL;

static void init_game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	g = malloc(sizeof(game));
	g->win = SDL_CreateWindow(GAME_NAME, 0, 0, WIDTH, HEIGHT, 0);
	g->scene = SDL_GetWindowSurface(g->win);

	g->x = WIDTH / 2 - RECT_WIDTH / 2;
	g->y = HEIGHT - RECT_HEIGHT;
}

static inline void draw() {
	if (g->x > WIDTH - RECT_WIDTH) {
		g->x = WIDTH - RECT_WIDTH;
	}
	if (g->x < 0) {
		g->x = 0;
	}

	if (g->y > HEIGHT - RECT_HEIGHT) {
		g->y = HEIGHT - RECT_HEIGHT;
	}
	if (g->y < 0) {
		g->y = 0;
	}
	SDL_Rect background = {0, 0, WIDTH, HEIGHT};
	SDL_FillRect(g->scene, &background, BG_COLOR);
	SDL_Rect rect = {g->x, g->y, RECT_WIDTH, RECT_HEIGHT};
	// argb: 0x a(透明)r(red)g(green)b(blue)
	SDL_FillRect(g->scene, &rect, RECT_COLOR);

	SDL_UpdateWindowSurface(g->win);
}

static inline void on_key_down(SDL_Event e) {
	SDL_Keycode keycode = e.key.keysym.sym;
	printf("keycode:%d\n", keycode);
	switch (keycode) {
	case SDLK_LEFT:
		g->x -= MOVE_SPEED;
		break;
	case SDLK_RIGHT:
		g->x += MOVE_SPEED;
		break;
	case SDLK_UP:
		g->y -= MOVE_SPEED;
		break;
	case SDLK_DOWN:
		g->y += MOVE_SPEED;
		break;
	}
}

static inline void on_quit() {
	// player quit
	printf("on_quit");
}

static void event_loop() {
	SDL_Event e;

	while (true) {
		uint64_t begin = SDL_GetTicks();

		draw();

		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				on_quit();
				return;
			case SDL_MOUSEMOTION:
			case SDL_MOUSEBUTTONDOWN:
			case SDL_KEYUP:
				break;
			case SDL_KEYDOWN:
				on_key_down(e);
				break;
			}
		}

		// 控制帧频 为 FRAME_RATE
		uint64_t current = SDL_GetTicks();
		uint64_t cost = current - begin;
		uint32_t frame_time = 1000 / FRAME_RATE;

		long delay = frame_time - cost;
		if (delay > 0) {
			SDL_Delay(delay);
			// 休眠 20 毫秒， 1 秒执行 50 次， 也即 50 帧
			/* SDL_Delay(20); */
		}
	}
}

static void on_destroy() {
	SDL_DestroyWindow(g->win);
	SDL_Quit();
}

void start_game() {
	printf("start_game\n");
	init_game();
	event_loop();
	on_destroy();
}

