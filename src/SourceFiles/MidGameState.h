#pragma once
#include "GameState.h"
#include "Texture.h"

class AnimatedViewer;
class AnimatedUIViewer;

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

	int numPlayers_ = 0;	//por constructora
	int roundWinner_ = 0;	//Por constructora y por reset
	int totalRounds_ = 0; //Viene de MatchInfo
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
	std::vector<AnimatedUIViewer*> playerRockets_;
	int framesUntilNextShake_ = 0;
	int shakeOffsetDistance_ = 3;

	//station
	AnimatedUIViewer* spaceStationViewer_ = nullptr;
	float spaceStationScaleFactor_ = 1;

	int ZeroTex;
	double markerScale_ = 1;
	double markerNumberScale_ = 1;


public:
	MidGameState(int numPlayers, int roundWinner) : numPlayers_(numPlayers), roundWinner_(roundWinner) {
	};
	virtual ~MidGameState();

	virtual void init();
	virtual void render();
	virtual void update();
	virtual void handleInput();
	virtual void onLoaded();

	void setWinner(int id) { roundWinner_ = id; };
};
