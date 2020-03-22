#include "ImpulseViewer.h"
#include "PlayerController.h"
#include "Collider.h"
#include "InputHandler.h"

ImpulseViewer::ImpulseViewer(int player, int emptyTexId, int chargeTexId) : Component(ComponentType::ImpulseViewer),
	playerCollider_(nullptr),  playerController_(nullptr), 
	emptyTextureId_(emptyTexId), chargeTextureId_(chargeTexId), playerNumber_(player)
{}

void ImpulseViewer::init() {
	playerCollider_ = GETCMP1_(Collider);
	playerController_ = GETCMP1_(PlayerController);

	emptyTexture_ = SDL_Game::instance()->getTexturesMngr()->getTexture(emptyTextureId_);
	chargeTexture_ = SDL_Game::instance()->getTexturesMngr()->getTexture(chargeTextureId_);
}

void ImpulseViewer::draw() const {
	if (SDL_Game::instance()->getInputHandler()->isButtonDown(playerNumber_,SDL_CONTROLLER_BUTTON_A)) {
		SDL_Rect colRec = playerCollider_->getRectRender();
		playerController_->calculateForce();
	}
}