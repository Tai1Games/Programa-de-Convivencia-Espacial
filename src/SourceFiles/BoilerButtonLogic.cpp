#include "BoilerButtonLogic.h"
#include "Collider.h"
#include "Collision.h"
#include "FireBallGenerator.h"
#include "AnimatedViewer.h"
#include "Resources.h"
#include "Constants.h"

BoilerButtonLogic::BoilerButtonLogic(bool inc_dec) :
	Component(ComponentType::BoilerButtonLogic),
	inc_dec_(inc_dec) {
}

void BoilerButtonLogic::init() {
	buttonViewer_ = entity_->getComponent<AnimatedViewer>(ComponentType::Viewer);
	buttonViewer_->setAnimSpeed(CONST(int, "BOILER_BUTTON_ANIMATION_SPEED"));
	framesForReactivation_ = CONST(int, "BOILER_BUTTON_COOLDOWN") * FRAMES_PER_SECOND;
	animationDuration_ = CONST(int, "BOILER_BUTTON_ANIMATION_SPEED") * buttonViewer_->getTexture()->getNumFramesX();
}

void BoilerButtonLogic::update() {
	if (activated) {
		currentFrame_++;
		if (currentFrame_ == animationEndedFrame_) {
			buttonViewer_->setFrame(2);
		}

		if (currentFrame_ == reactivationFrame_) {
			activated = false;
			buttonViewer_->setFrame(0);
		}
	}
}

void BoilerButtonLogic::onCollisionEnter(Collision* c) {
	Entity* other = c->entity;
	if (c->hitFixture->GetFilterData().categoryBits & Collider::CollisionLayer::Player ||
		c->hitFixture->GetBody()->GetLinearVelocity().Length() > minForceForAcivation_ && !activated) {

		fbGen_->onButtonAction(inc_dec_);
		buttonViewer_->startAnimation(0);
		reactivationFrame_ = currentFrame_ + framesForReactivation_;
		animationEndedFrame_ = currentFrame_ + animationDuration_;

		activated = true;
	}
}