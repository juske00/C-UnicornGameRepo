#pragma once
#include "Unicorn.h"
extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
class Winx
{
	SDL_Surface* winx = SDL_LoadBMP("winx.bmp");
	int width = 52;
	int height = 48;
	float offset_x = 0;
	float offset_y = 0.05;

public:
	SDL_Rect coords;
	float speed_offset = 0;
	bool spawn_allowed = true;
	void collision(Unicorn* unicorn, int& points);
	bool collided = false;
	Winx();
	void draw(SDL_Surface* ekran);
	void move(float speed, SDL_Surface* ekran, Unicorn* unicorn);
	void subpoints(Unicorn* unicorn, int& points);
};

