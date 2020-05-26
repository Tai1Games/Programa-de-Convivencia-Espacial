#pragma once
#include "ActionableWeapon.h"
#include "BulletPool.h"
#include "Resources.h"

class Viewer;
class Collider;
class TimedDespawn;

class StaplerWeapon : public ActionableWeapon
{
private:
	BulletPool* bulletPool_;
	Viewer* viewer_ = nullptr;
	Collider* collider_ = nullptr;
	TimedDespawn* timedDespawn_ = nullptr;
	int maxAmmo;
	int currentAmmo;

public:
	StaplerWeapon(int damage, BulletPool* pb, int impctForce);
	~StaplerWeapon() {}

	virtual void init() override;
	virtual void action() override;
	virtual void setActive(bool a, b2Vec2 pos = { 0,0 });
};
