#include "GameStateMachine.h"
#include "StocksGameMode.h"
#include "WiFightGameMode.h"
#include "ControllerGameMode.h"
#include "CapitalismGameMode.h"
#include "TimeGameMode.h"
#include "Constants.h"

#include "PlayState.h"
#include "PauseState.h"
#include "MenuState.h"
#include "MidGameState.h"
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
}

void GameStateMachine::setPauseOwner(int ownerID)
{
	changeToState(States::pause);
	if (PauseState* pause = static_cast<PauseState*>(states_[States::pause]))
		pause->setOwner(ownerID);
}

void GameStateMachine::changeToState(int state, int numberOfPlayers, int gameMode, string tileMap) {
	if (state != currentState_ && state < States::NUMBER_OF_STATES) {
		loadState(state, numberOfPlayers, gameMode, tileMap);
		currentState_ = state;
		if (states_[States::transition] != nullptr) {
			deleteState(States::transition);
		}
	}
}

void GameStateMachine::transitionToState(int state, int numberOfPlayers, int gameMode, string tileMap) {
	loadState(state, numberOfPlayers, gameMode, tileMap);
	states_[States::transition] = new TransitionState(currentState_, state, &states_);
	states_[States::transition]->init();
	currentState_ = States::transition;
}

void GameStateMachine::loadState(int state, int numberOfPlayers, int gameMode, string tileMap) {
	if (state == States::menu || states_[state] == nullptr) {
		//create state
		//states_[state] = new... se necesita struct? o switch tal cual xd
		switch (state) {
		case States::menu:
			deleteState(States::menu); //borrar el playState y menu para poder crear otros
			deleteState(States::play);
			states_[state] = new MenuState(numberOfPlayers); //numberOfPlayers usado como ownerID
			break;
		case States::play:
		{
			if (gameMode < NUMBER_OF_GAMEMODES) {
				switch (gameMode) {
				case (GamemodeID::Capitalism):
					states_[state] = new PlayState(new CapitalismGameMode(numberOfPlayers), tileMap);
					break;
				case (GamemodeID::Controller):
					states_[state] = new PlayState(new ControllerGameMode(numberOfPlayers), tileMap);
					break;
				case (GamemodeID::Stocks):
					states_[state] = new PlayState(new StocksGameMode(numberOfPlayers), tileMap);
					break;
				case (GamemodeID::WiFight):
					states_[state] = new PlayState(new WiFightGameMode(numberOfPlayers), tileMap);
					break;
				case (GamemodeID::Timed):
					states_[state] = new PlayState(new TimeGameMode(numberOfPlayers), tileMap);
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
		case States::midGame:			//Jugadores totales-----Jugador que gana la ronda
			states_[state] = new MidGameState(numberOfPlayers+3, 1);
			break;
		}
		//inicializar la nueva escena
		states_[state]->init();
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
