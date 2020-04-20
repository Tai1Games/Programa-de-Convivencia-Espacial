#pragma once
#include "Component.h"

class Collider;
class Hands;

class TomatoLogic : public Component
{
private:
	Collider* colTomato_ = nullptr;
	Hands* playerHands_ = nullptr;

	bool activated_ = false;
	int timeForActivation_ = 1000;
	int timeSinceActivated_ = 0;
public:
	TomatoLogic() : Component(ComponentType::TomatoLogic){};
	~TomatoLogic() {};

	virtual void init();
	virtual void update();
	virtual void onCollisionEnter(Collision* c);
};

