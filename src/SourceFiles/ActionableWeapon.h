#pragma once
#include "Weapon.h"
class ActionableWeapon :
	public Weapon
{
protected:
	//cooldown
	Uint16 framesSinceActivation_ = 0;
	int cooldownFrames_ = 0;
	bool beenActivated_ = false;
public:
	ActionableWeapon(WeaponID wId, int impactDmg, int cooldownFrames, int impctForce);
	ActionableWeapon(ComponentType::CmpId compType, WeaponID wId, int impactDmg, int cooldownFrames, int impctForce);
	virtual ~ActionableWeapon() {};

	virtual void update() override;
	virtual void handleInput() override;
	virtual void action() = 0;
};

