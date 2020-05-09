#include "BoilerButtonLogic.h"
#include "Collider.h"
#include "Collision.h"
#include "FireBallGenerator.h"
#include "Viewer.h"
#include "Resources.h"

BoilerButtonLogic::BoilerButtonLogic(bool inc_dec) : Component(ComponentType::BoilerButtonLogic) {
	if (inc_dec) inc_dec_ = true;
	else inc_dec = false;
}

void BoilerButtonLogic::init() {
	buttonViewer_ = GETCMP1_(Viewer);
	reactivationCd_ = CONST(int, "BOILER_BUTTON_COOLDOWN");
	frameSize = buttonViewer_->getTexture()->getHeight();
	minForceForAcivation_ = CONST(int, "BOILER_MIN_FORCE_FOR_ACTIVATION");
}

void BoilerButtonLogic::update() {
	if (!activated) {
		if (SDL_Game::instance()->getTime() > timeForReactivation_) {
			activated = true;
			buttonViewer_->setClip(SDL_Rect{ 0, 0, frameSize, frameSize });
		}
	}
}

void BoilerButtonLogic::onCollisionEnter(Collision* c) {
	Entity* other = c->entity;
	if (c->hitFixture->GetFilterData().categoryBits == Collider::CollisionLayer::Player ||
		c->hitFixture->GetBody()->GetLinearVelocity().Length() > minForceForAcivation_) {

		fbGen_->onButtonAction(inc_dec_);
		buttonViewer_->setClip(SDL_Rect{ frameSize, 0, frameSize, frameSize });
		timeForReactivation_ = SDL_Game::instance()->getTime() + reactivationCd_;
		activated = false;
	}
}