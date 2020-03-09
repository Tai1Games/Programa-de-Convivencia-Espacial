#include "Hands.h"
#include "Entity.h"

Hands::Hands() : 
	Component(ComponentType::Hands),
	tex_(nullptr),	//
	collider_(nullptr)
{
}

Hands::Hands(int textureId) :
	Component(ComponentType::Hands),
	tex_(nullptr),	//
	collider_(nullptr),
	textureId_(textureId)
{
}

Hands::Hands(int textureId, SDL_Rect clip) :
	Component(ComponentType::Hands),
	tex_(nullptr),	//
	collider_(nullptr),
	textureId_(textureId),
	clip_(clip)
{
}

void Hands::init()
{
	collider_ = GETCMP1_(Collider);
	if (tex_ == nullptr) {
		tex_ = SDL_Game::instance()->getTexturesMngr()->getTexture(textureId_);
		if (clip_.w == 0 && clip_.h == 0)
			clip_ = SDL_Rect{ 0, 0, tex_->getWidth(), tex_->getHeight() };
	}
}

void Hands::draw() const
{
	tex_->render(collider_->getRect(), collider_->getAngle(), clip_);
}

void Hands::setWeapon(int weaponColumn)
{
	clip_.x = clip_.w * weaponColumn;
}
