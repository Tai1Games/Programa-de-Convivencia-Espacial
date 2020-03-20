#include "PlayerController.h"
#include "InputHandler.h"
#include "Entity.h"

PlayerController::PlayerController(int p) :Component(ComponentType::PlayerController), 
	coll_(nullptr), attachesToObj_(nullptr), playerNumber_(p), chargeTimeStart_(0), dirImpulse_(1,0), impulseForce_(0)
{}

void PlayerController::init()
{
	coll_ = GETCMP1_(Collider); //pilla referencia al collider
	attachesToObj_ = GETCMP1_(AttachesToObjects);
}

void PlayerController::handleInput()
{
	InputHandler* ih = SDL_Game::instance()->getInputHandler();
	//Empieza la carga
	if (ih->isButtonJustDown(playerNumber_, SDL_CONTROLLER_BUTTON_A)) { 
		chargeTimeStart_ = SDL_Game::instance()->getTime();
		cout << chargeTimeStart_ << endl;
	}//Soltarse
	else if (ih->isButtonJustUp(playerNumber_, SDL_CONTROLLER_BUTTON_A)){
		dirImpulse_ = SDL_Game::instance()->getInputHandler()->getStickDir(playerNumber_, InputHandler::GAMEPADSTICK::LEFTSTICK);
		dirImpulse_ *= calculateForce(attachesToObj_->isAttached());
		dirImpulse_.y *= -1; //hay que invertirlo para convertirlo en vector compatible con box2D
		attachesToObj_->deAttachFromObject();
		coll_->applyLinearImpulse(dirImpulse_, b2Vec2(0, 0)); //aplica la fuerza

		chargeTimeStart_ = 0;
		impulseForce_ = 0;
	}
}

float PlayerController::calculateForce(bool isAttached) {
	//Funcion de calculo de fuerza, de momento lineal
	//El tiempo va dado en milisegundos

	Uint32 newForce = (SDL_Game::instance()->getTime() - chargeTimeStart_) / 100;
	if (isAttached) {
		if (newForce > IMPULSE_GRABBED)
			newForce = IMPULSE_GRABBED;
	}
	else if (newForce > IMPULSE_FLOATING)
		newForce = IMPULSE_FLOATING;

	return newForce;
}
