#pragma once
extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
class Unicorn
{
	SDL_Surface* life = SDL_LoadBMP("Life.bmp");
	SDL_Surface* unicorn = SDL_LoadBMP("Unicorn.bmp");
	
public :
	int currentground = 435;
	float speed = 0.1;
	bool jumped = false;
	int lives = 3;
	int points = 0;
	bool dash = false;
	float jumpfloat = 0;
	float rememberjump = 0;
	bool touched_ground = true;
	int jumpcounter = 0;
	SDL_Rect coords;
	SDL_Rect lifecoords;
	SDL_Rect animation;
	Unicorn();
	void draw(SDL_Surface* ekran);
	void jump(int ticks);
	bool getJumped();
	void setJumped();
};

