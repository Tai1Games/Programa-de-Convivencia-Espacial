#include "CarnivorousPlant.h"

void CarnivorousPlant::init()
{
	frame_ = 0;
	viewer_ = entity_->getComponent<Viewer>(ComponentType::Viewer);
	idle_ = true;
	maxAnimationSpeed_ = CONST(int, "CARNIVOROUSEPLANT_MAX_SPEED");
	minAnimationSpeed_ = CONST(int, "CARNIVOROUSEPLANT_MIN_SPEED");
	idleFrames_ = CONST(int, "IDLE_FRAMES");
	eatingFrames_ = CONST(int, "EATING_FRAMES");
	frameSize_ = CONST(int, "FRAME_SIZE");
	coinDMG = CONST(int, "CARNIVOROUSEPLANT_COIN_DMG");
	damage = CONST(int, "CARNIVOROUSEPLANT_DMG");
	timePassed_ = 0;
	playersInside_ = 0;

	actualSpeed_ = minAnimationSpeed_;
	aumento_ = (float)(minAnimationSpeed_ - maxAnimationSpeed_) / (CONST(float, "CARNIVOROUSEPLANT_TIME") / 16.66);
	playerDetected_ = false;
}

void CarnivorousPlant::update()
{
	//sistema de animaicon
	if (idle_) {
		int pos = frameSize_ * (frame_ / (int)actualSpeed_);
		if (pos < frameSize_ * idleFrames_) {
			viewer_->setClip(SDL_Rect{ 0,pos,frameSize_,frameSize_ });
			frame_++;
		}
		else frame_ = 0;
	}
	else {
		int pos = frameSize_ * (frame_ / (int)actualSpeed_) + frameSize_ * idleFrames_;
		if (pos < frameSize_ * (eatingFrames_ + idleFrames_)) {
			viewer_->setClip(SDL_Rect{ 0,pos,frameSize_,frameSize_ });
			frame_++;
		}
		else {
			frame_ = 0;
			actualSpeed_ = minAnimationSpeed_;
			idle_ = true;
		}
	}

	if (playerDetected_) {
		if (SDL_Game::instance()->getTime() > limitTime_) { //tiene que morder xd
			idle_ = false;
			if (player_ != nullptr) {
				Health* healthPlayer = player_->getComponent<Health>(ComponentType::Health);
				if (healthPlayer != nullptr && !healthPlayer->subtractLife(damage)) healthPlayer->playerDead(playerCollHandler_);
				else if (walletPlayer_ != nullptr) playerCollHandler_->addCoinDrop(std::make_tuple(walletPlayer_, GETCMP2(player_, PlayerData), coinDMG));
			}
			resetCycle();
		}
		else if (idle_) {
			actualSpeed_ -= aumento_;
		}
	}
}



void CarnivorousPlant::onCollisionEnter(Collision* c)
{
	if (c->hitFixture->GetFilterData().categoryBits == Collider::CollisionLayer::Player) {


		if (playersInside_ == 0) {
			playerDetected_ = true;
			player_ = c->entity;
			playerCollHandler_ = c->collisionHandler;
			walletPlayer_ = GETCMP2(c->entity, Wallet);
			enterTime_ = SDL_Game::instance()->getTime();
			if (timePassed_ != 0)limitTime_ = SDL_Game::instance()->getTime() + CONST(float, "CARNIVOROUSEPLANT_TIME") - timePassed_;
			else resetCycle();
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
			timePassed_ += (SDL_Game::instance()->getTime() - enterTime_);
		}
	}
}

void CarnivorousPlant::resetCycle()
{
	enterTime_ = SDL_Game::instance()->getTime();
	limitTime_ = enterTime_ + CONST(int, "CARNIVOROUSEPLANT_TIME"); //aqui te mete un bocado
	timePassed_ = 0;
}
