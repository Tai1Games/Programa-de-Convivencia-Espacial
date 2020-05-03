#pragma once
#include "GameState.h"
#include "Texture.h"

class AnimatedViewer;

class MidGameState : public GameState
{
private:

	enum animationState
	{
		waiting,
		movingWinner,
		waitingButton,
		zoom,
	};

	int numPlayers_;
	int roundWinner_;
	vector<int> points;
	Texture* fondo = nullptr;

	//Input
	bool buttonPush = false;
	Entity* continueText = nullptr;
	//time

	animationState currentState = waiting;
	int currentFrame = 0;
	int watingStateDuration_ = 120;
	int zoomStateDuration_ = 180;
	int frameZoomStateEnds_ = 0;
	int framesBetweenShakes_ = 5;

	//rocket
	int distanceBetweenRockets_ = 200;
	int rocketXPositionObjective_ = 0;
	int rocketMovementY_ = 3;
	int rocketMovementX_ = 1;
	int distanceGainedPerFrame_ = 2;
	int startingXPosition_ = 450;
	int distanceGainedByPoint_ = 150;
	std::vector<AnimatedViewer*> playerRockets_;

	int framesUntilNextShake_ = 0;
	int shakeOffsetDistance_ = 3;

	//station
	float spaceStationScaleFactor_ = 1;
	float scaleGrowthPerFrame_ = 0.02;
	b2Vec2 spaceStationOffset = b2Vec2(0, 0);
	AnimatedViewer* spaceStationViewer_ = nullptr;

	int spaceStationWidht_ = 300;
	int spaceStationHeight_ = 150;

public:
	MidGameState(int numPlayers, int roundWinner) { numPlayers_ = numPlayers; roundWinner_ = roundWinner; };
	~MidGameState();

	virtual void init();
	virtual void render();
	virtual void update();
	virtual void handleInput();
	virtual void resetScene();
};

