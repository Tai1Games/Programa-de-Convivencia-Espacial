#include "ConfettiWeapon.h"
#include "Collider.h"
#include "ParticleEmitter.h"
#include "Hands.h"
#include "TimedDespawn.h"

ConfettiWeapon::ConfettiWeapon(WeaponID wId, int dmg, int impactDmg, int cooldownFrames) : MeleeWeapon(ComponentType::ConfettiWeapon, wId, dmg, impactDmg, cooldownFrames) {}

void ConfettiWeapon::init() {
	MeleeWeapon::init();
	colWeapon_ = GETCMP1_(Collider);
	particleEmitter_ = GETCMP1_(ParticleEmitter);
	viewer_ = entity_->getComponent<AnimatedViewer>(ComponentType::Viewer);
	timedDespawn_ = GETCMP1_(TimedDespawn);
	frameSize_ = viewer_->getTexture()->getHeight();

	viewer_->stopAnimation();
	viewer_->setFrame(0);
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
		viewer_->setFrame(1);
		timedDespawn_->startTimer(this);
		MeleeWeapon::action();
	}
}

void ConfettiWeapon::setActive(bool a, b2Vec2 pos)
{
	if (used) {
		if (currentHand_ != nullptr) UnPickObject();
		viewer_->setFrame(0);
		used = false;
		cout << "tesst";
	}
	entity_->setActive(a);
	viewer_->setDrawable(a);
	colWeapon_->getBody()->SetEnabled(a);
	colWeapon_->getBody()->SetTransform(pos, 0);
}
