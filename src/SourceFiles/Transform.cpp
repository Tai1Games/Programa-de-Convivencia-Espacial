#include "Transform.h"

void Transform::init() {
	if(coll_)
	{
		SDL_Rect collRect = coll_->getRectRender();

		renderRect_ = SDL_Rect{
			//Primero alineamos los centros de los sprites, y luego les a�adimos el offset que teniamos
			-(renderRect_.w - collRect.w) / 2 - renderRect_.x , -(renderRect_.h - collRect.h) / 2 - renderRect_.y,
			renderRect_.w, renderRect_.h
		};
	}
}

SDL_Rect Transform::getRectRender() const
{
	SDL_Rect temp;

	if(coll_) temp = coll_->getRectRender();
	else temp = overRect_;
	
	return SDL_Rect{
		temp.x + renderRect_.x, temp.y + renderRect_.y,
		renderRect_.w, renderRect_.h
	};
}	

void Transform::setRenderRectangle(SDL_Rect newRect) {
	overRect_ = newRect;
}