#include "Coin.h"

void Coin::init() {
	vw_ = GETCMP1_(Viewer);
	col_ = GETCMP1_(Collider);
	repickeableTime_ = CONST(int, "COINS_COOLDOWN_WHEN_DROPPED");
	msPerFrame_ = CONST(double, "MS_PER_FRAME");
}

void Coin::update()
{
	if (justDroppedByPlayer_ != -1) {
		timeSinceDropped_ += msPerFrame_;
		if (timeSinceDropped_ >= repickeableTime_) {
			justDroppedByPlayer_ = -1;
			timeSinceDropped_ = 0;
			col_->setLinearVelocity(b2Vec2(0,0));
			col_->destroyFixture(1);
		}
	}
}

void Coin::setActive(bool b, int droppedByPlayerNum, b2Vec2 pos, int value) {
	vw_->setDrawable(b);
	col_->getFixture(0)->GetBody()->SetEnabled(b);
	entity_->setActive(b);
	col_->getFixture(0)->GetBody()->SetTransform(pos, 0);
	if (b) col_->createCircularFixture(CONST(double, "COIN_BASE_SIZE"), CONST(double, "COIN_DENSITY"), CONST(double, "COIN_FRICTION"), CONST(double, "COIN_RESTITUTION"), Collider::CollisionLayer::UnInteractableObject, false);
	else if (col_->getNumFixtures() > 1) col_->destroyFixture(1);
	value_ = value;
	justDroppedByPlayer_ = droppedByPlayerNum;
}
