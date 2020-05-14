#include "MeleeWeapon.h"
#include "Hands.h"
#include "Entity.h"
#include "Collision.h"
#include "CollisionHandler.h"
#include "ThrownByPlayer.h"

MeleeWeapon::MeleeWeapon(WeaponID wId, int dmg, int impactDmg, int cooldownFrames) : MeleeWeapon(ComponentType::MeleeWeapon, wId, dmg, impactDmg, cooldownFrames) {};

MeleeWeapon::MeleeWeapon(ComponentType::CmpId compType, WeaponID wId, int dmg, int impactDmg, int cooldownFrames) : ActionableWeapon(compType, wId, impactDmg, cooldownFrames), damage_(dmg) {}

void MeleeWeapon::action() {
	if (!beenActivated_) {
		std::cout << "ACCION ARMA MELEE ACTIVADA" << endl;
		mainCollider_->createRectangularFixture(mainCollider_->getW(0) * 4, mainCollider_->getH(0) * 4, 0, 0, 0, Collider::CollisionLayer::Trigger, true);
		beenActivated_ = true;
	}
	else
		std::cout << "COOLDING DOWN" << endl;
}

void MeleeWeapon::update() {
	ActionableWeapon::update();

	//>2 para no romper el rango del arma para pickup
	if (mainCollider_->getNumFixtures() > 2 && beenActivated_ && framesSinceActivation_>=3) {
		mainCollider_->destroyFixture(mainCollider_->getNumFixtures()-1);
	}

	if (currentHand_ != nullptr) {
		mainCollider_->setTransform(currentHand_->getPointerPos(), 0.0);
	}
}

void MeleeWeapon::PickObjectBy(int index) {
	Hands* playerHands = playerInfo_[index].playerHands;
	if (playerHands->getWeaponID() == NoWeapon) {
		currentHand_ = playerHands;
		picked_ = true;
		pickedIndex_ = index;
		currentHand_->setWeapon(weaponType_, this);
		vw_->setDrawable(false);
		//Desactivamos el trigger de pickUp

		mainCollider_->disableFixtureCollisions(0);
		mainCollider_->disableFixtureCollisions(1);
    
		ThrownByPlayer* throwData = GETCMP1_(ThrownByPlayer);
		throwData->SetOwner(index);
	}
}

void MeleeWeapon::onCollisionEnter(Collision* c) {
	ActionableWeapon::onCollisionEnter(c);

	if (picked_ && c->hitFixture->GetFilterData().categoryBits & Collider::CollisionLayer::Player && c->entity != currentHand_->getEntity()) {
		//Restar vida
		Health* auxHe = GETCMP2(c->entity, Health);
		Wallet* auxWa = GETCMP2(c->entity, Wallet);
		Collider* auxCo = GETCMP2(c->entity, Collider);
		PlayerData* pData = GETCMP2(c->entity, PlayerData);

		b2Vec2 knockback = auxCo->getPos() - mainCollider_->getPos();
		knockback.Normalize();
		knockback *= CONST(double, "WEAPON_MELEE_KNOCKBACK");

		auxCo->applyLinearImpulse(knockback, b2Vec2(0, 1));
		if (auxHe != nullptr) {
			if (!auxHe->subtractLife(damage_)) {
				ThrownByPlayer* objThrown = GETCMP1_(ThrownByPlayer);
				// player is killed by a weapon
				if (objThrown != nullptr && pData != nullptr) {
					if (objThrown->getOwnerId() != pData->getPlayerNumber())
						objThrown->addPointsToOwner();
				}
				auxHe->playerDead(c->collisionHandler);
			}
		}
		else
			c->collisionHandler->addCoinDrop(std::make_tuple(auxWa, GETCMP2(c->entity,PlayerData), damage_));
		std::cout << "Golpeado jugador" << endl;
	}
	
}

void MeleeWeapon::UnPickObject() {
	//Reactivamos el trigger de pickUp
	mainCollider_->getFixture(0)->SetFilterData(mainCollider_->getFilterFromLayer(Collider::CollisionLayer::NormalObject));
	mainCollider_->getFixture(1)->SetFilterData(mainCollider_->getFilterFromLayer(Collider::CollisionLayer::Trigger));

	ActionableWeapon::UnPickObject();
}