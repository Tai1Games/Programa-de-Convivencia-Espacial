#pragma once
#include <vector>
#include <string>
#include "GameState.h"
#include "checkML.h"

class GameStateMachine
{
private:
	std::vector<GameState*> states_;

	int currentState_ = -1;
public:
	GameStateMachine();
	virtual ~GameStateMachine();
	/*Cambia al estado pausa con un owner*/
	void setPauseOwner(int ownerID);

	void changeToState(int state, int numberOfPlayers = 1, int gameMode = 0, std::string tileMap = "");
	void deleteState(int state);

	void update();
	void render();
	void handleInput();
};

