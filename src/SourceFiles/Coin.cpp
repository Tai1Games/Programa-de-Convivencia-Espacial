#include "Coin.h"

void Coin::init() {
	vw_ = GETCMP1_(Viewer);
	col_ = GETCMP1_(Collider);
}

void Coin::update()
{
	if (justDroppedByPlayer_ != -1) {
		timeSinceDropped_ += CONST(double, "MS_PER_FRAME");
		if (timeSinceDropped_ >= CONST(int, "COINS_COOLDOWN_WHEN_DROPPED")) {
			justDroppedByPlayer_ = -1;
			timeSinceDropped_ = 0;
			col_->getFixture(0)->SetSensor(true);
			col_->setLinearVelocity(b2Vec2(0,0));
		}
	}
}

void Coin::setActive(bool b, int droppedByPlayerNum, b2Vec2 pos, int value) {
	vw_->setDrawable(b);
	col_->getFixture(0)->GetBody()->SetEnabled(b);
	entity_->setActive(b);
	col_->getFixture(0)->GetBody()->SetTransform(pos, 0);
	value_ = value;
	justDroppedByPlayer_ = droppedByPlayerNum;
}
