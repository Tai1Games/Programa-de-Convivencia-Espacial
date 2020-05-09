#include "ConfettiWeapon.h"
#include "Collider.h"
#include "ParticleEmitter.h"
#include "Hands.h"

ConfettiWeapon:: ConfettiWeapon(WeaponID wId, int dmg, int impactDmg, int cooldownFrames) : MeleeWeapon(ComponentType::ConfettiWeapon, wId, dmg, impactDmg, cooldownFrames) {}

void ConfettiWeapon::init() {
	MeleeWeapon::init();
	colWeapon_ = GETCMP1_(Collider);
	particleEmitter_ = GETCMP1_(ParticleEmitter);
}

void ConfettiWeapon::action() {
	if (!used) {
		if (playerInfo_[currentHand_->getPlayerId()].playerHealth != nullptr) {
			damage_ = playerInfo_[currentHand_->getPlayerId()].playerHealth->getHealthMax() - playerInfo_[currentHand_->getPlayerId()].playerHealth->getHealth() + 1;
		}
		else damage_ = calculateCoinsDropped(playerInfo_[currentHand_->getPlayerId()].playerWallet->getCoins());
		particleEmitter_->setPositionCollider(colWeapon_);
		particleEmitter_->PlayStop();
		used = true;
		MeleeWeapon::action();
	}
}