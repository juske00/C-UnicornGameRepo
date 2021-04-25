#include "Platform.h"

Platform::Platform() {
	this->coords.x = 1280;
	this->coords.y = 465;
}

void Platform::draw(SDL_Surface* ekran) {
	SDL_BlitSurface(this->platform,NULL, ekran, &this->coords);
	SDL_SetColorKey(this->platform, SDL_TRUE, SDL_MapRGB(this->platform->format, 0, 0, 0));
}
void Platform::move(SDL_Surface* ekran, Unicorn* unicorn) {
	
	if (this->coords.x > -300) {
		this->spawn_allowed = false;
		this->draw(ekran);
		offset_x += 0.05 + unicorn->speed / 100;
		if (unicorn->dash) {
			speed_offset += 0.1;
		}
		this->coords.x = 1280 - offset_x - speed_offset;
		this->coords.y = 465 + (435 - unicorn->coords.y);
	}
	else {
		this->spawn_allowed = true;
	}
}
void Platform::collision(Unicorn* unicorn) {
	if (!collided && (unicorn->coords.x >= this->coords.x && unicorn->coords.x + 91 <= this->coords.x + 300) && unicorn->coords.y+70 == this->coords.y ) {
		collided = true;
	}
	else if (!collided&& unicorn->coords.x + 91 >= this->coords.x && unicorn->coords.x + 91 <= this->coords.x + 300 && unicorn->coords.y + 70 > this->coords.y) {
		unicorn->lives--;
		return;
	}
	if (collided) {
		if(unicorn->coords.x >= this->coords.x && unicorn->coords.x  <= this->coords.x + 300)
		unicorn->currentground = 465 - 70;
		else {
			unicorn->currentground = 435;
		}
	}
	else {
		unicorn->currentground = 435;
	}
}


