#pragma once
#include "Component.h"
#include "Vector2D.h"
#include "checkML.h"
#include "box2d.h"
#include "Collider.h"

class Transform : public Component
{
public:
	//-------------------------------------------------------------------------------------------------------------------
	// IMPORTANTISIMO: AL REFERIRSE DIRECTAMENTE AL RENDER, LOS OFFSETS Y TAMAÑOS DE renderRect SON EN PIXELES, NO EN S.I.
	//--------------------------------------------------------------------------------------------------------------------
	Transform(SDL_Rect renderRect, Collider* coll) : Component(ComponentType::Transform) {
		coll_ = coll;
		renderRect_ = renderRect;
	};

	virtual ~Transform() {};

	void init();

	SDL_Rect getRectRender(int index = 0) const {
		SDL_Rect temp = coll_->getRectRender();
		return SDL_Rect{
			temp.x + renderRect_.x, temp.y + renderRect_.y,
			renderRect_.w, renderRect_.h
		};
	}

	Collider* getCollider() { return coll_; };

	float getAngleInDegrees() const { return coll_->getAngleInDegrees(); }

private:

	SDL_Rect renderRect_;
	Collider* coll_;
};
