#include "GameStateMachine.h"
#include "StocksGameMode.h"
#include "WiFightGameMode.h"
#include "ControllerGameMode.h"
#include "CapitalismGameMode.h"
#include "TimeGameMode.h"
#include "Constants.h"
#include "PlayState.h"
#include "PauseState.h"

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
		if (states_[state] == nullptr) {
			//create state
			//states_[state] = new... se necesita struct? o switch tal cual xd
			switch (state) {
			case States::menu:
				//deleteState(currentState_);
				break;
			case States::play:
				//deleteState(currentState_);

				states_[state] = new PlayState(new CapitalismGameMode(4), "BoilerRoom"); //LivingRoom, BoilerRoom

				break;
			case States::pause:
				//if (states_[state] != nullptr)	delete states_[state];
				states_[state] = new PauseState();
				break;
			}
			//inicializar la nueva escena
			states_[state]->init();
		}
		currentState_ = state;
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
