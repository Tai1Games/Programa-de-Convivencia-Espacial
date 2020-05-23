#pragma once
#include "Component.h"
#include "ActionableWeapon.h"

class Collider;
class AnimatedViewer;
class ParticleEmitter;

class TomatoWeapon : public ActionableWeapon
{
private:
	Collider* colTomato_ = nullptr;
	AnimatedViewer* tomatoViewer_ = nullptr;
	ParticleEmitter* particleEmitterTomato_ = nullptr;

	bool activated_ = false;
	bool exploded_ = false;
	int currentFrame_ = 0;

	//Constants loaded in Init()
	int framesCharge_ = 0;
	int framesExplosion_ = 0;
	int nFramesCharge_ = 0;
	int explosionSize_ = 0;
	int nFramesExplosion_ = 0;
	int timePerFrameCharge_ = 0;
	int timePerFrameExplosion_ = 0;
	int damageOnExplosionImpact_ = 0;
	int explosionForce_ = 0;
public:
	TomatoWeapon() : ActionableWeapon(WeaponID::Tomato, 0, 0, CONST(double, "TOMATO_IMPACT_FORCE")){};
	~TomatoWeapon() {};

	virtual void init();
	virtual void update();
	virtual void action();
	virtual void PickObjectBy(Hands* playerHands);
	virtual void UnPickObject();
	virtual void onCollisionEnter(Collision* c);
	virtual void setActive(bool a, b2Vec2 pos = { 0,0 });
};

