#pragma once
#include "GameState.h"

class AnimatedViewer;

class MidGameState : public GameState
{
private:
	int numPlayers_;
	int roundWinner_;

	bool rocketAnimationStarted_ = false;
	bool rocketAnimationEnded_ = false;
	int currentFrame = 0;

	std::vector<AnimatedViewer*> playerRockets_;

	//Load of constants.
	int distanceBetweenRockets_ = 200;
	int startingXPosition_ = 300;
	int distanceGainedByPoint_ = 150;
	int framesUntilAnimationStart_ = 120;
	int rocketXPositionObjective_ = 0;
	int distanceGainedPerFrame_ = 2;

public:
	MidGameState(int numPlayers, int roundWinner) { numPlayers_ = numPlayers; roundWinner_ = roundWinner; };
	~MidGameState();

	virtual void init();
	virtual void render();
	virtual void update();
	virtual void handleInput();

	virtual void rocketReachedDestination();
};

