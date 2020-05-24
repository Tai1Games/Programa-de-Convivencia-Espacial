#include "ConfettiWeapon.h"
#include "Collider.h"
#include "ParticleEmitter.h"
#include "Hands.h"
#include "TimedDespawn.h"
#include "AnimatedViewer.h"
#include "Constants.h"

ConfettiWeapon::ConfettiWeapon(WeaponID wId, int dmg, int impactDmg, int cooldownFrames, int impctForce) : MeleeWeapon(wId, dmg, impactDmg, cooldownFrames, impctForce) {}

void ConfettiWeapon::init() {
	MeleeWeapon::init();
	colWeapon_ = GETCMP1_(Collider);
	particleEmitter_ = GETCMP1_(ParticleEmitter);
	viewer_ = entity_->getComponent<AnimatedViewer>(ComponentType::Viewer);
	timedDespawn_ = GETCMP1_(TimedDespawn);
	animationDuration_ = CONST(int, "CONFETTI_ANIMATION_DURATION") * FRAMES_PER_SECOND;
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
		currentHand_->setFrame(1, weaponType_);

		MeleeWeapon::action();
	}
}

void ConfettiWeapon::setActive(bool a, b2Vec2 pos)
{
	if (used) {
		if (currentHand_ != nullptr) UnPickObject();
		viewer_->setFrame(0);
		used = false;
		colWeapon_->setLinearVelocity(b2Vec2(0, 0));
		colWeapon_->setAngularVelocity(0);
		currentFrame_ = 0;
	}
	entity_->setActive(a);
	viewer_->setDrawable(a);
	colWeapon_->getBody()->SetEnabled(a);
	colWeapon_->getBody()->SetTransform(pos, 0);
}

void ConfettiWeapon::update()
{
	MeleeWeapon::update();
	if (used) {
		currentFrame_++;
		if (currentFrame_ == animationDuration_) {
			if (currentHand_ != nullptr) currentHand_->setFrame(2, weaponType_);
		}
	}
}

void ConfettiWeapon::PickObjectBy(int index)
{
	MeleeWeapon::PickObjectBy(index);
	if (currentHand_) {
		if (used) currentHand_->setFrame(2, weaponType_);
		else currentHand_->setFrame(0, weaponType_);
	}
}
