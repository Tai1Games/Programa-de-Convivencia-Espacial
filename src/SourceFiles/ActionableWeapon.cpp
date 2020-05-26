#include "ActionableWeapon.h"
#include "Hands.h"
#include "InputBinder.h"

ActionableWeapon::ActionableWeapon(WeaponID wId, int impactDmg, int cooldownFrames, int impctForce) :
	ActionableWeapon(ComponentType::Weapon, wId, impactDmg, cooldownFrames, impctForce) {};

ActionableWeapon::ActionableWeapon(ComponentType::CmpId compType, WeaponID wId, int impactDmg, int cooldownFrames, int impctForce) :
	Weapon(compType, wId, impactDmg, impctForce),
	cooldownFrames_(cooldownFrames) {}

void ActionableWeapon::update() {
	Weapon::update();
	if (beenActivated_) {
		framesSinceActivation_++;
		if (framesSinceActivation_ >= cooldownFrames_) {
			framesSinceActivation_ = 0;
			beenActivated_ = false;
		}
	}
}

void ActionableWeapon::handleInput() {
	Weapon::handleInput();

	if (IsPicked() && playerInfo_[pickedIndex_].playerBinder->pressAttack())
		action();
}