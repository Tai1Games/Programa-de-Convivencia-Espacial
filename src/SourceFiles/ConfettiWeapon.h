#pragma once
#include "MeleeWeapon.h"

class Collider;
class ParticleEmitter;
class TimedDespawn;
class AnimatedViewer;

class ConfettiWeapon : public MeleeWeapon
{
private:
	Collider* colWeapon_ = nullptr;
	ParticleEmitter* particleEmitter_ = nullptr;
	AnimatedViewer* viewer_ = nullptr;
	TimedDespawn* timedDespawn_ = nullptr;
	bool used = false;
	int frameSize_ = 0;
	
	int currentFrame_ = 0;
	int animationDuration_ = 0; //Loaded at init();
public:
	ConfettiWeapon(WeaponID wId, int dmg, int impactDmg, int cooldownFrames, int impctForce);
	virtual ~ConfettiWeapon() {};

	virtual void init() override;
	virtual void action() override;
	virtual void setActive(bool a, b2Vec2 pos = { 0,0 });
	virtual void update();
	virtual void PickObjectBy(int index) override;
};
