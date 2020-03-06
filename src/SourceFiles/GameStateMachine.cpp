#include "GameStateMachine.h"
#include "Constants.h"
#include "PlayState.h"

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
				states_[state] = new PlayState();
				break;
			case States::pause:
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
	states_[currentState_]->render();
}

void GameStateMachine::handleInput() {
	states_[currentState_]->handleInput();
}