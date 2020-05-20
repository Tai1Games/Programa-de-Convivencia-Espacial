#include "Fireball.h"
#include "Viewer.h"
#include "Collider.h"
#include "Collision.h"
#include "CollisionHandler.h"
#include "Health.h"
#include "Wallet.h"


void Fireball::init()
{
	viewer_ = entity_->getComponent<AnimatedViewer>(ComponentType::Viewer);
	col_ = GETCMP1_(Collider);
	damage_ = CONST(int, "FIREBALL_DMG");
	coinDamage_ = CONST(int, "FIREBALL_COIN_DMG");
}

void Fireball::setActive(bool to, b2Vec2 pos, double angle)
{
	viewer_->setDrawable(to);
	col_->getFixture(0)->GetBody()->SetEnabled(to);
	entity_->setActive(to);
	col_->getFixture(0)->GetBody()->SetTransform(pos, angle);
	if (to) {
		col_->createCircularFixture(CONST(double, "FIREBALL_RADIUS_PHYSICS"), CONST(double, "FIREBALL_DENSITY"), CONST(double, "FIREBALL_FRICTION"), CONST(double, "FIREBALL_RESTITUTION"), Collider::CollisionLayer::NormalObject, true);
		viewer_->startAnimation();
	}
	else if (col_->getNumFixtures() > 1) col_->destroyFixture(1);
}

void Fireball::onCollisionEnter(Collision* c)
{
	Entity* other = c->entity;
	Health* health = GETCMP2(other, Health);
	Wallet* wallet = GETCMP2(other, Wallet);

	if (c->myFixture->IsSensor())
	{
		if (health != nullptr) {
			if (!health->subtractLife(damage_))
				health->playerDead(c->collisionHandler);
		}
		else if (wallet != nullptr) {
			c->collisionHandler->addCoinDrop(std::make_tuple(wallet, GETCMP2(c->entity, PlayerData), coinDamage_));
		}
	}

	c->collisionHandler->removeFireball(this);
}