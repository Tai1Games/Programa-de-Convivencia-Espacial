#include "Hands.h"
#include "Entity.h"
#include "Resources.h"

Hands::Hands(int playerID) : 
	Component(ComponentType::Hands),
	tex_(nullptr),	//
	collider_(nullptr),
	playerID_(playerID)
{
}

Hands::Hands(int textureId, int playerID) :
	Component(ComponentType::Hands),
	tex_(nullptr),	//
	collider_(nullptr),
	textureId_(textureId),
	playerID_(playerID)
{
}

Hands::Hands(int textureId, SDL_Rect clip, int playerID) :
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
	/*if (tex_ == nullptr) {
		tex_ = game_->getTexturesMngr()->getTexture(Resources::Tinky);
	}*/
}

void Hands::draw() const
{
	//tex_->render(collider_->getRect(), collider_->getAngle(), clip_);
}

void Hands::setWeapon(int weaponColumn)
{
	clip_.x = clip_.w * weaponColumn;
}
