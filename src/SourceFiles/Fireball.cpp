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
	if (to) {
		col_->createCircularFixture(CONST(double, "FIREBALL_RADIUS"), CONST(double, "FIREBALL_DENSITY"), CONST(double, "FIREBALL_FRICTION"), CONST(double, "FIREBALL_RESTITUTION"), Collider::CollisionLayer::NormalObject, false);
	}
	else if (col_->getNumFixtures() > 1) col_->destroyFixture(1);

}
