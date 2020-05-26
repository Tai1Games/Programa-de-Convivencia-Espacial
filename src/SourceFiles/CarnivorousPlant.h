#pragma once
#include "Component.h"
#include "checkML.h"
#include "Collision.h"
#include "PlayerData.h"
#include "Health.h"
#include "Wallet.h"
#include "CollisionHandler.h"
#include "CarnivorousPlantViewer.h"

class CarnivorousPlant : public Component
{
private:
	CarnivorousPlantViewer* viewer_;
	int minAnimationSpeed_, maxAnimationSpeed_, playersInside_ = 0, marginUntilBite_ = 5,
		coinDamage_, damage_, maxFrames_, frameCount_ = 0;
	float increase_, actualSpeed_;
	bool playerDetected_ = false;
	Entity* player_ = nullptr;
	CollisionHandler* playerCollHandler_ = nullptr;
	Wallet* walletPlayer_ = nullptr;

public:
	CarnivorousPlant() : Component(ComponentType::CarnivorousPlant) {}

	virtual void init() override;
	virtual void update() override;
	virtual void onCollisionEnter(Collision* c);
	virtual void onCollisionExit(Collision* c);
	void bite();
};
