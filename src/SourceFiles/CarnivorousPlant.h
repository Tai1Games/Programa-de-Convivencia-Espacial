#pragma once
#include "Component.h"
#include "checkML.h"
#include "Viewer.h"
#include "Collision.h"
#include "PlayerData.h"

class CarnivorousPlant : public Component
{
private:
	Viewer* viewer_;
	int frame_, minAnimationSpeed_, maxAnimationSpeed_,
		idleFrames_, eatingFrames_, frameSize_, limitTime_,
		timedPassed_;
	float aumento_, actualSpeed_;
	bool idle_, playerDetected_;
public:
	CarnivorousPlant() :Component(ComponentType::CarnivorousPlant) {}

	virtual void init() override;
	virtual void update() override;
	virtual void onCollisionEnter(Collision* c);
	virtual void onCollisionExit(Collision* c);
};

