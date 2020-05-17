#pragma once
#include "Component.h"
#include "checkML.h"
#include "Collision.h"
#include "PlayerData.h"
#include "CollisionHandler.h"

class TriggerButton : public Component
{
private:
	int stateToChange = 0;

	int framesInside = 0;
	int timeToActivate = 0;
	bool playerDetected_ = false;

public:
	TriggerButton(int state) : Component(ComponentType::TriggerButton) { stateToChange = state; }

	virtual void init() override;
	virtual void update() override;
	virtual void handleInput() override {};
	virtual void onCollisionEnter(Collision* c);
	virtual void onCollisionExit(Collision* c);
	void PassState();
};



