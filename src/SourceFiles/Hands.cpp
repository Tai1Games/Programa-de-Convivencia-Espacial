#include "Hands.h"
#include "Entity.h"
#include "Resources.h"
#include "InputHandler.h"
#include "InputBinder.h"

Hands::Hands(int textureId, WeaponID wId) :
	AnimatedViewer(textureId, CONST(int, "HAND_BASE_ANIMATION_SPEED"), ComponentType::Hands)
{
}

void Hands::init()
{
	AnimatedViewer::init();
	stopAnimation();

	playerData_ = GETCMP1_(PlayerData);
	collider_ = GETCMP1_(Collider);
	armLengthPhysics_ = CONST(double, "ARM_LENGTH_PHYSICS");
	handSize_ = (CONST(double, "HAND_SIZE"));
	canPickWeaponCooldown_ = CONST(int, "PICK_COOLDOWN");
	ib_ = playerData_->getBinder();
}

void Hands::handleInput()
{
	b2Vec2 vI = ib_->getAimDir();
	vI.Normalize();
	if (vI.Length() != 0) dir_.Set(vI.x, vI.y);
}

void Hands::update()
{
	AnimatedViewer::update();
	angle_ = (std::asin(dir_.x) * -_180entrepi_) - 90;

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

	if (!canPickWeapon_) {
		canPickWeaponTimer_++;
		if (canPickWeaponTimer_ >= canPickWeaponCooldown_) {
			canPickWeapon_ = true;
			canPickWeaponTimer_ = 0;
		}
	}

	updateRect();
}

void Hands::updateRect()
{
	b2Vec2 stickDir = dir_;
	drawAngle_ = std::atan2((double)stickDir.x, -(double)stickDir.y) * _180entrepi_ + 90;
	SDL_Rect playerRect = collider_->getRectRender();
	rect = {
		playerRect.x + (int)(playerRect.w * 0.5 - handSize_ * 0.5),
		playerRect.y + (int)(playerRect.h * 0.5 - handSize_ * 0.5),
		(int)handSize_ ,
		(int)handSize_
	};
}

void Hands::setWeapon(WeaponID wId, Weapon* w)
{
	currentWeaponID_ = wId;
	currentWeapon_ = w;
	frameY_ = wId;
}