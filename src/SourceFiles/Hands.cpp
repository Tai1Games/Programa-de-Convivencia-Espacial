#include "Hands.h"
#include "Entity.h"
#include "Resources.h"
#include "InputHandler.h"

Hands::Hands(int playerID, int textureId, WeaponID wId) :
	Component(ComponentType::Hands),
	textureId_(textureId),
	playerID_(playerID)
{
}

void Hands::init()
{
	collider_ = GETCMP1_(Collider);
	ih_ = SDL_Game::instance()->getInputHandler();
	if (tex_ == nullptr) {
		tex_ = SDL_Game::instance()->getTexturesMngr()->getTexture(textureId_);
	}
}

void Hands::draw() const
{
	SDL_Rect colRec = collider_->getRectRender();
	SDL_Rect destRect;
	destRect.w = colRec.w / 2;
	destRect.h = colRec.h / 2;
	destRect.x = (colRec.x + colRec.w / 4) + dir_.x * bodyOffset_;
	destRect.y = (colRec.y + colRec.h / 4) + dir_.y * bodyOffset_;

	SDL_Rect clip;
	clip.w = tex_->getWidth() / WEAPON_NUMBER;
	clip.h = tex_->getHeight();
	clip.y = 0; clip.x = clip.w * currentWeapon_;
	tex_->render(destRect, angle_, clip);
}

void Hands::update()
{
	b2Vec2 vI = ih_->getStickDir(getPlayerId(), InputHandler::GAMEPADSTICK::LEFTSTICK);
	if (vI.Length() != 0) {
		dir_.Set(vI.x, vI.y);
		//Cálculo principal del ángulo dependiendo de si está Flipeado o no
		if (!onFlipped_) angle_ = (std::asin(dir_.x) * -180.0 / PI) + 90;
		else angle_ = (std::asin(dir_.x) * -180.0 / PI) - 90;
		//Corrección de sentido de giro cuando se cálcula en la semicircunferencia inferior.
		if (dir_.y < 0) angle_ = -angle_;
		//Si apunta a la derecha desactiva el flip, si apunta a la izquierda lo activa
		if (dir_.x < 0 && !onFlipped_) onFlipped_ = true;
		else if (dir_.x > 0 && onFlipped_) onFlipped_ = false;
	}
	pos_.Set(collider_->getPos().x + dir_.x * (bodyOffset_ / PIXELS_PER_METER),
		collider_->getPos().y - dir_.y * (bodyOffset_ / PIXELS_PER_METER));
}

void Hands::setWeapon(WeaponID wId)
{
	currentWeapon_ = wId;
}
