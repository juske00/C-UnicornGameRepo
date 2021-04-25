#pragma once
extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
#include "Unicorn.h"
#include "Dolphin.h"
#include "Obstacle.h"
#include "Platform.h"
class Board
{
	SDL_Surface* board = SDL_LoadBMP("board.bmp");

public:
	int lastticks = SDL_GetTicks();
	int counter = 0;
	SDL_Rect coords;
	char jumpButton = 'z';
	char dashButton = 'x';
	int ticks;
	float offset_x = 0.25;
	float speed_offset = 0;
	Board();
	void move(Unicorn* unicorn);
	void draw(SDL_Surface* ekran);
	void reset(Dolphin** arr, int &points, Unicorn* unicorn, Obstacle* obstacle, Platform*platform);
	void dash(Unicorn* unicorn);
};

