#include "BananaWeapon.h"

void BananaWeapon::init()
{
	ActionableWeapon::init();
	colBanana_ = GETCMP1_(Collider);
	viewer_ = GETCMP1_(Viewer);
}

void BananaWeapon::action()
{	
	setActive(false);
	entity_->setActive(false);
	b2Vec2 dir = currentHand_->getDir();
	dir *= CONST(double, "BANANA_BULLER_SPEED");
	   
	bulletPool_->addBullet(currentHand_->getPos(), { 0,0 }, {dir.x, -dir.y}, Resources::Negro, 0);

	currentHand_->setWeapon(NoWeapon, nullptr);
	picked_ = false;
	pickedIndex_ = -1;
	mainCollider_->getBody()->SetEnabled(true);
	vw_->setDrawable(true);
	currentHand_ = nullptr;
	
}

void BananaWeapon::setActive(bool a, b2Vec2 pos)
{
	entity_->setActive(a);
	viewer_->setDrawable(a);
	colBanana_->getBody()->SetEnabled(a);
	if (a) {
		colBanana_->getBody()->SetTransform(pos, 0);		
	}
}
