#include "Hands.h"
#include "Entity.h"
#include "Resources.h"

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
	destRect.x = colRec.x + (colRec.w + colRec.w/5);
	destRect.y = colRec.y + (colRec.h / 2) - (destRect.h/2);
	tex_->render(destRect, collider_->getAngle()/*, clip_*/);
}

void Hands::update() const {
	//pos_.x = collider_->getPos().x + collider_->getPos
}

void Hands::setWeapon(int weaponColumn)
{
	clip_.x = clip_.w * weaponColumn;
}
