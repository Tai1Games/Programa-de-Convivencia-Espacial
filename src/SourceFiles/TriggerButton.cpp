#include "TriggerButton.h"

void TriggerButton::init()
{

	viewer_ = entity_->getComponent<AnimatedViewer>(ComponentType::Viewer); //pilla referencia al viewer
	timeToActivate = CONST(int, "TRIGGER_BUTTON_TIME");
	viewer_->stopAnimation();
}

void TriggerButton::update()
{
	if (playerDetected_) {
		framesInside++;

		if (framesInside >= timeToActivate) {
			//Pasas al modo correspondiente según que valga tu atributo state
			PassState();
		}
	}
}

void TriggerButton::PassState()
{
	framesInside = 0;
	if (stateToChange == "Play") {
		if (SDL_Game::instance()->getStateMachine()->getStateById(States::lobby) == nullptr) {
			SDL_Game::instance()->getStateMachine()->transitionToState(States::lobby, 0);
		}else SDL_Game::instance()->getStateMachine()->transitionToState(States::menu, 0);

	}
	else if (stateToChange == "Options") {
		SDL_Game::instance()->getStateMachine()->transitionToState(States::options, 0);
		//SDL_Game::instance()->getStateMachine()->changeToState(States::pause, 0);
	}
	else if (stateToChange == "Credits") {
		SDL_Game::instance()->getStateMachine()->transitionToState(States::credits, 0);
		//SDL_Game::instance()->getStateMachine()->changeToState(States::States::Credits, 0);
	}
	else if (stateToChange == "Exit") {
		SDL_Game::instance()->exitGame();
	}
	viewer_->setFrame(0, 0);
}

void TriggerButton::onCollisionEnter(Collision* c)
{
	if (c->hitFixture->GetFilterData().categoryBits & Collider::CollisionLayer::Player) {
		playerDetected_ = true;
		viewer_->startAnimation(0, 0, CONST(int, "TRIGGER_BUTTON_FRAMES"), 0);
	}
}

void TriggerButton::onCollisionExit(Collision* c)
{
	if (c->hitFixture->GetFilterData().categoryBits & Collider::CollisionLayer::Player) {

		playerDetected_ = false;
		viewer_->setFrame(0, 0);
		viewer_->stopAnimation();
		framesInside = 0;
	}
}