#include "ConfettiWeapon.h"
#include "Collider.h"
#include "ParticleEmitter.h"
#include "Hands.h"

ConfettiWeapon:: ConfettiWeapon(WeaponID wId, int dmg, int impactDmg, int cooldownFrames, int impctForce) :
	MeleeWeapon( wId, dmg, impactDmg, cooldownFrames, impctForce) {}

void ConfettiWeapon::init() {
	MeleeWeapon::init();
	colWeapon_ = GETCMP1_(Collider);
	particleEmitter_ = GETCMP1_(ParticleEmitter);
	viewer_ = entity_->getComponent<AnimatedViewer>(ComponentType::Viewer);
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
		MeleeWeapon::action();
	}
}

void ConfettiWeapon::setActive(bool a, b2Vec2 pos)
{
	entity_->setActive(a);
	viewer_->setDrawable(a);
	colWeapon_->getBody()->SetEnabled(a);
	colWeapon_->getBody()->SetTransform(pos, 0);
	if (used) {
		viewer_->setFrame(0);
		used = false;
	}
}
