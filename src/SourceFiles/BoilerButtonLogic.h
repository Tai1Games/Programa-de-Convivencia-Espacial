#pragma once
#include "Component.h"

class FireBallGenerator;
class Collider;
class Viewer;

class BoilerButtonLogic : public Component
{
private:
	FireBallGenerator* fbGen_ = nullptr;
	Viewer* buttonViewer_ = nullptr;

	bool inc_dec_ = false;
	bool activated = true;
	int timeForReactivation_ = 0;

	//Initialized at init()
	int reactivationCd_ = 0; 
	int frameSize = 0;
	int minForceForAcivation_ = 0;

public:
	BoilerButtonLogic(bool inc_dec);
	~BoilerButtonLogic() {};
	
	virtual void init();
	virtual void update();
	virtual void onCollisionEnter(Collision* c);
	void assignBoiler(FireBallGenerator* fbGen) { fbGen_ = fbGen; }
};

