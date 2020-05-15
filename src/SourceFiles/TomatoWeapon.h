#pragma once
#include "Component.h"
#include "ActionableWeapon.h"

class Collider;
class Viewer;
class ParticleEmitter;

class TomatoWeapon : public ActionableWeapon
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
	int explosionSize_ = 0;
	int nFramesExplosion_ = 0;
	int frameSpeedCharge_ = 0;
	int frameSpeedExplosion_ = 0;
	int frameSize_ = 0;
	int damageOnExplosionImpact_ = 0;
	int explosionForce_ = 0;
public:
	TomatoWeapon() : ActionableWeapon(WeaponID::Tomato, 0, 0){};
	~TomatoWeapon() {};

	virtual void init();
	virtual void update();
	virtual void action();
	virtual void PickObjectBy(Hands* playerHands);
	virtual void UnPickObject();
	virtual void onCollisionEnter(Collision* c);
	virtual void setActive(bool a, b2Vec2 pos = { 0,0 });
};

