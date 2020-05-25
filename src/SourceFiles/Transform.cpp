#include "Transform.h"

void Transform::init(){

	SDL_Rect collRect = coll_->getRectRender();

	renderRect_ = SDL_Rect{ 
		//Primero alineamos los centros de los sprites, y luego les añadimos el offset que teniamos
		-(renderRect_.w - collRect.w)/2 -renderRect_.x , -(renderRect_.h - collRect.h )/2 - renderRect_.y,
		renderRect_.w, renderRect_.h
	};
}
