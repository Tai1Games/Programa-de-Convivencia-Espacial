#pragma once
#include "GameMode.h"
#include "GameMode.h"
#include "Health.h"
#include "HealthViewer.h"
#include "box2d.h"
#include "Hands.h"
#include "PlayerData.h"
#include "WeaponFactory.h"
#include "PlayState.h"
#include "GameState.h"
#include "Weapon.h"

class ControllerGameMode : public GameMode
{
private:
	vector<double> controllerTimes_;
	Weapon* controller_ = nullptr;
	vector<Viewer*> emptyProgressBars_;
	vector<Viewer*> progressBars_;
public:
	ControllerGameMode() {};
	virtual ~ControllerGameMode();
	virtual void init(PlayState* game);
	virtual void render();
	virtual void update();
	void updateProgressBar(Viewer& progressBar,const float& progressValue);
	vector<double> getTimes() { return controllerTimes_; }
};

