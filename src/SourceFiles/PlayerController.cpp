#include "PlayerController.h"
#include "InputHandler.h"
#include "Entity.h"

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

	maxImpulseGrabbed_ = CONST(float, "IMPULSE_GRABBED");
	maxImpulseFloating_ = CONST(float, "IMPULSE_FLOATING");
	chargeMultiplier_ = CONST(float, "IMPULSE_MULTIPLIER");
}

void PlayerController::handleInput()
{
	InputHandler* ih = SDL_Game::instance()->getInputHandler();
	//Empieza la carga
	if (ih->isButtonJustDown(playerNumber_, SDL_CONTROLLER_BUTTON_A)) {
		chargingImpulse_ = true;
	}//Soltarse
	else if (ih->isButtonJustUp(playerNumber_, SDL_CONTROLLER_BUTTON_A)) {
		dirImpulse_ = SDL_Game::instance()->getInputHandler()->getLastStickDir(playerNumber_, InputHandler::GAMEPADSTICK::LEFTSTICK);
		dirImpulse_ *= impulseForce_;
		dirImpulse_.y *= -1; //hay que invertirlo para convertirlo en vector compatible con box2D
		Collider* attachedObj = attachesToObj_->getAttachedObject();
		if (attachedObj) {
			dirImpulse_ *= -1;
			attachedObj->applyLinearImpulse(dirImpulse_, b2Vec2(0, 0));
			dirImpulse_ *= -1;
		}
		attachesToObj_->deAttachFromObject();
		coll_->applyLinearImpulse(dirImpulse_, b2Vec2(0, 0)); //aplica la fuerza
		chargingImpulse_ = false;
		chargedFrames_ = 0;
		impulseForce_ = 0;
	}
}

void PlayerController::update() {
	if (chargingImpulse_) {
		if ((attachesToObj_->isAttached() && impulseForce_ < maxImpulseGrabbed_) || impulseForce_ < maxImpulseFloating_) {
			chargedFrames_++;
			//Esta es la funcion del calculo de fuerza
			impulseForce_ = chargedFrames_ * chargeMultiplier_;
		}
	}
}
