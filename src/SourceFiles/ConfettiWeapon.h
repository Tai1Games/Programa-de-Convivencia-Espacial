#pragma once
#include "MeleeWeapon.h"

class Collider;
class ParticleEmitter;

class ConfettiWeapon : public MeleeWeapon
{
private:
	Collider* colWeapon_ = nullptr;
	ParticleEmitter* particleEmitter_ = nullptr;
	bool used = false;
public:
	ConfettiWeapon(WeaponID wId, int dmg, int impactDmg, int cooldownFrames) : MeleeWeapon(WeaponID::Slipper, dmg, impactDmg, cooldownFrames) {};
	~ConfettiWeapon() {};

	virtual void init() override;
	virtual void action() override;
};