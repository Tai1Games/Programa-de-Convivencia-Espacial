#pragma once
#include "Component.h"
#include "checkML.h"
#include "Collision.h"
#include "PlayerData.h"
#include "CollisionHandler.h"

class TriggerButton : public Component
{
private:
	TriggerButton* viewer_;

	int playersInside_ = 0;
	float increase_, actualSpeed_;
	bool playerDetected_ = false;
	Entity* player_ = nullptr;
	CollisionHandler* playerCollHandler_ = nullptr;
	Wallet* walletPlayer_ = nullptr;

public:
	TriggerButton() : Component(ComponentType::TriggerButton) {}

	virtual void init() override;
	virtual void update() override;
	virtual void onCollisionEnter(Collision* c);
	virtual void onCollisionExit(Collision* c);
	void PassState();
};



