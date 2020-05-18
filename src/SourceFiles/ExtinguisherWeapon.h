#pragma once
#include "ActionableWeapon.h"
class ParticleEmitter;

class ExtinguisherWeapon :
	public ActionableWeapon
{
protected:
	ParticleEmitter* emitter_;

	float impulse_;
	float PIXELS_PER_METER;
	int WINDOW_HEIGHT;
public:
	ExtinguisherWeapon(WeaponID wId, int impctDmg, int cooldownFrames, int impctForce);
	~ExtinguisherWeapon() {}

	virtual void init() override;
	virtual void action() override;

	virtual void UnPickObject();
};

