#include "Hands.h"
#include "Entity.h"
#include "Resources.h"
#include "InputHandler.h"
#include "InputBinder.h"

Hands::Hands(int textureId, WeaponID wId) :
	Component(ComponentType::Hands),
	textureId_(textureId)
{
}

void Hands::init()
{
	playerData_ = GETCMP1_(PlayerData);
	collider_ = GETCMP1_(Collider);
	armLengthPhysics_ = CONST(double, "ARM_LENGTH_PHYSICS");
	handSize_ = (CONST(double, "HAND_SIZE"));
	ib_ = playerData_->getBinder();
	if (tex_ == nullptr) {
		tex_ = SDL_Game::instance()->getTexturesMngr()->getTexture(textureId_);
	}
}

void Hands::draw() const
{
	b2Vec2 stickDir = dir_;

	double angle = std::atan2((double)stickDir.x, -(double)stickDir.y) * (180.0 / PI);
	SDL_Rect playerRect = collider_->getRectRender();
	SDL_Rect destRect{ playerRect.x + playerRect.w / 2 - handSize_ / 2,playerRect.y + playerRect.h / 2 - handSize_ / 2 , handSize_ , handSize_ };

	tex_->render(destRect, angle_, currentWeaponID_, 0, Flipped_);
}

void Hands::handleInput()
{
	b2Vec2 vI = (ib_->getAimDir()).NormalizedVector();
	if (vI.Length() != 0) dir_.Set(vI.x, vI.y);
}

void Hands::update()
{
	angle_ = (std::asin(dir_.x) * -180.0 / PI) - 90;

	//el arcoseno solo nos devuelve angulos en el intervalo 0� - 180�, si apuntamos hacia abajo hay que coger el angulo inverso
	if (dir_.y < 0) angle_ = (int)(360 - angle_) % 360;

	float dispAngHand = (int)(180 - angle_) % 360;	 //el angulo estandarizado de la mano

	float dispAngPlayer = (360 + (90 + (int)(-collider_->getAngleInDegrees()) % 360)) % 360;	//el angulo estandarizado del jugador

	if ((dispAngHand < (dispAngPlayer + 180)) && (dispAngHand > dispAngPlayer)) {	//si la mano esta a su espalda
		Flipped_ = SDL_FLIP_NONE;
	}
	else Flipped_ = SDL_FLIP_VERTICAL;

	pos_.Set(collider_->getPos().x, collider_->getPos().y);
	handPos_.Set(pos_.x + dir_.x * 1, pos_.y - dir_.y * 1);
}

void Hands::setWeapon(WeaponID wId, Weapon* w)
{
	currentWeaponID_ = wId;
	currentWeapon_ = w;
}
