#include "BananaWeapon.h"

void BananaWeapon::init()
{
	ActionableWeapon::init();
	pEmitterBanana_ = GETCMP1_(ParticleEmitter);
	colBanana_ = GETCMP1_(Collider);
	viewer_ = GETCMP1_(Viewer);
}

void BananaWeapon::action()
{	
	pEmitterBanana_->setPositionCollider(currentHand_->getColHands_());
	pEmitterBanana_->setDirection({ 0,.1 });
	pEmitterBanana_->PlayStop();

	//setActive(false);
	//entity_->setActive(false);
	//DISPARAR BALA Y DESACTIVAR ESTA ENTIDAD
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
