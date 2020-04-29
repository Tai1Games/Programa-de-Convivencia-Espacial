#pragma once
#include <vector>
#include <string>
#include "GameState.h"
#include "checkML.h"
#include "Texture.h"

class GameStateMachine
{
private:
	std::vector<GameState*> states_;

	int currentState_ = -1;
	Uint8 newState_ = -1;
	bool stateActive_ = false;

	//Scene transitions
	bool stateTransitioning_ = false;
	Uint8 currentTransitionFrame_ = 0;
	Uint8 transitionFrames_ = 0;
	Texture* blackSquare_ = nullptr;

	void update();
	void render();
	void handleInput();
public:
	GameStateMachine();
	virtual ~GameStateMachine();
	/*Cambia al estado pausa con un owner*/
	void setPauseOwner(int ownerID);

	void changeToState(int state, int numberOfPlayers = 1, int gameMode = 0, std::string tileMap = "");
	void deleteState(int state);

	void gameCycle();
	void inline setStateActive(bool active) { stateActive_ = active; };
};

