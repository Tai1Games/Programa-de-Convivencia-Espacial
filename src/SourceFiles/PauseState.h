#pragma once
#include "GameState.h"
#include "Entity.h"
#include "checkML.h"

using namespace std;

class PauseState : public GameState
{
private:
public:
	PauseState() : GameState() {};
	~PauseState(){};
	virtual void init();
	virtual void handleInput();
};

