#include "AnimatedViewer.h"

void AnimatedViewer::init() {
	Viewer::init();
	nFrames_ = tex_->getWidth() / clip_.w;	//Obtenemos el número de frames de la spritesheet
	AbstractViewers::setNFrames(nFrames_);
}

void AnimatedViewer::update()
{
	if (updateTime(nFrames_)) {
		setClip(SDL_Rect{ (clip_.w * frame_), 0, clip_.w, clip_.h });	//Cogemos el frame del spritesheet

		frame_++;	//Cambiamos al siguiente frame de la animación
	}
}