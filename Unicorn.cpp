#include "Unicorn.h"
Unicorn::Unicorn() {
	coords.x = 200;
	coords.y = currentground;
	animation.x = 0;
	animation.y = 0;
	animation.w = 90;
	animation.h = 70;
	lifecoords.x = 0;
	lifecoords.y = 0;
	lifecoords.h = 32;
	lifecoords.w = 180;

}

void Unicorn::draw(SDL_Surface* ekran) {
	lifecoords.w = this->lives * 60;
	SDL_BlitSurface(this->unicorn, &this->animation, ekran, &this->coords);
	SDL_SetColorKey(this->unicorn, SDL_TRUE, SDL_MapRGB(this->unicorn->format, 0, 0, 0));
	SDL_BlitSurface(this->life, &this->lifecoords, ekran, NULL);
	SDL_SetColorKey(this->life, SDL_TRUE, SDL_MapRGB(this->unicorn->format, 0, 0, 0));
}

bool Unicorn::getJumped() {
	return this->jumped;
}

void Unicorn::setJumped() {
	if (this->jumped == true) {
		this->jumped = false;
	}
	else {
		this->jumped = true;
	}
}

void Unicorn::jump(int ticks) {
	
	if (!dash)
	{
		this->animation.x = 90;
		if (this->getJumped() == true && this->jumpcounter < 2) {
			if (this->coords.y > currentground - (this->jumpcounter + 1) * 170) {
				this->coords.y = currentground - jumpfloat;
				this->jumpfloat += 0.05;
				
			}
			else {
				this->jumped = false;
				
			}
		}
		else {
			if (this->coords.y < currentground) {
				this->coords.y = currentground - jumpfloat;
				this->jumpfloat -= 0.05;
				touched_ground = false;
			}
			else if (this->coords.y >= currentground) {
				this->jumpfloat = 0;
				touched_ground = true;
				this->jumpcounter = 0;
				if(SDL_GetTicks()% 500 < 250)
				this->animation.x = 0;
				else {
					this->animation.x = 300;
				}
			}
			else {
				touched_ground = false;
			}
		}
	}
	
	
}
