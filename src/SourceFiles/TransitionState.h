#pragma once
#include <vector>
#include "GameState.h"
#include "checkML.h"
#include "Texture.h"

class TransitionState :
	public GameState
{
private:
	//Scene transitions
	int currentState_ = -1, toState_ = -1;
	int WIN_WIDTH = 0, WIN_HEIGHT = 0;
	int currentTransitionFrame_ = 0;
	int transitionFrames_ = 0;
	vector<GameState*>* gameStatesVector_ = nullptr;
public:
	TransitionState(int fromState, int toState, vector<GameState*>* gameStatesVector);
	virtual ~TransitionState() {};

	virtual void update() override;
	virtual void render() override;
};

