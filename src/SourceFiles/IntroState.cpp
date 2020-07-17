#include "IntroState.h"
#include "Constants.h"
#include "SDL.h"
#include "SDL_Game.h"

void IntroState::init() {
	ih_ = SDL_Game::instance()->getInputHandler();
}

void IntroState::handleInput() {
	GameState::handleInput();
	if (ih_->isButtonDown(0, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A))
		SDL_Game::instance()->getStateMachine()->changeToState(States::playableMenu);
}