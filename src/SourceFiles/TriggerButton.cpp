#include "TriggerButton.h"

void TriggerButton::init()
{
	//viewer_ = entity_->getComponent<CarnivorousPlantViewer>(ComponentType::AdvancedAnimatedViewer);

	
	

	//viewer_->startAnimation(-1, 0, idleFrames_, 0);
}

void TriggerButton::update()
{
	if (playerDetected_) {
		
	}
}

void TriggerButton::PassState()
{
	
}

void TriggerButton::onCollisionEnter(Collision* c)
{
	if (c->hitFixture->GetFilterData().categoryBits & Collider::CollisionLayer::Player) {
		player_ = c->entity;
		playerCollHandler_ = c->collisionHandler;
		if (playersInside_ == 0) {
			playerDetected_ = true;
		}
		playersInside_++;
	}
}

void TriggerButton::onCollisionExit(Collision* c)
{
	if (c->hitFixture->GetFilterData().categoryBits & Collider::CollisionLayer::Player) {
		playersInside_--;

		if (playersInside_ == 0) {
			playerDetected_ = false;
			player_ = nullptr;
			playerCollHandler_ = nullptr;
		}
	}
}