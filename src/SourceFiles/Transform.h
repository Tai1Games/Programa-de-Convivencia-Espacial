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
	// IMPORTANTISIMO: AL REFERIRSE DIRECTAMENTE AL RENDER, LOS OFFSETS Y TAMA�OS DE renderRect SON EN PIXELES, NO EN S.I.
	//--------------------------------------------------------------------------------------------------------------------
	Transform(SDL_Rect renderRect, Collider* coll) : Component(ComponentType::Transform) {
		coll_ = coll;
		renderRect_ = renderRect;
	};

	virtual ~Transform() {};

	void init();

	SDL_Rect getRectRender() const;

	Collider* getCollider() { return coll_; };

	float getAngleInDegrees() const {
		if(coll_) return coll_->getAngleInDegrees();
		return 0;
	}

	void setRenderRectangle(SDL_Rect newRect);

private:

	SDL_Rect renderRect_;
	SDL_Rect overRect_;

	Collider* coll_;
};
