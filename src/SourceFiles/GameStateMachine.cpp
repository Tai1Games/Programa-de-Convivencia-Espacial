#include "GameStateMachine.h"
#include "StocksGameMode.h"
#include "WiFightGameMode.h"
#include "Constants.h"
#include "PlayState.h"
#include "PauseState.h"
#include "ControllerGameMode.h"

GameStateMachine::GameStateMachine() {
	for (short i = 0; i < States::NUMBER_OF_STATES; i++)
		states_.push_back(nullptr);
}

GameStateMachine::~GameStateMachine() {
	for (GameState* state : states_) {
		delete state;
	}
	states_.clear();
}

void GameStateMachine::setPauseOwner(int ownerID)
{
	changeToState(States::pause);
	if(PauseState* pause = static_cast<PauseState*>(states_[States::pause]))
	pause->setOwner(ownerID);
}

void GameStateMachine::changeToState(int state) {
	if (state != currentState_ && state < States::NUMBER_OF_STATES) {
		currentState_ = state;
		if (states_[state] == nullptr) {
			//create state
			//states_[state] = new... se necesita struct? o switch tal cual xd
			switch (state) {
			case States::menu:
				break;
			case States::play:
				states_[state] = new PlayState(new WiFightGameMode(2));
				break;
			case States::pause:
				states_[state] = new PauseState();
				break;
			}
			//inicializar la nueva escena
			states_[state]->init();
		}
	}
}

void GameStateMachine::deleteState(int state) {
	if (state != currentState_ && state < States::NUMBER_OF_STATES) {
		delete states_[state];
		states_[state] = nullptr;
	}
}

void GameStateMachine::update() {
	states_[currentState_]->update();
}

void GameStateMachine::render() {
	SDL_RenderClear(SDL_Game::instance()->getRenderer());
	states_[currentState_]->render();
	SDL_RenderPresent(SDL_Game::instance()->getRenderer());
}

void GameStateMachine::handleInput() {
	states_[currentState_]->handleInput();
}