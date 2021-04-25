#pragma once
extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
#include "Unicorn.h"
class Stalaktyt
{
	int height = 150;
	int width = 80;
	float offset_x = 0;
	SDL_Surface* stalaktyt = SDL_LoadBMP("stalaktyt.bmp");
public:
	SDL_Rect coords;
	bool spawn_allowed = true;
	Stalaktyt();
	void draw(SDL_Surface* ekran);
	void move(SDL_Surface* ekran, Unicorn* unicorn, float speed);
	void collision(Unicorn* unicorn, int& quit);
};

