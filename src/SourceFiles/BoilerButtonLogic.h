#pragma once
#include "Component.h"

class FireBallGenerator;
class Collider;

class BoilerButtonLogic : public Component
{
private:
	FireBallGenerator* fbGen_ = nullptr;
	bool inc_dec_ = false;
public:
	BoilerButtonLogic(bool inc_dec);
	~BoilerButtonLogic() {};
	
	virtual void onCollisionEnter(Collision* c);
	void assignBoiler(FireBallGenerator* fbGen) { fbGen_ = fbGen; }
};

