#include "ImpulseViewer.h"
#include "PlayerController.h"
#include "Collider.h"
#include "InputHandler.h"
#include "PlayerData.h"

ImpulseViewer::ImpulseViewer(int emptyTexId, int chargeTexId) :
	AnimatedViewer(chargeTextureId_, 0, ComponentType::ImpulseViewer),
	playerCollider_(nullptr), playerController_(nullptr),
	emptyTextureId_(emptyTexId), chargeTextureId_(chargeTexId),
	maxImpulseGrabbed_(0), impulseSize_(0) {
}

void ImpulseViewer::init() {
	playerData_ = GETCMP1_(PlayerData);
	playerCollider_ = GETCMP1_(Collider);
	playerController_ = GETCMP1_(PlayerController);

	emptyTexture_ = SDL_Game::instance()->getTexturesMngr()->getTexture(emptyTextureId_);
	chargeTexture_ = SDL_Game::instance()->getTexturesMngr()->getTexture(chargeTextureId_);

	maxImpulseGrabbed_ = CONST(float, "IMPULSE_GRABBED");
	numFramesCharge_ = chargeTexture_->getNumFramesX();

	impulseSize_ = CONST(int, "IMPULSE_SIZE");

	ib_ = playerData_->getBinder();

	pauseAnimation();
}

void ImpulseViewer::update()
{
	b2Vec2 stickDir = ib_->getAimDir();
	angle_ = std::atan2((double)stickDir.x, -(double)stickDir.y) * (180.0 / PI);
	frameX_ = (playerController_->getImpulseForce() / maxImpulseGrabbed_) * (numFramesCharge_ - 1);
}

void ImpulseViewer::draw() const {
	if (playerController_->isChargingImpulse()) {
		SDL_Rect playerRect = playerCollider_->getRectRender();
		SDL_Rect destRect{ playerRect.x,playerRect.y,impulseSize_,impulseSize_ };
		emptyTexture_->render(destRect, angle_);
		chargeTexture_->render(destRect, angle_, frameX_);
	}
}