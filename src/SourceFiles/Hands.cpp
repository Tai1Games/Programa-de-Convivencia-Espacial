#include "Hands.h"
#include "Entity.h"
#include "Resources.h"
#include "InputHandler.h"

Hands::Hands(int playerID, int textureId) :
	Component(ComponentType::Hands),
	tex_(nullptr),	//
	collider_(nullptr),
	textureId_(textureId),
	playerID_(playerID)
{
}

Hands::Hands(int playerID, int textureId, SDL_Rect clip) :
	Component(ComponentType::Hands),
	tex_(nullptr),	//
	collider_(nullptr),
	textureId_(textureId),
	clip_(clip),
	playerID_(playerID)
{
}

void Hands::init()
{
	collider_ = GETCMP1_(Collider);
	ih_ = SDL_Game::instance()->getInputHandler();
	if (tex_ == nullptr) {
		tex_ = game_->getTexturesMngr()->getTexture(Resources::Tinky);
	}
}

void Hands::draw() const
{
	SDL_Rect colRec = collider_->getRectRender();
	SDL_Rect destRect;
	destRect.w = colRec.w / 2;
	destRect.h = colRec.h / 2;
	destRect.x = (colRec.x /*+ (colRec.w + colRec.w/5)*/ + colRec.w/4) + pos_.x*bodyOffset_;
	destRect.y = (colRec.y /*+ (colRec.h / 2) - (destRect.h/2)*/+ colRec.h/4) + pos_.y*bodyOffset_;
	tex_->render(destRect, collider_->getAngle()/*, clip_*/);
}

void Hands::update()
{

	b2Vec2 vI = ih_->getStickDir(0, InputHandler::GAMEPADSTICK::LEFTSTICK);
	if (vI.Length() != 0) {
		b2Vec2 vI = ih_->getStickDir(0, InputHandler::LEFTSTICK);
		pos_.Set(vI.x,vI.y);
	}
}

void Hands::setWeapon(int weaponColumn)
{
	clip_.x = clip_.w * weaponColumn;
}

SDL_Rect  Hands::getRectRender() const {
	return SDL_Rect{
		(int)(pos_.x * PIXELS_PER_METER - (tex_->getWidth() * PIXELS_PER_METER)),
		(int)(WINDOW_HEIGHT - (pos_.y * PIXELS_PER_METER + (tex_->getHeight() * PIXELS_PER_METER))),
		(int)(tex_->getWidth() * PIXELS_PER_METER * 2),
		(int)(tex_->getHeight() * PIXELS_PER_METER * 2)
	};
}
