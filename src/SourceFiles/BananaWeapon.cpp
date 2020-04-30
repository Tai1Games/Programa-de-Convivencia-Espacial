#include "BananaWeapon.h"

void BananaWeapon::init()
{
	ActionableWeapon::init();
	pEmitterBanana_ = GETCMP1_(ParticleEmitter);
	colBanana_ = GETCMP1_(Collider);
}

void BananaWeapon::action()
{	
	pEmitterBanana_->setPositionCollider(currentHand_->getColHands_());
	pEmitterBanana_->setDirection({ 0,.1 });
	pEmitterBanana_->PlayStop();
}

void BananaWeapon::setActive(bool a, b2Vec2 pos)
{
	entity_->setActive(a);
	GETCMP1_(Viewer)->setDrawable(a);
	colBanana_->getBody()->SetEnabled(a);
	if (a) {
		colBanana_->getBody()->SetTransform(pos, 0);
	}
}
