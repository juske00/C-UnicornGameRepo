#pragma once
extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
#include "Unicorn.h"
class Platform
{
	SDL_Surface* platform = SDL_LoadBMP("platform.bmp");
	
public:
	SDL_Rect coords;
	bool collided = false;
	float offset_x = 0;
	bool spawn_allowed = false;
	float speed_offset = 0;
	void draw(SDL_Surface* ekran);
	Platform();
	void collision(Unicorn* unicorn);
	void move(SDL_Surface* ekran, Unicorn* unicorn);
};

