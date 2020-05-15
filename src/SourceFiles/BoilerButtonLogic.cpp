#include "BoilerButtonLogic.h"
#include "Collider.h"
#include "Collision.h"
#include "FireBallGenerator.h"
#include "AnimatedViewer.h"
#include "Resources.h"

BoilerButtonLogic::BoilerButtonLogic(bool inc_dec) : Component(ComponentType::BoilerButtonLogic) {
	if (inc_dec) inc_dec_ = true;
	else inc_dec = false;
}

void BoilerButtonLogic::init() {
	buttonViewer_ = entity_->getComponent<AnimatedViewer>(ComponentType::Viewer);
	reactivationCd_ = CONST(int, "BOILER_BUTTON_COOLDOWN");
	minForceForAcivation_ = CONST(int, "BOILER_MIN_FORCE_FOR_ACTIVATION");
}

void BoilerButtonLogic::update() {
	if (!activated) {
		if (SDL_Game::instance()->getTime() > timeForReactivation_) {
			activated = true;
			buttonViewer_->setFrame(0);
		}
	}
}

void BoilerButtonLogic::onCollisionEnter(Collision* c) {
	Entity* other = c->entity;
	if (c->hitFixture->GetFilterData().categoryBits == Collider::CollisionLayer::Player ||
		c->hitFixture->GetBody()->GetLinearVelocity().Length() > minForceForAcivation_) {

		fbGen_->onButtonAction(inc_dec_);
		buttonViewer_->setFrame(1);
		timeForReactivation_ = SDL_Game::instance()->getTime() + reactivationCd_;
		activated = false;
	}
}