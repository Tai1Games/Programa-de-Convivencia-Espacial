#pragma once
#include "Component.h"
#include "ActionableWeapon.h"

class Collider;
class Viewer;
class ParticleEmitter;

class TomatoLogic : public ActionableWeapon
{
private:
	Collider* colTomato_ = nullptr;
	Viewer* tomatoViewer_ = nullptr;
	ParticleEmitter* particleEmitterTomato_ = nullptr;

	bool activated_ = false;
	bool exploded_ = false;
	int timeActivated_ = 0;
	int timeExploded_ = 0;
	int frame = 0;
	//Constants loaded in Init()

	int timeForExplosion_ = 0;
	int timeForExplosionExpire_ = 0;
	int nFramesCharge_ = 0;
	int nFramesExplosion_ = 0;
	int frameSpeedCharge_ = 0;
	int frameSpeedExplosion_ = 0;
	int frameSize_ = 0;
public:
	TomatoLogic() : ActionableWeapon(ComponentType::TomatoLogic, WeaponID::Tomato, 0, 0){};
	~TomatoLogic() {};

	virtual void init();
	virtual void update();
	virtual void action();
	virtual void onCollisionEnter(Collision* c);
};

