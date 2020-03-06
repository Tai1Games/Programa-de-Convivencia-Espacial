#include "Pickable.h"

void Pickable::init()
{
	mainCollider_ = GETCMP1_(Collider);
}

void Pickable::PickObjectBy(Collider* player)
{
	b2WeldJointDef jointDef;
	jointDef.bodyA = player->getBody();
	jointDef.bodyB = mainCollider_->getBody();
	jointDef.collideConnected = false;
	jointDef.localAnchorA = b2Vec2(0,player->getH()/2);
	joint_ = (b2WeldJoint*)mainCollider_->getWorld()->CreateJoint(&jointDef);
}

void Pickable::UnPickObject()
{
	if (joint_ != nullptr) mainCollider_->getWorld()->DestroyJoint(joint_);
}
