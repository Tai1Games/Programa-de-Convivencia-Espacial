#include "PlayerController.h"
#include "InputBinder.h"
#include "Entity.h"

#include"AnimatedPlayer.h"


bool PlayerController::isImpulseValid(const b2Vec2& dir)
{
	b2Vec2 normal = attachesToObj_->getAttachmentNormal();
	float angle = atan2(normal.x * dir.x + normal.y * dir.y,
		normal.x * dir.y - normal.y * dir.x);
	//comop mucho permite impulsos perpendiculares al agarre
	//sumar radianes a PI/2 para restringir aun mas la direccion de impulso
	return abs(angle) > PI / 2;
}

PlayerController::PlayerController() : Component(ComponentType::PlayerController),
coll_(nullptr), attachesToObj_(nullptr), playerNumber_(-1), chargedFrames_(0), dirImpulse_(1, 0),
chargeMultiplier_(0), maxImpulseFloating_(0), maxImpulseGrabbed_(0), impulseForce_(0)
{
}

void PlayerController::init()
{
	playerData_ = GETCMP1_(PlayerData);
	coll_ = GETCMP1_(Collider); //pilla referencia al collider
	attachesToObj_ = GETCMP1_(AttachesToObjects);
	playerNumber_ = playerData_->getPlayerNumber();
	ib = playerData_->getBinder();
	KeyboardBinder* bindAux = static_cast<KeyboardBinder*>(ib);
	if (bindAux != nullptr) kBinder_ = bindAux;

	maxImpulseGrabbed_ = CONST(float, "IMPULSE_GRABBED");
	maxImpulseFloating_ = CONST(float, "IMPULSE_FLOATING");
	chargeMultiplier_ = CONST(float, "IMPULSE_MULTIPLIER");

	maxSpeedAfterImpulse_ = CONST(float, "MAX_SPEED_AFTER_IMPULSE") + maxImpulseFloating_;

	impulseCooldown_ = CONST(int, "IMPULSE_COOLDOWN");
}

void PlayerController::handleInput()
{
	//Empieza la carga
	if (impulseCooldownTimer_ >= impulseCooldown_ &&
		(ib->pressImpulse() || (ib->holdImpulse() && !chargingImpulse_))) {
		chargingImpulse_ = true;
		impulseCooldownTimer_ = 0;
	}//Soltarse
	else if (ib->releaseImpulse()) {
		Collider* attachedTo = attachesToObj_->getAttachedObject();

		dirImpulse_ = ib->getAimDir();
		dirImpulse_ *= impulseForce_;
		dirImpulse_.y *= -1; //hay que invertirlo para convertirlo en vector compatible con box2D
		//si estamos agarrados
		if (attachedTo != nullptr) {
			if (isImpulseValid(dirImpulse_))
			{
				dirImpulse_ *= -1;
				attachedTo->applyLinearImpulse(dirImpulse_, b2Vec2(0, 0));
				attachesToObj_->deAttachFromObject();
				dirImpulse_ *= -1;
				coll_->applyLinearImpulse(dirImpulse_, b2Vec2(0, 0)); //aplica la fuerza
			}
		}
		//si estamos flotando
		else {
			// si se pasa del l�mite de velocidad le bajamos los humos (s�lo aplica cuando no est�s agarrao)
			Vector2D velAfterImpulse = { (coll_->getLinearVelocity() + dirImpulse_).x, (coll_->getLinearVelocity() + dirImpulse_).y };
			if (!attachesToObj_->isAttached()) {
				if (abs(velAfterImpulse.getX()) > maxSpeedAfterImpulse_) dirImpulse_.x = 0;
				if (abs(velAfterImpulse.getY()) > maxSpeedAfterImpulse_) dirImpulse_.y = 0;
			}
			coll_->applyLinearImpulse(dirImpulse_, b2Vec2(0, 0)); //aplica la fuerza
		}

		//HAY QUE BORRAR-----------------------------------------------------------
		AnimatedPlayer* ap = GETCMP1_(AnimatedPlayer);
		(ap)->setAnim(1);
		//HAY QUE BORRAR-----------------------------------------------------------

		//si te impulsas contra el objeto contra el que estas agarrado
		//cuenta como que te sueltas
		chargingImpulse_ = false;
		chargedFrames_ = 0;
		impulseForce_ = 0;
		if (kBinder_ != nullptr) kBinder_->grabbed = false;
		impulseCooldownTimer_ = 0;
	}

	if (ib->releaseGrab()) {
		Collider* attachedObj = attachesToObj_->getAttachedObject();
		if (attachedObj != nullptr) {
			chargedFrames_ = 0;
			impulseForce_ = 0;
			chargingImpulse_ = false;
			attachesToObj_->deAttachFromObject();
			if (kBinder_ != nullptr)kBinder_->grabbed = false;
		}
	}
}

void PlayerController::update() {
	if (chargingImpulse_ && (attachesToObj_->isAttached() && impulseForce_ < maxImpulseGrabbed_) || impulseForce_ < maxImpulseFloating_) {
		chargedFrames_++;
		//Esta es la funcion del calculo de fuerza
		impulseForce_ = chargedFrames_ * chargeMultiplier_;
	}
	impulseCooldownTimer_++;
}