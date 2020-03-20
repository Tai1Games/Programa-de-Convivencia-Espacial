#include "PlayerController.h"
#include "InputHandler.h"
#include "Entity.h"

PlayerController::PlayerController(int p) :Component(ComponentType::PlayerController), 
	coll_(nullptr), attachesToObj_(nullptr), playerNumber_(p), chargeTime(0), dirImpulse_(1,0), impulseForce_(0)
{}

void PlayerController::init()
{
	coll_ = GETCMP1_(Collider); //pilla referencia al collider
	attachesToObj_ = GETCMP1_(AttachesToObjects);
}

void PlayerController::handleInput()
{
	if (SDL_Game::instance()->getInputHandler()->isButtonJustUp(playerNumber_, SDL_CONTROLLER_BUTTON_A) && attachesToObj_->isAttached()) {
		dirImpulse_ = SDL_Game::instance()->getInputHandler()->getStickDir(playerNumber_, InputHandler::GAMEPADSTICK::LEFTSTICK);
		dirImpulse_ *= IMPULSE_FROM_OBJECT_FORCE;
		dirImpulse_.y *= -1; //hay que invertirlo para convertirlo en vector compatible con box2D
		attachesToObj_->deAttachFromObject();
		coll_->applyLinearImpulse(dirImpulse_, b2Vec2(0, 0)); //aplica la fuerza
	}
}
