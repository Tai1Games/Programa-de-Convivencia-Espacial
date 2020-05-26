#pragma once
#include "Bullet.h"

class WiFiBullet : public Bullet
{
private:
	Collider* routerCollider_;

public:
	WiFiBullet(Collider* routerCollider) :
		Bullet(),
		routerCollider_(routerCollider)
	{};
	virtual ~WiFiBullet() {};

	virtual void onCollisionEnter(Collision* c) override;
	virtual void onCollisionExit(Collision* c) override;
};
