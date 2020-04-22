#include "SlipperWeapon.h"
#include "Hands.h"

SlipperWeapon::SlipperWeapon(WeaponID wId, int dmg, int impactDmg, int cooldownFrames) : MeleeWeapon(ComponentType::SlipperWeapon, wId, dmg, impactDmg, cooldownFrames) {};

void SlipperWeapon::action() {
	if (playerInfo_[currentHand_->getPlayerId()].playerHealth != nullptr) {
		damage_ = playerInfo_[currentHand_->getPlayerId()].playerHealth->getHealthMax() - playerInfo_[currentHand_->getPlayerId()].playerHealth->getHealth() + 1;
	}
	else damage_ = calculateCoinsDropped(playerInfo_[currentHand_->getPlayerId()].playerWallet->getCoins());
	
	MeleeWeapon::action();
}
