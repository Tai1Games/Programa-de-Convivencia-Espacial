#include "AnimatedViewer.h"

void AnimatedViewer::init() {
	Viewer::init();
	nframes_ = tex_->getWidth() / clip_.w;	//Obtenemos el número de frames de la spritesheet
}

void AnimatedViewer::update()
{
	timeElapsed_++;		//Aumentamos en uno el número de ciclos
	
	if (timeElapsed_ == timePerFrame_) {
		timeElapsed_ = 0;	//Reseteamos el contador de frames

		frame_ = frame_ % nframes_;
		setClip(SDL_Rect{ (clip_.w * frame_), 0, clip_.w, clip_.h });	//Cogemos el frame del spritesheet

		frame_++;	//Cambiamos al siguiente frame de la animación
	}
}