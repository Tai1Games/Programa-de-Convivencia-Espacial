#include "AnimatedViewer.h"

void AnimatedViewer::init() {
	Viewer::init();
	nframes = tex_->getWidth() / clip_.w;	//Obtenemos el número de frames de la spritesheet
}

void AnimatedViewer::update()
{
	time++;		//Aumentamos en uno el número de ciclos
	
	if (time == timeFrame) {
		time = 0;	//Reseteamos el contador de frames

		frame = frame % nframes;
		setClip(SDL_Rect{ (clip_.w * frame), 0, clip_.w, clip_.h });	//Cogemos el frame del spritesheet

		frame++;	//Cambiamos al siguiente frame de la animación
	}
}