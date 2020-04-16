#include "BoilerButtonLogic.h"
#include "Collider.h"
#include "Collision.h"
#include "FireBallGenerator.h"


BoilerButtonLogic::BoilerButtonLogic(bool inc_dec) : Component(ComponentType::BoilerButton) {
	if (inc_dec) inc_dec_ = true;
	else inc_dec = false;
}

void BoilerButtonLogic::onCollisionEnter(Collision* c) {
	Entity* other = c->entity;

	if (c->hitFixture->GetFilterData().categoryBits == Collider::CollisionLayer::Player ||
		c->hitFixture->GetBody()->GetLinearVelocity().Length() > 35) {

		fbGen_->modifyGenerationRate(inc_dec_);
	}
}