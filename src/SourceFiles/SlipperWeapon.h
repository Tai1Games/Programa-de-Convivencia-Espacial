#pragma once
#include "MeleeWeapon.h"
class SlipperWeapon :
	public MeleeWeapon
{
public:
	SlipperWeapon(WeaponID wId, int dmg, int impactDmg, int cooldownFrames);

	virtual void action() override;
};

