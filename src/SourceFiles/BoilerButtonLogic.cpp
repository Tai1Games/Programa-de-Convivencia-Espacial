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
	buttonViewer_->setAnimSpeed(30);
	reactivationCd_ = CONST(int, "BOILER_BUTTON_COOLDOWN");
	framesForReactivation_ = CONST(int, "BOILER_MIN_FORCE_FOR_ACTIVATION") * FRAMES_PER_SECOND;
}

void BoilerButtonLogic::update() {
	if (activated) {
		currentFrame_++;
		if (currentFrame_ >= reactivationFrame_) {
			activated = false;
			//buttonViewer_->setFrame(2);
		}
	}
}

void BoilerButtonLogic::onCollisionEnter(Collision* c) {
	Entity* other = c->entity;
	if (c->hitFixture->GetFilterData().categoryBits & Collider::CollisionLayer::Player ||
		c->hitFixture->GetBody()->GetLinearVelocity().Length() > minForceForAcivation_ && !activated) {

		fbGen_->onButtonAction(inc_dec_);
		buttonViewer_->startAnimation(1, 0, 3);
		reactivationFrame_ = currentFrame_ + framesForReactivation_;
		activated = true;
	}
}