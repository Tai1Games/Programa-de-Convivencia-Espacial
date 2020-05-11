#include "ConfettiWeapon.h"
#include "Collider.h"
#include "ParticleEmitter.h"
#include "Hands.h"

ConfettiWeapon:: ConfettiWeapon(WeaponID wId, int dmg, int impactDmg, int cooldownFrames) : MeleeWeapon(ComponentType::ConfettiWeapon, wId, dmg, impactDmg, cooldownFrames) {}

void ConfettiWeapon::init() {
	MeleeWeapon::init();
	colWeapon_ = GETCMP1_(Collider);
	particleEmitter_ = GETCMP1_(ParticleEmitter);
	viewer_ = GETCMP1_(Viewer);
	frameSize_ = viewer_->getTexture()->getHeight();

	viewer_->setClip(SDL_Rect{ 0, 0, frameSize_, frameSize_ });
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
		viewer_->setClip(SDL_Rect{ frameSize_, 0, frameSize_, frameSize_ });
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
		viewer_->setClip(SDL_Rect{ 0, 0, frameSize_, frameSize_ });
		used = false;
	}
}
