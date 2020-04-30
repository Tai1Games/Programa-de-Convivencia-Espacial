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
	bool spaceStationAnimationStarted_ = false;
	int currentFrame = 0;

	std::vector<AnimatedViewer*> playerRockets_;
	AnimatedViewer* spaceStationViewer_ = nullptr;

	//Load of constants.
	int distanceBetweenRockets_ = 200;
	int startingXPosition_ = 300;
	int distanceGainedByPoint_ = 150;
	int framesUntilAnimationStart_ = 120;
	int spaceStationAnimationDuration_ = 360;
	int framesUntilSpaceStationAnimationEnds_ = 0;
	int rocketXPositionObjective_ = 0;
	int distanceGainedPerFrame_ = 2;
	double spaceStationGrowthPerFrame_ = 0.05;

	int spaceStationWidht_ = 300;
	int spaceStationHeight_ = 150;

public:
	MidGameState(int numPlayers, int roundWinner) { numPlayers_ = numPlayers; roundWinner_ = roundWinner; };
	~MidGameState();

	virtual void init();
	virtual void render();
	virtual void update();
	virtual void handleInput();
};

