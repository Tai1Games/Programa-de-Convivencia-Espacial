#pragma once
#include <list>
#include "GameMode.h"
#include "Entity.h"
#include "checkML.h"
#include "Resources.h"

using namespace std;

class CreditsState : public GameState
{
private:
	double secondsPerFrame_ = 0;
	Texture* fondo_ = nullptr;
	Entity* continueText = nullptr;

	InputBinder* playerControl;
public:
	CreditsState() {};
	virtual ~CreditsState();

	virtual void init() override;
	virtual void render() override;
	virtual void handleInput() override;
};
