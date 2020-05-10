#include "ConfettiWeapon.h"
#include "Collider.h"
#include "ParticleEmitter.h"
#include "Hands.h"

ConfettiWeapon:: ConfettiWeapon(WeaponID wId, int dmg, int impactDmg, int cooldownFrames) : MeleeWeapon(ComponentType::ConfettiWeapon, wId, dmg, impactDmg, cooldownFrames) {}

void ConfettiWeapon::init() {
	MeleeWeapon::init();
	colWeapon_ = GETCMP1_(Collider);
	particleEmitter_ = GETCMP1_(ParticleEmitter);
	particleEmitter_->setOffset({ 10, 15 });
}

void ConfettiWeapon::action() {
	if (!used) {
		if (playerInfo_[currentHand_->getPlayerId()].playerHealth != nullptr) {
			damage_ = playerInfo_[currentHand_->getPlayerId()].playerHealth->getHealthMax() - playerInfo_[currentHand_->getPlayerId()].playerHealth->getHealth() + 1;
		}
		else damage_ = calculateCoinsDropped(playerInfo_[currentHand_->getPlayerId()].playerWallet->getCoins());
		b2Vec2 handDirection = currentHand_->getDir();
		particleEmitter_->setPositionCollider(colWeapon_);
		particleEmitter_->setDirection({ handDirection.x, handDirection.y });
		particleEmitter_->PlayStop();
		used = true;
		MeleeWeapon::action();
	}
}