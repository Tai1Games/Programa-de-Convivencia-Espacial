#pragma once
#include "GameState.h"

class RocketLogic;
class b2World;

class MidGameState : public GameState
{
private:
	b2World* b2World_ = nullptr;
	std::vector<RocketLogic*> playerRockets;
	int numPlayers_;
	int roundWinner_;

	bool rocketAnimationStarted = false;
	int currentFrame = 0;

	//Load of constants.
	int distanceBetweenRockets_ = 5;
	int startingYPosition_ = 5;
	int distanceGainedByPoint_ = 1;
	int framesUntilAnimationStart_ = 120;

public:
	MidGameState(int numPlayers, int roundWinner) { numPlayers_ = numPlayers; roundWinner_ = roundWinner; };
	~MidGameState();

	virtual void init();
	virtual void render();
	virtual void update();
	virtual void handleInput();

	virtual void rocketReachedDestination();
};

