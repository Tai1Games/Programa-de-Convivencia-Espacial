#pragma once
#include "Weapon.h"
class ParticleEmitter;

class ExtinguisherWeapon :
	public Weapon
{
protected:
	ParticleEmitter* emitter_ = nullptr;

	float impulse_;
	float PIXELS_PER_METER;
	int WINDOW_HEIGHT;
public:
	ExtinguisherWeapon(WeaponID wId) : Weapon(wId), impulse_(0.0), PIXELS_PER_METER(0) {}
	~ExtinguisherWeapon() {}

	virtual void init() override;
	virtual void update() override;
	virtual void Action() override;
};

