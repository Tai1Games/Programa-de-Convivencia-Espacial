#include "CarnivorousPlant.h"

void CarnivorousPlant::init()
{
	frame_ = 0;
	viewer_ = entity_->getComponent<Viewer>(ComponentType::Viewer);
	idle_ = true;
	maxAnimationSpeed_ = CONST(int, "CARNIVOROUSPLANT_MAX_SPEED");
	minAnimationSpeed_ = CONST(int, "CARNIVOROUSPLANT_MIN_SPEED");
	idleFrames_ = CONST(int, "IDLE_FRAMES");
	eatingFrames_ = CONST(int, "EATING_FRAMES");
	frameSize_ = CONST(int, "FRAME_SIZE");
	coinDMG = CONST(int, "CARNIVOROUSPLANT_COIN_DMG");
	damage = CONST(int, "CARNIVOROUSPLANT_DMG");
	maxFrames_ = CONST(int, "CARNIVOROUSPLANT_TIME");
	playersInside_ = 0;
	frameCount_ = 0;

	increase_ = (float)(minAnimationSpeed_ - maxAnimationSpeed_) / maxFrames_;
	actualSpeed_ = minAnimationSpeed_;
	playerDetected_ = false;
}

void CarnivorousPlant::update()
{
	//sistema de animacion
	if (idle_) {
		int pos = frameSize_ * (frame_ / (int)actualSpeed_);
		if (pos < frameSize_ * idleFrames_) {
			viewer_->setFrame(pos);
			frame_++;
		}
		else frame_ = 0;
	}
	else {
		int pos = frame_ / (int)actualSpeed_ + idleFrames_;
		if (pos < eatingFrames_ + idleFrames_) {
			viewer_->setFrame(pos);
			frame_++;
		}
		else {
			frame_ = 0;
			actualSpeed_ = minAnimationSpeed_;
			idle_ = true;
		}
	}

	if (playerDetected_) {
		frameCount_++;
		if (frameCount_ < maxFrames_) { //tiene que morder xd
			actualSpeed_ -= increase_;
		}
		else {
			idle_ = false;
			Health* healthPlayer = player_->getComponent<Health>(ComponentType::Health);
			if (healthPlayer != nullptr && !healthPlayer->subtractLife(damage)) healthPlayer->playerDead(playerCollHandler_);
			else if (walletPlayer_ != nullptr) playerCollHandler_->addCoinDrop(std::make_tuple(walletPlayer_, GETCMP2(player_, PlayerData), coinDMG));
			frameCount_ = 0;
		}
	}
}



void CarnivorousPlant::onCollisionEnter(Collision* c)
{
	if (c->hitFixture->GetFilterData().categoryBits == Collider::CollisionLayer::Player) {
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
	if (c->hitFixture->GetFilterData().categoryBits == Collider::CollisionLayer::Player) {
		playersInside_--;

		if (playersInside_ == 0) {
			playerDetected_ = false;
			player_ = nullptr;
			playerCollHandler_ = nullptr;
			walletPlayer_ = nullptr;
		}
	}
}
