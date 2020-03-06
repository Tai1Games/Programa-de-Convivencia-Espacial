#include "Pickable.h"

void Pickable::init()
{
	mainCollider_ = GETCMP1_(Collider);
	//Fixture Sensor añadido por el componente
	mainCollider_->createFixture(50, 50, 10, 0, 0, 0, true);
}

void Pickable::update()
{

}

void Pickable::PickObjectBy(Collider* player)
{
	if (joint_ == nullptr) {
		b2WeldJointDef jointDef;
		jointDef.bodyA = player->getBody();
		jointDef.bodyB = mainCollider_->getBody();
		jointDef.collideConnected = false;
		jointDef.localAnchorA = b2Vec2(0, player->getH(0) / 2);
		joint_ = (b2WeldJoint*)mainCollider_->getWorld()->CreateJoint(&jointDef);
		picked_ = true;
	}
}

void Pickable::UnPickObject()
{
	if (joint_ != nullptr) {
		mainCollider_->getWorld()->DestroyJoint(joint_);
		picked_ = false;
	}
}
