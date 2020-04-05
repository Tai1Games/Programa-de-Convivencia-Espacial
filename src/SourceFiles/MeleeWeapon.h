#pragma once
#include "Weapon.h"
#include "Hands.h"

class MeleeWeapon : public Weapon{
private:
	Collider* meleeCollider = nullptr;

public:
	MeleeWeapon(WeaponID wId) : Weapon(wId) {};
	virtual void update() override;

	virtual void Action();
};

