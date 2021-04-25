#include "Winx.h"
void Winx::draw(SDL_Surface* ekran) {
	SDL_BlitSurface(this->winx, NULL, ekran, &this->coords);
	SDL_SetColorKey(this->winx, SDL_TRUE, SDL_MapRGB(this->winx->format, 0, 0, 0));
}
void Winx::move(float speed, SDL_Surface* ekran, Unicorn* unicorn){
	if (this->coords.x > 0) {
		this->spawn_allowed = false;
		this->draw(ekran);
		offset_x += 0.05 + unicorn->speed / 100;
		if (unicorn->dash) {
			speed_offset += 0.1;
		}
		this->coords.x = 1280 - offset_x - speed_offset;
		if (SDL_GetTicks() / 1000 % 2 == 0) {
			this->offset_y += 0.03;
		}
		else {
			this->offset_y -= 0.03;
		}
		this->coords.y = 300 + offset_y;

	}
	else {
		this->spawn_allowed = true;
	}
}

Winx::Winx() {
	this->coords.x = 1280;
	this->coords.y = 370;
}

void Winx::collision(Unicorn* unicorn, int& points) {
	
	if (this != NULL && unicorn->coords.x+91 >= this->coords.x && unicorn->coords.x+91 <= this->coords.x + 52 && unicorn->coords.y >= this->coords.y && unicorn->coords.y <= this->coords.y + 48) {
		if (!collided) {
			unicorn->points += points;
			points += 10;
			this->collided = true;
			this->coords.x = -100;
		}
		
	}
}
void Winx::subpoints(Unicorn* unicorn, int& points) {
	if (this != NULL)
		if (unicorn->coords.x > this->coords.x + 52 && !this->collided) {
			points = 10;
		}
}