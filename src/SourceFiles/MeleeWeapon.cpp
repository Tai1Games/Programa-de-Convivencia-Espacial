#include "MeleeWeapon.h"
#include "Hands.h"
#include "Entity.h"
#include "Collision.h"

MeleeWeapon::MeleeWeapon(WeaponID wId, int dmg, int impactDmg, int cooldownFrames) : MeleeWeapon(ComponentType::MeleeWeapon, wId, dmg, impactDmg, cooldownFrames) {};

MeleeWeapon::MeleeWeapon(ComponentType::CmpId compType, WeaponID wId, int dmg, int impactDmg, int cooldownFrames) : ActionableWeapon(compType, wId, impactDmg, cooldownFrames), damage_(dmg) {}

void MeleeWeapon::action() {
	if (!beenActivated_) {
		cout << "ACCION ARMA MELEE ACTIVADA" << endl;
		mainCollider_->createRectangularFixture(mainCollider_->getW(0) * 4, mainCollider_->getH(0) * 4, 0, 0, 0, Collider::CollisionLayer::Trigger, true);
		beenActivated_ = true;
	}
	else
		cout << "COOLDING DOWN" << endl;
}

void MeleeWeapon::PickObjectBy(Hands* playerHands) {
	if (playerHands->getWeaponID() == NoWeapon) {
		currentHand_ = playerHands;
		picked_ = true;
		currentHand_->setWeapon(weaponType_, this);
		vw_->setDrawable(false);
		//Desactivamos el trigger de pickUp
		b2Filter pickUpCollider = mainCollider_->getFixture(0)->GetFilterData();
		pickUpCollider.categoryBits = 0;
		pickUpCollider.maskBits = 0;
		mainCollider_->getFixture(0)->SetFilterData(pickUpCollider);
	}
}

void MeleeWeapon::onCollisionEnter(Collision* c) {
	Weapon::onCollisionEnter(c);
	cout << "COLISION" << endl;
}

void MeleeWeapon::UnPickObject() {
	//Reactivamos el trigger de pickUp
	b2Filter pickUpCollider = mainCollider_->getFixture(0)->GetFilterData();
	pickUpCollider.categoryBits = Collider::CollisionLayer::PickableObject;
	pickUpCollider.maskBits = Collider::CollisionLayer::Player | Collider::CollisionLayer::Wall;
	mainCollider_->getFixture(0)->SetFilterData(pickUpCollider);

	Weapon::UnPickObject();
}