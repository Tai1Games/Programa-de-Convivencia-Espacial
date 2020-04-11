#include "Fireball.h"
#include "Viewer.h"
#include "Collider.h"

void Fireball::init()
{
	vw_ = GETCMP1_(Viewer);
	col_ = GETCMP1_(Collider);
}

void Fireball::setActive(bool to,b2Vec2 pos)
{
	vw_->setDrawable(to);
	col_->getFixture(0)->GetBody()->SetEnabled(to);
	entity_->setActive(to);
	col_->getFixture(0)->GetBody()->SetTransform(pos, 0);
	//if (to) {
	//	col_->createCircularFixture(CONST(double, "COIN_BASE_SIZE"), CONST(double, "COIN_DENSITY"), CONST(double, "COIN_FRICTION"), CONST(double, "COIN_RESTITUTION"), Collider::CollisionLayer::Trigger, true);
	//}
	//else if (col_->getNumFixtures() > 1) col_->destroyFixture(1);

}
