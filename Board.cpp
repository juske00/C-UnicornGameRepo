#include "Board.h"

Board::Board() {
	coords.x = 0;
	coords.y = -640;
}
void Board::draw(SDL_Surface* ekran) {
	SDL_BlitSurface(this->board, NULL, ekran, &this->coords);
}

void Board::move(Unicorn* unicorn) {
	unicorn->speed += 0.000001;
	this->offset_x = SDL_GetTicks() * unicorn->speed - counter * 640 + speed_offset;
	this->coords.x = -offset_x;
	if (this->offset_x >= 640) this->counter++;
	this->coords.y = -640 + 435 - unicorn->coords.y;

}

void Board::reset(Dolphin** arr, int& points, Unicorn* unicorn, Obstacle* obstacle, Platform* platform) {
	this->coords.x = 0;
	this->coords.y = 0;
	this->offset_x = 0;
	points = 0;
	unicorn->currentground = 435;
	unicorn->jumpfloat = 0;
	if (obstacle)
	obstacle->coords.x = 0;
	if (platform) {
		platform->offset_x += 1500;
	}
	for (int i = 0; i < 12; i++) {
		arr[i] = NULL;
	}

}

void Board::dash(Unicorn* unicorn) {
	if (SDL_GetTicks() - this->ticks < 1000 && unicorn->dash) {
		this->speed_offset += 0.1;
		unicorn->animation.x = 180;
		unicorn->animation.w = 120;
	}
	else {
		if (unicorn->dash) {
			unicorn->dash = false;
			unicorn->animation.x = 0;
			unicorn->animation.w = 90;
		}
		
	}
	
}




