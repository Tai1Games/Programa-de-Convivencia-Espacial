#pragma once
#include "ActionableWeapon.h"
#include "BulletPool.h"
#include "Resources.h"

class StaplerWeapon : public ActionableWeapon
{
private:
	BulletPool* bulletPool_;
	int currentAmo;

public:
	StaplerWeapon(int damage, BulletPool* pb);
	~StaplerWeapon(){}

	virtual void init() override;
	virtual void action() override;
};

