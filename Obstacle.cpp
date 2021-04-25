#include "Obstacle.h"

Obstacle::Obstacle() {
	this->coords.x = 1280;
	this->coords.y = 405 + this->height;
	this->offset_x = 0;
	this->speed_offset = 0;
	animation.x = 0;
	animation.y = 0;
	animation.w = 36;
	animation.h = 50;
}

void Obstacle::draw(SDL_Surface* ekran) {
	SDL_BlitSurface(this->obstacle, &this->animation, ekran, &this->coords);
	SDL_SetColorKey(this->obstacle, SDL_TRUE, SDL_MapRGB(this->obstacle->format, 0, 0, 0));
}

void Obstacle::move(Obstacle* obstacle, SDL_Surface* ekran, Unicorn* unicorn, float speed) {
	if (obstacle != NULL) {
		if (this->coords.x > 0) {
			this->draw(ekran);
			offset_x += 0.05 + unicorn->speed / 100;
			if (unicorn->dash) {
				speed_offset += 0.1;
			}
			this->coords.x = 1280 - offset_x - speed_offset;
			this->coords.y = 405 + this->height + (435 - unicorn->coords.y);
			this->spawn_allowed = false;
		}
		else {
			this->spawn_allowed = true;
		}
		
		
	}
}

void Obstacle::collision(Unicorn* unicorn, int &points) {
	if (this != NULL && !unicorn->dash) {
		if (unicorn->coords.x + 91 >= this->coords.x && unicorn->coords.x + 91 <= this->coords.x + 36 && unicorn->coords.y + 70 >= this->coords.y) {
			unicorn->lives--;
			return;
		}
	}
	else if (this != NULL && unicorn->dash && unicorn->coords.x + 91 >= this->coords.x && unicorn->coords.x + 91 <= this->coords.x + 36 && unicorn->coords.y + 70 >= this->coords.y) {
		if (unicorn->coords.x+91 == this->coords.x && !collided) {
			unicorn->points += points;
			points += 100;
			this->collided = true;
			this->show = true;
		}
		if (this->animation.x == 0) {
			this->explosion_time = SDL_GetTicks();
		}
		if (SDL_GetTicks() - this->explosion_time < 50)
			animation.x = 36;
		else
			animation.x = 72;
	}
}

void Obstacle::subpoints(Unicorn* unicorn, int& points) {
	if(this != NULL)
	if (unicorn->coords.x + 91 > this->coords.x + 36 && !this->collided) {
		points = 100;
	}
}