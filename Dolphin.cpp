#include "Dolphin.h"

Dolphin::Dolphin(Dolphin** array, int x) {
	int i = 0;
	for (i; array[i] != NULL; i++);
	if (i < 12) {
		this->coords.x = x;
		this->coords.y = y;
		this->coords2.x = 0;
		this->coords2.y = 0;
		this->coords2.w = 35;
		this->coords2.h = 16;
		this->time = SDL_GetTicks();
		array[i] = this;
	}
	
}

void Dolphin::draw(SDL_Surface* ekran) {
	
		if ((SDL_GetTicks() - this->time) % 500 < 250) {
			this->coords2.x = 0;
		}
		else {
			this->coords2.x = 35;
		}
		SDL_BlitSurface(this->dolphin, &this->coords2, ekran, &this->coords);
		SDL_SetColorKey(this->dolphin, SDL_TRUE, SDL_MapRGB(this->dolphin->format, 0, 0, 0));
	
	
}
