#pragma once
#include "Component.h"
#include "checkML.h"
#include "AnimatedViewer.h"
#include "Collision.h"
#include "PlayerData.h"
#include "Health.h"
#include "Wallet.h"
#include "CollisionHandler.h"

class CarnivorousPlant : public Component
{
private:
	AnimatedViewer* viewer_;
	int frame_, minAnimationSpeed_, maxAnimationSpeed_, playersInside_,
		idleFrames_, eatingFrames_, frameSize_, coinDMG, damage, maxFrames_, frameCount_;
	float increase_, actualSpeed_;
	bool idle_, playerDetected_;
	Entity* player_;
	CollisionHandler* playerCollHandler_;
	Wallet* walletPlayer_;

public:
	CarnivorousPlant() : Component(ComponentType::CarnivorousPlant) {}

	virtual void init() override;
	virtual void update() override;
	virtual void onCollisionEnter(Collision* c);
	virtual void onCollisionExit(Collision* c);
};

