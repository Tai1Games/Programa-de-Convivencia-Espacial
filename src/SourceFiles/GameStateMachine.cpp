#include "GameStateMachine.h"
#include "StocksGameMode.h"
#include "WiFightGameMode.h"
#include "ControllerGameMode.h"
#include "CapitalismGameMode.h"
#include "TimeGameMode.h"
#include "TutorialGameMode.h"
#include "Constants.h"
#include "MatchInfo.h"

#include "PlayState.h"
#include "PauseState.h"
#include "MenuState.h"
#include "TransitionState.h"
#include "LobbyState.h"

GameStateMachine::GameStateMachine() {
	for (short i = 0; i < States::NUMBER_OF_STATES; i++)
		states_.push_back(nullptr);
}

GameStateMachine::~GameStateMachine() {
	for (GameState* state : states_) {
		delete state;
	}
	states_.clear();

	delete matchInfo_;
}

void GameStateMachine::setPauseOwner(int ownerID)
{
	changeToState(States::pause);
	if (PauseState* pause = static_cast<PauseState*>(states_[States::pause]))
		pause->setOwner(ownerID);
}

void GameStateMachine::changeToState(int state, int gameMode, string tileMap) {
	if (state != currentState_ && state < States::NUMBER_OF_STATES) {
		loadState(state, gameMode, tileMap);
		currentState_ = state;
		states_[state]->onLoaded();
		if (states_[States::transition] != nullptr) {
			deleteState(States::transition);
		}
	}
}

void GameStateMachine::transitionToState(int state, int gameMode, string tileMap) {
	loadState(state, gameMode, tileMap);
	states_[States::transition] = new TransitionState(currentState_, state, &states_);
	states_[States::transition]->init();
	currentState_ = States::transition;
}

void GameStateMachine::loadState(int state, int gameMode, string tileMap) {
	if (states_[state] == nullptr) {
		//create state
		//states_[state] = new... se necesita struct? o switch tal cual xd
		switch (state) {
		case States::menu:		
			states_[state] = new MenuState(1); //numberOfPlayers usado como ownerID
			break;
		case States::play:
		{
			if (gameMode < NUMBER_OF_GAMEMODES) {
				switch (gameMode) {
				case (GamemodeID::Capitalism):
					states_[state] = new PlayState(new CapitalismGameMode(matchInfo_), tileMap);
					break;
				case (GamemodeID::Controller):
					states_[state] = new PlayState(new ControllerGameMode(matchInfo_), tileMap);
					break;
				case (GamemodeID::Stocks):
					states_[state] = new PlayState(new StocksGameMode(matchInfo_), tileMap);
					break;
				case (GamemodeID::WiFight):
					states_[state] = new PlayState(new WiFightGameMode(matchInfo_), tileMap);
					break;
				case (GamemodeID::Timed):
					states_[state] = new PlayState(new TimeGameMode(matchInfo_), tileMap);
					break;
				case (GamemodeID::Tutorial):
					states_[state] = new PlayState(new TutorialGameMode(matchInfo_), tileMap);
					break;
				}
			}
			
		}
		break; // :P
		case States::lobby: {
			states_[state] = new LobbyState();
		}
		break;
		case States::pause:
			//if (states_[state] != nullptr)	delete states_[state];
			states_[state] = new PauseState();
			break;
		}
		//inicializar la nueva escena
		states_[state]->init();
	}
	else if (state==States::menu){
		//borrar playState para crear otro
		deleteState(States::play);
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

void GameStateMachine::gameCycle() {
	handleInput();
	update();
	render();
}
