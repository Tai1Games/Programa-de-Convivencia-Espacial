#pragma once
#include "ActionableWeapon.h"
#include "Hands.h"
#include "BulletPool.h"
#include "Resources.h"

class BananaWeapon :public ActionableWeapon
{
private:
	Collider* colBanana_ = nullptr;
	Viewer* viewer_ = nullptr;
	BulletPool* bulletPool_;
public:
	BananaWeapon(BulletPool* p, int damage, int impctForce) :ActionableWeapon( WeaponID::Banana, 0, 0, impctForce) {
		bulletPool_ = p;
		impactDamage_ = damage;		
	} //provisional
	~BananaWeapon(){}

	virtual void init();
	virtual void action() override;
	virtual void setActive(bool a, b2Vec2 pos = { 0,0 });
};

