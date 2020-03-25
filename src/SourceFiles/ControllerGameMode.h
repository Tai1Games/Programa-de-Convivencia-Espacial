#pragma once
#include "GameMode.h"
#include "GameMode.h"
#include "Health.h"
#include "HealthViewer.h"
#include "box2d.h"
#include "Hands.h"
#include "PlayerData.h"

class ControllerGameMode : public GameMode
{
private:
	vector<double> controllerTimes_;
	Entity* winner = nullptr;
public:
	ControllerGameMode() {};
	virtual void init(PlayState* game);
	virtual void render();
	virtual void update();
	vector<double> getTimes() { return controllerTimes_; }
};

