#pragma once
#include "Component.h"
#include "checkML.h"
#include "Viewer.h"
#include "Collision.h"
#include "PlayerData.h"
#include "Health.h"
#include "Wallet.h"
#include "CollisionHandler.h"

class CarnivorousPlant : public Component
{
private:
	Viewer* viewer_;
	int frame_, minAnimationSpeed_, maxAnimationSpeed_,
		idleFrames_, eatingFrames_, frameSize_, coinDMG, damage;
	float aumento_, actualSpeed_, timePassed_, enterTime_, limitTime_;
	bool idle_, playerDetected_;
	Entity* player_;
	CollisionHandler* playerCollHandler_;
	Wallet* walletPlayer_;

public:
	CarnivorousPlant() :Component(ComponentType::CarnivorousPlant) {}

	virtual void init() override;
	virtual void update() override;
	virtual void onCollisionEnter(Collision* c);
	virtual void onCollisionExit(Collision* c);

	void resetCycle();
};

