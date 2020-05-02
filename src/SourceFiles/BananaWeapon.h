#pragma once
#include "ActionableWeapon.h"
#include "Hands.h"
#include "BulletPool.h"
#include "Resources.h"

class BananaWeapon :public ActionableWeapon
{
private:
	Collider* colBanana_ = nullptr;
	Viewer* viewer_;
	BulletPool* bulletPool_;
public:
	BananaWeapon(BulletPool* p) :ActionableWeapon(ComponentType::Banana, WeaponID::Mancuerna, 0, 0) {
		bulletPool_ = p;
	} //provisional
	~BananaWeapon(){}

	virtual void init();
	virtual void action() override;
	virtual void setActive(bool a, b2Vec2 pos = { 0,0 });
};

