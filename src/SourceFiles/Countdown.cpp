#include "Countdown.h"

void Countdown::init() {
	viewer = GETCMP1_(Viewer);
	viewer->setTexture(texturesId_[0]);
}

void Countdown::update() {
	if (currentFrame_ < maxFrames_) {
		if (currentFrame_ >= numAct_ * framesPerNum_)	// si se pasa de n�mero, cambia la textura
		{		
			currentNumTexture_ = viewer->setTexture(texturesId_[numAct_]);
			SDL_Game::instance()->getAudioMngr()->playChannel((numAct_ == 3) ? Resources::GoSound : Resources::ThreeTwoOneSound, 0);
			numAct_++;
		}
		currentFrame_++;
		currentSize_ = minSize_ + sizeChangeRate_ * (4 * currentFrame_ % maxFrames_); //tama�o actual teniendo en cuenta que hay 4 texturas
		if (currentFrame_ == maxFrames_)
		{
			gMode_->activateControl();
			if (fGen_ != nullptr) fGen_->activate(true);
		}
		
		SDL_Rect rect;
		rect.w = currentSize_ * currentNumTexture_->getWidth() / currentNumTexture_->getHeight(); //ajustar tama�o que si no GO! se ve achatado
		rect.h = currentSize_;
		rect.x = posX_ - rect.w * 0.5; //centro de la pantalla
		rect.y = posY_ - rect.h * 0.5;
		viewer->setRenderRectangle(rect);
	}
	else entity_->setActive(false);
}