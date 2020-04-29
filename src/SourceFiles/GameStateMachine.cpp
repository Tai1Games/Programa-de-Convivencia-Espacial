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

GameStateMachine::GameStateMachine() {
	for (short i = 0; i < States::NUMBER_OF_STATES; i++)
		states_.push_back(nullptr);

	blackSquare_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::Debug);
	transitionFrames_ = CONST(Uint8, "SCENE_TRANSITION_FRAMES");
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
		if (states_[state] == nullptr) {
			//create state
			//states_[state] = new... se necesita struct? o switch tal cual xd
			switch (state) {
			case States::menu:
				for (int i = 1; i < states_.size(); i++) deleteState(i); //borrar el playState y menu para poder crear otros
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
				break;
			}
			case States::pause:
				//if (states_[state] != nullptr)	delete states_[state];
				states_[state] = new PauseState();
				break;
			}
			//inicializar la nueva escena
			states_[state]->init();
		}
		newState_ = state;
		stateActive_ = false;
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
	if (stateTransitioning_) {
		if (currentTransitionFrame_ < transitionFrames_) {
			if (currentTransitionFrame_ == transitionFrames_ / 2)
				currentState_ = newState_;
			blackSquare_->render({})
		}
		else
		{
			currentTransitionFrame_ = 0;
			stateTransitioning_ = true;
			stateActive_ = true;
		}
	}
	SDL_RenderPresent(SDL_Game::instance()->getRenderer());
}

void GameStateMachine::handleInput() {
	states_[currentState_]->handleInput();
}

void GameStateMachine::gameCycle() {
	if (stateActive_) {
		handleInput();
		update();
	}
	render();
}
