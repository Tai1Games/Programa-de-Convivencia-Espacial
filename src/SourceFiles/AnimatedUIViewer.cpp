#include "AnimatedUIViewer.h"

void AnimatedUIViewer::init()
{
	UIViewer::init();
	nFrames_ = tex_->getWidth() / clip_.w;
	AbstractViewers::setNFrames(nFrames_);
}

void AnimatedUIViewer::update()
{
	if (AbstractAnimatedViewers::updateTime(nFrames_)) {
		AbstractViewers::setClip(SDL_Rect{ (clip_.w * frame_), 0, clip_.w, clip_.h });	//Cogemos el frame del spritesheet

		frame_++;	//Cambiamos al siguiente frame de la animación
	}
}
