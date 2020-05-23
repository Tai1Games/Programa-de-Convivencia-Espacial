#pragma once
#include "Component.h"
#include "checkML.h"
#include "Collision.h"
#include "PlayerData.h"
#include "CollisionHandler.h"
#include "AdvancedAnimatedViewer.h"

class TriggerButton : public Component
{
private:
	string stateToChange = " ";

	int framesInside = 0;
	int timeToActivate = 0;
	bool playerDetected_ = false;

	AnimatedViewer* viewer_ = nullptr;

public:
	TriggerButton(string state) : Component(ComponentType::TriggerButton) { stateToChange = state; }

	virtual void init() override;
	virtual void update() override;
	virtual void handleInput() override {};
	virtual void onCollisionEnter(Collision* c);
	virtual void onCollisionExit(Collision* c);
	void PassState();
};



