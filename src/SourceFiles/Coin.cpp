#include "Coin.h"

void Coin::init() {
	vw_ = GETCMP1_(Viewer);
	col_ = GETCMP1_(Collider);
}

void Coin::setActive(bool b, b2Vec2 pos, int value) {
	vw_->setDrawable(b);
	col_->getFixture(0)->GetBody()->SetEnabled(b);
	entity_->setActive(b);
	col_->getFixture(0)->GetBody()->SetTransform(pos, 0);
	value_ = value;
}
