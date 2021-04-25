#pragma once
extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
class Dolphin
{
	SDL_Surface* dolphin = SDL_LoadBMP("dolphin.bmp");
	SDL_Rect coords;
	SDL_Rect coords2;
	int x = 0;
	int y = 600;
	int time;
	
public:
	
	Dolphin(Dolphin** array, int x);
	void draw(SDL_Surface* ekran);
};

