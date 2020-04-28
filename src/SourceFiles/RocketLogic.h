#pragma once
#include "Entity.h"

class Viewer;
class Collider;
class MidGameState;

class RocketLogic : public Component
{
private:
	int currentPoints_;
	Viewer* rocketViewer_ = nullptr;
	Collider* rocketColl_ = nullptr;
	MidGameState* gameState_ = nullptr;
	bool animationStarted_ = false;

	float YPositionObjective_ = 0;
public:
	RocketLogic(int points, MidGameState* gameState) : Component(ComponentType::RocketLogic) { currentPoints_ = points; gameState_ = gameState; }
	~RocketLogic() {};
	virtual void init();
	virtual void update();
	void startAnimation();
};

