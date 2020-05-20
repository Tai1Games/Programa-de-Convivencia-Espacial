#include "TriggerButton.h"

void TriggerButton::init()
{
	//viewer_ = entity_->getComponent<CarnivorousPlantViewer>(ComponentType::AdvancedAnimatedViewer);
	timeToActivate = CONST(int, "TRIGGER_BUTTON_TIME");
	
	

	//viewer_->startAnimation(-1, 0, idleFrames_, 0);
}

void TriggerButton::update()
{
	if (playerDetected_) {
		framesInside++;

		if (framesInside >= timeToActivate) {
			//Pasas al modo correspondiente
			PassState();
		}
	}
}

void TriggerButton::PassState()
{
	if (stateToChange == "Play") {
		SDL_Game::instance()->getStateMachine()->transitionToState(States::lobby, 0);
	}
	else if (stateToChange == "Options") {
		//SDL_Game::instance()->getStateMachine()->changeToState(States::pause, 0);
	}
	else if (stateToChange == "Credits") {
		//SDL_Game::instance()->getStateMachine()->changeToState(States::playableMenu/*States::Credits*/, 0);
	}
	else if (stateToChange == "Exit") {
		SDL_Game::instance()->exitGame();
	}
	
}

void TriggerButton::onCollisionEnter(Collision* c)
{
	if (c->hitFixture->GetFilterData().categoryBits & Collider::CollisionLayer::Player) {
		playerDetected_ = true;
	}
}

void TriggerButton::onCollisionExit(Collision* c)
{
	if (c->hitFixture->GetFilterData().categoryBits & Collider::CollisionLayer::Player) {
		
		playerDetected_ = false;
		
		framesInside = 0;
	}
}