#include "ActionableWeapon.h"
#include "Hands.h"
#include "InputHandler.h"

ActionableWeapon::ActionableWeapon(ComponentType::CmpId compType, WeaponID wId, int impactDmg, int cooldownFrames) : Weapon(compType, wId, impactDmg),
cooldownFrames_(cooldownFrames) {}

void ActionableWeapon::update() {
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

	if (IsPicked() && ih_->isButtonJustDown(currentHand_->getPlayerId(), SDL_CONTROLLER_BUTTON_X))
		action();
}