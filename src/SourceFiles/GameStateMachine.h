#pragma once
#include <vector>
#include "GameState.h"

class GameStateMachine
{
private:
	std::vector<GameState*> states_;

	int currentState_ = 0;

	SDL_Game* game_ = nullptr;
public:
	GameStateMachine(SDL_Game* game);
	virtual ~GameStateMachine();
	void changeToState (int state);
	void deleteState(int state);

	void update();
	void render();
	void handleInput();
};

