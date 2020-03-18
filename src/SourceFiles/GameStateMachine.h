#pragma once
#include <vector>
#include "GameState.h"

class GameStateMachine
{
private:
	std::vector<GameState*> states_;

	int currentState_ = 0;
public:
	GameStateMachine();
	virtual ~GameStateMachine();
	/*Cambia al estado pausa con un owner*/
	void setPauseOwner(int ownerID);

	void changeToState (int state);
	void deleteState(int state);

	void update();
	void render();
	void handleInput();
};

