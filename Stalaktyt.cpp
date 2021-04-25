#include "Stalaktyt.h"

Stalaktyt::Stalaktyt() {
	this->coords.x = 1280;
	this->coords.y = 0;
	this->offset_x = 0;
}

void Stalaktyt::draw(SDL_Surface* ekran) {
	SDL_BlitSurface(this->stalaktyt, NULL, ekran, &this->coords);
	SDL_SetColorKey(this->stalaktyt, SDL_TRUE, SDL_MapRGB(this->stalaktyt->format, 0, 0, 0));
}

void Stalaktyt::move(SDL_Surface* ekran, Unicorn* unicorn, float speed) {
	if (this != NULL) {
		if (this->coords.x > -37) {
			this->draw(ekran);
			offset_x += 0.05 + unicorn->speed / 100;
			this->coords.x = 1280 - offset_x;
			this->spawn_allowed = false;
		}
		else {
			this->spawn_allowed = true;
		}


	}
}

void Stalaktyt::collision(Unicorn* unicorn, int& quit) {
	if (this != NULL) {
		if (unicorn->coords.x + 91 >= this->coords.x && unicorn->coords.x + 91 <= this->coords.x + 80 && unicorn->coords.y <= height) {
			unicorn->lives--;
			return;
		}
	}

}