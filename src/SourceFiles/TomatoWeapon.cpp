#include "TomatoWeapon.h"
#include "Collider.h"
#include "Entity.h"
#include "Collision.h"
#include "Health.h"
#include "Wallet.h"
#include "PlayerData.h"
#include "AnimatedViewer.h"
#include "InputHandler.h"
#include "ParticleEmitter.h"
#include "Hands.h"
#include "CollisionHandler.h"
#include "ThrownByPlayer.h"

void TomatoWeapon::init() {
	ActionableWeapon::init();
	colTomato_ = GETCMP1_(Collider);
	tomatoViewer_ = GETCMP1_(AnimatedViewer);
	particleEmitterTomato_ = GETCMP1_(ParticleEmitter);

	timeForExplosion_ = CONST(int, "TOMATO_TIME_CHARGE");
	timeForExplosionExpire_ = CONST(int, "TOMATO_TIME_EXPLOSION");
	nFramesCharge_ = CONST(int, "TOMATO_N_FRAMES_ACTIVATED");
	nFramesExplosion_ = CONST(int, "TOMATO_N_FRAMES_EXPLOSION");
	damageOnExplosionImpact_ = CONST(int, "TOMATO_DAMAGE");
	explosionSize_ = CONST(int, "TOMATO_EXPLOSION_SIZE");
	explosionForce_ = CONST(int, "TOMATO_EXPLOSION_FORCE");

	timePerFrame_ = timeForExplosion_ / nFramesCharge_;
	timePerFrameUntilExplosion_ = timeForExplosionExpire_ / nFramesExplosion_;
}

void TomatoWeapon::update() {
	Weapon::update();
	if (currentHand_) mainCollider_->setTransform(currentHand_->getPointerPos(), 0.0);

	if (activated_) {

		if (SDL_Game::instance()->getTime() > timeForExplosion_) {
			colTomato_->createCircularFixture(explosionSize_, 0, 0, 0, Collider::CollisionLayer::NormalObject, true);
			timeForExplosionExpire_ = SDL_Game::instance()->getTime() + timeForExplosionExpire_;
			timeExploded_ = SDL_Game::instance()->getTime();
			exploded_ = true;
			activated_ = false;
			if (picked_) UnPickObject();
			colTomato_->setLinearVelocity({ 0,0 });
		}
		frame = (SDL_Game::instance()->getTime() - timeActivated_) / timePerFrame_;
		tomatoViewer_->setFrame(frame);
	}
	else if (exploded_) {
		if (SDL_Game::instance()->getTime() > timeForExplosionExpire_) {
			colTomato_->destroyFixture(1);
			setActive(false);
		}
		frame = nFramesCharge_ + (SDL_Game::instance()->getTime() - timeExploded_) / timePerFrameUntilExplosion_;
		tomatoViewer_->setFrame(frame);
	}
}

void TomatoWeapon::onCollisionEnter(Collision* c) {
	Weapon::onCollisionEnter(c);

	if (exploded_) {
		Entity* other = c->entity;

		Health* healthPlayer = GETCMP2(other, Health);
		Wallet* walletPlayer = GETCMP2(other, Wallet);
		PlayerData* playerData = GETCMP2(other, PlayerData);
		Collider* collPlayer = GETCMP2(other, Collider);

		ThrownByPlayer* objThrown = GETCMP1_(ThrownByPlayer);

		if (healthPlayer && collPlayer) {
			if (!healthPlayer->subtractLife(damageOnExplosionImpact_)) {

				// add points to owner
				if (objThrown->getOwnerId() != playerData->getPlayerNumber())
					objThrown->addPointsToOwner();

				healthPlayer->playerDead(c->collisionHandler);
			}
		}
		else if (walletPlayer && collPlayer) {
			c->collisionHandler->addCoinDrop(std::make_tuple(walletPlayer, playerData, 3));
		}

		b2Vec2 dir = (collPlayer->getPos() - colTomato_->getPos()).NormalizedVector();
		collPlayer->applyForce({ dir.x * explosionForce_, dir.y * explosionForce_ }, { 0,0 });
	}
}

void TomatoWeapon::action() {
	if (!activated_) {
		activated_ = true;
		timeForExplosion_ = SDL_Game::instance()->getTime() + timeForExplosion_;
		timeActivated_ = SDL_Game::instance()->getTime();
		particleEmitterTomato_->setPositionCollider(colTomato_);
		particleEmitterTomato_->setDirection({ 0, -1 });
		particleEmitterTomato_->PlayStop();
	}
}

void TomatoWeapon::PickObjectBy(Hands* playerHands)
{
	if (playerHands->getWeaponID() == NoWeapon) {
		currentHand_ = playerHands;
		picked_ = true;
		currentHand_->setWeapon(weaponType_, this);
		vw_->setDrawable(false);
		b2Filter pickUpCollider = mainCollider_->getFixture(0)->GetFilterData();
		pickUpCollider.categoryBits = 0;
		pickUpCollider.maskBits = 0;
		mainCollider_->getFixture(0)->SetFilterData(pickUpCollider);
	}
}

void TomatoWeapon::UnPickObject() {
	b2Filter pickUpCollider = mainCollider_->getFixture(0)->GetFilterData();
	pickUpCollider.categoryBits = Collider::CollisionLayer::NormalObject;
	pickUpCollider.maskBits = Collider::CollisionLayer::NormalObject | Collider::CollisionLayer::NormalAttachableObject | Collider::CollisionLayer::Player | Collider::CollisionLayer::Wall | Collider::CollisionLayer::NonGrababbleWall;
	mainCollider_->getFixture(0)->SetFilterData(pickUpCollider);

	ActionableWeapon::UnPickObject();
}

void TomatoWeapon::setActive(bool a, b2Vec2 pos) {
	entity_->setActive(a);
	GETCMP1_(Viewer)->setDrawable(a);
	colTomato_->getBody()->SetEnabled(a);
	if (a) colTomato_->getBody()->SetTransform(pos, 0);
	else {
		exploded_ = false;
		activated_ = false;
	}
}