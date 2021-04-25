#pragma once
extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
#include "Unicorn.h"
class Obstacle
{
	int height = 50;
	float offset_x = 0;
	SDL_Surface* obstacle = SDL_LoadBMP("obstacle.bmp");
public:
	SDL_Rect coords;
	SDL_Rect animation;
	int explosion_time;
	float speed_offset = 0;
	bool spawn_allowed = true;
	Obstacle();
	void draw(SDL_Surface* ekran);
	void move(Obstacle* obstacle, SDL_Surface* ekran, Unicorn* unicorn, float speed);
	void collision(Unicorn* unicorn, int &quit);
	int points = 100;
	bool collided = false;
	void subpoints(Unicorn* unicorn, int &points);
	bool show = false;
};

