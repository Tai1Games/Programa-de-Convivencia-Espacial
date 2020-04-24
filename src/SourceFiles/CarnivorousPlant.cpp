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
	limitTime_ = CONST(int, "CARNIVOROUSEPLANT_TIME");
	actualSpeed_ = minAnimationSpeed_;
	timedPassed_ = 0;
	aumento_ = (float)(minAnimationSpeed_ - maxAnimationSpeed_) / (float)limitTime_;
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
			idle_ = true;
			timedPassed_ = 0;
			actualSpeed_ = minAnimationSpeed_;
		}
	}

	if (playerDetected_) {
		if (timedPassed_ >= limitTime_) { //tiene que morder xd
			idle_ = false;
			if (player_ != nullptr) {
				Health* healthPlayer = player_->getComponent<Health>(ComponentType::Health);

				//if (!healthPlayer->subtractLife(1)) healthPlayer->playerDead(playerCollision_);
			}
		}
		else {
			timedPassed_++;
			actualSpeed_ -= aumento_;
		}
	}

}

void CarnivorousPlant::onCollisionEnter(Collision* c)
{
	if (c->hitFixture->GetFilterData().categoryBits == Collider::CollisionLayer::Player) {
		playerDetected_ = true;
		player_ = c->entity;
		playerCollision_ = c;
	}

}

void CarnivorousPlant::onCollisionExit(Collision* c)
{
	if (c->hitFixture->GetFilterData().categoryBits == Collider::CollisionLayer::Player) {
		playerDetected_ = false;
		player_ = nullptr;
	}
}
