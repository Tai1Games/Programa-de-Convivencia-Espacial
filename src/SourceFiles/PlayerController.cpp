#include "PlayerController.h"
#include "InputHandler.h"
#include "Entity.h"

PlayerController::PlayerController() : Component(ComponentType::PlayerController)
{
	dirImpulse_ = b2Vec2(1, 0);
}

void PlayerController::init()
{
	playerData_ = GETCMP1_(PlayerData);
	coll_ = GETCMP1_(Collider); //pilla referencia al collider
	attachesToObj_ = GETCMP1_(AttachesToObjects);
}

void PlayerController::handleInput()
{
	if (SDL_Game::instance()->getInputHandler()->isButtonJustUp(playerData_->getPlayerNumber(), SDL_CONTROLLER_BUTTON_A) && attachesToObj_->isAttached()) {
		dirImpulse_ = SDL_Game::instance()->getInputHandler()->getStickDir(playerData_->getPlayerNumber(), InputHandler::GAMEPADSTICK::LEFTSTICK);
		dirImpulse_ *= IMPULSE_FROM_OBJECT_FORCE;
		dirImpulse_.y *= -1; //hay que invertirlo para convertirlo en vector compatible con box2D
		attachesToObj_->deAttachFromObject();
		coll_->applyLinearImpulse(dirImpulse_, b2Vec2(0, 0)); //aplica la fuerza
	}
}
