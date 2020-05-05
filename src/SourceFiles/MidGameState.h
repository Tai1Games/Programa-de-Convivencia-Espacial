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

	int numPlayers_;	//por constructora
	int roundWinner_;	//Por constructora y por reset
	int totalRounds=10; //Viene de la Super clase
	Texture* fondo = nullptr;

	//Input
	bool buttonPush = false;
	Entity* continueText = nullptr;

	//time
	animationState currentState = waiting;
	int currentFrame = 0;
	int frameZoomStateEnds_ = 0;

	//Markers
	std::vector <Entity*> markers;

	//rocketS
	int distanceBetweenRockets_ = 200;	//Distancia normal
	int rocketXPositionObjective_ = 0;
	int distanceGainedByPoint_ = 150;	//Por defecto
	std::vector<AnimatedViewer*> playerRockets_;
	int framesUntilNextShake_ = 0;
	int shakeOffsetDistance_ = 3;

	//station
	AnimatedViewer* spaceStationViewer_ = nullptr;
	float spaceStationScaleFactor_ = 1;
	

public:
	MidGameState(int numPlayers, int roundWinner) { 
		numPlayers_ = numPlayers; 
		roundWinner_ = roundWinner;
	};
	virtual ~MidGameState();

	virtual void init();
	virtual void render();
	virtual void update();
	virtual void handleInput();
	virtual void resetScene();
};
