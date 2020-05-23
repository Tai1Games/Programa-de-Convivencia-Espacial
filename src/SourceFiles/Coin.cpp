#include "Coin.h"
#include "Collision.h"
#include "Wallet.h"
#include "CollisionHandler.h"

void Coin::init() {
	vw_ = GETCMP1_(Viewer);
	col_ = GETCMP1_(Collider);
	repickeableTime_ = CONST(int, "COINS_COOLDOWN_WHEN_DROPPED");
	sPerFrame_ = CONST(double, "SECONDS_PER_FRAME");
	winWidth_ = CONST(int, "WINDOW_WIDTH");
	winHeigth_ = CONST(int, "WINDOW_HEIGHT");
	pixelsPerMeter_ = CONST(double, "PIXELS_PER_METER");
}

void Coin::update()
{
	if (col_->getPos().x < 0 || col_->getPos().x > (winWidth_ / pixelsPerMeter_) || col_->getPos().y > (winHeigth_/pixelsPerMeter_) || col_->getPos().y < 0) setActive(false);

	if (justDroppedByPlayer_ != -1) {
		timeSinceDropped_ += sPerFrame_;
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

void Coin::onCollisionEnter(Collision* c)
{
	Wallet* wallet = GETCMP2(c->entity, Wallet);

	if (wallet != nullptr && justDroppedByPlayer_ != GETCMP2(c->entity,PlayerData)->getPlayerNumber()) {
		wallet->addCoins(value_);
		c->collisionHandler->addCoinPick(this);
		SDL_Game::instance()->getAudioMngr()->playChannel(Resources::CoinSound, 0);
	}
}
