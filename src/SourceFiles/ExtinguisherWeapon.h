#pragma once
#include "Weapon.h"
class ParticleEmitter;

class ExtinguisherWeapon :
	public Weapon
{
protected:
	uint16 framesSinceActivation_;
	bool activated;

	ParticleEmitter* emitter_;

	float impulse_;
	int cooldown_;
	float PIXELS_PER_METER;
	int WINDOW_HEIGHT;
public:
	ExtinguisherWeapon(WeaponID wId);
	~ExtinguisherWeapon() {}

	virtual void init() override;
	virtual void update() override;
	virtual void Action() override;

	virtual void UnPickObject();
};

