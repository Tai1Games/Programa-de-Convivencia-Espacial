#include "Countdown.h"

void Countdown::update() {
	if (currentFrame_ < maxFrames_) {
		currentFrame_++;
		if (currentFrame_ == maxFrames_) gMode_->activateControl();
	}
}

void Countdown::draw() {
	SDL_Rect rect;
	rect.x = posX; rect.y = posY;
	rect.w = 100; rect.h = 100;
	number->render(rect);
}