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
	bulletPool_->addBullet({ 5,5 }, { 0,0 }, { 1,1 }, Resources::Negro, 0);
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
