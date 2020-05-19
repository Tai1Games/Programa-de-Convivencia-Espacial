#pragma once
#include "Component.h"

class FireBallGenerator;
class Collider;
class AnimatedViewer;

class BoilerButtonLogic : public Component
{
private:
	FireBallGenerator* fbGen_ = nullptr;
	AnimatedViewer* buttonViewer_ = nullptr;

	bool inc_dec_ = false;
	bool activated = false;
	int timeForReactivation_ = 0;
	int currentFrame_ = 0;
	int reactivationFrame_ = 0;

	//Initialized at init()
	int reactivationCd_ = 0;
	int minForceForAcivation_ = 0;
	int framesForReactivation_ = 0;

public:
	BoilerButtonLogic(bool inc_dec);
	~BoilerButtonLogic() {};
	
	virtual void init();
	virtual void update();
	virtual void onCollisionEnter(Collision* c);
	void assignBoiler(FireBallGenerator* fbGen) { fbGen_ = fbGen; }
};

