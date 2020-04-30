#pragma once
#include "ActionableWeapon.h"
#include "Hands.h"

class BananaWeapon :public ActionableWeapon
{
public:
	BananaWeapon():ActionableWeapon(ComponentType::Banana,WeaponID::Mancuerna,0,0){} //provisional
	~BananaWeapon(){}

	virtual void action() override;
	virtual void setActive(bool a, b2Vec2 pos = { 0,0 });
};

