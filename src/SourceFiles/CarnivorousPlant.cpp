#include "CarnivorousPlant.h"

void CarnivorousPlant::init()
{
	viewer_ = entity_->getComponent<CarnivorousPlantViewer>(ComponentType::AdvancedAnimatedViewer);
	maxAnimationSpeed_ = CONST(int, "CARNIVOROUSPLANT_MAX_SPEED");
	minAnimationSpeed_ = CONST(int, "CARNIVOROUSPLANT_MIN_SPEED");
	coinDamage_ = CONST(int, "CARNIVOROUSPLANT_COIN_DMG");
	damage_ = CONST(int, "CARNIVOROUSPLANT_DMG");
	maxFrames_ = CONST(int, "CARNIVOROUSPLANT_TIME");
	marginUntilBite_ = CONST(int, "CARNIVOROUSPLANT_MARGIN_UNTIL_BITE");

	increase_ = (float)(minAnimationSpeed_ - maxAnimationSpeed_) / maxFrames_;
	actualSpeed_ = minAnimationSpeed_;

	viewer_->startAnimation(-1, 0, CONST(int, "CARNIVOROUSPLANT_NFRAMES_ANIM0"), 0);
}

void CarnivorousPlant::update()
{
	if (playerDetected_) {
		frameCount_++;
		if (viewer_->getCurrentAnim() != 1) {
			if (frameCount_ >= maxFrames_ - marginUntilBite_) {
				viewer_->startAnimation(0, 0, -1, 1);
				bite();
			}
			else {
				actualSpeed_ -= increase_;
				viewer_->setAnimSpeed(actualSpeed_);
			}
		}
	}
}

void CarnivorousPlant::bite()
{
	SDL_Game::instance()->getAudioMngr()->playChannel(Resources::AudioId::CarnivorousPlantSound, 0);
	Health* healthPlayer = player_->getComponent<Health>(ComponentType::Health);
	if (healthPlayer != nullptr && !healthPlayer->subtractLife(damage_)) healthPlayer->playerDead(playerCollHandler_);
	else if (walletPlayer_ != nullptr) playerCollHandler_->addCoinDrop(std::make_tuple(walletPlayer_, GETCMP2(player_, PlayerData), coinDamage_));
	frameCount_ = 0;
	actualSpeed_ = minAnimationSpeed_;
}

void CarnivorousPlant::onCollisionEnter(Collision* c)
{
	if (c->hitFixture->GetFilterData().categoryBits & Collider::CollisionLayer::Player) {
		player_ = c->entity;
		playerCollHandler_ = c->collisionHandler;
		walletPlayer_ = GETCMP2(c->entity, Wallet);
		if (playersInside_ == 0) {
			playerDetected_ = true;
		}
		playersInside_++;
	}
}

void CarnivorousPlant::onCollisionExit(Collision* c)
{
	if (c->hitFixture->GetFilterData().categoryBits & Collider::CollisionLayer::Player) {
		playersInside_--;

		if (playersInside_ == 0) {
			playerDetected_ = false;
			player_ = nullptr;
			playerCollHandler_ = nullptr;
			walletPlayer_ = nullptr;
		}
	}
}
