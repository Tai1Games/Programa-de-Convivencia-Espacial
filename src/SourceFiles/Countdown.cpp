#include "Countdown.h"

void Countdown::update() {
	if (currentFrame_ < maxFrames_) {
		currentFrame_++;
		currentSize_ = minSize_ + sizeChangeRate_ * (4 * currentFrame_ % maxFrames_); //tamaño actual teniendo en cuenta que hay 4 texturas
		if (currentFrame_ == maxFrames_) {
			gMode_->activateControl();
			if (fGen_ != nullptr) fGen_->activate(true);
		}
	}
}

void Countdown::draw() const {
	if (currentFrame_ < maxFrames_) {
		SDL_Rect rect;
		Texture* t = textures_[4 * currentFrame_ / maxFrames_]; //textura actual
		rect.w = currentSize_ * t->getWidth() / t->getHeight(); //ajustar tamaño que si no GO! se ve achatado
		rect.h = currentSize_;
		rect.x = posX_ - rect.w / 2; //centro de la pantalla
		rect.y = posY_ - rect.h / 2; 
		t->render(rect);
	}
}