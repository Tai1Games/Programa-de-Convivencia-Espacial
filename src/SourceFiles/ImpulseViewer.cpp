#include "ImpulseViewer.h"
#include "PlayerController.h"
#include "Collider.h"
#include "InputHandler.h"
#include "PlayerData.h"

ImpulseViewer::ImpulseViewer(int emptyTexId, int chargeTexId) : Component(ComponentType::ImpulseViewer),
playerCollider_(nullptr), playerController_(nullptr),
emptyTextureId_(emptyTexId), chargeTextureId_(chargeTexId), playerNumber_(-1)
{}

void ImpulseViewer::init() {
	playerData_ = GETCMP1_(PlayerData);
	playerCollider_ = GETCMP1_(Collider);
	playerController_ = GETCMP1_(PlayerController);

	playerNumber_ = playerData_->getPlayerNumber();

	emptyTexture_ = SDL_Game::instance()->getTexturesMngr()->getTexture(emptyTextureId_);
	chargeTexture_ = SDL_Game::instance()->getTexturesMngr()->getTexture(chargeTextureId_);
}

void ImpulseViewer::draw() const {
	b2Vec2 stickDir = SDL_Game::instance()->getInputHandler()->getLastStickDir(playerNumber_, InputHandler::LEFTSTICK);
	if (SDL_Game::instance()->getInputHandler()->isButtonDown(playerNumber_, SDL_CONTROLLER_BUTTON_A)) {
		double angle = std::atan2((double)stickDir.x, -(double)stickDir.y) * (180.0 / PI);
		SDL_Rect playerRect = playerCollider_->getRectRender();
		SDL_Rect destRect{ playerRect.x,playerRect.y,IMPULSE_SIZE,IMPULSE_SIZE };
		emptyTexture_->render(destRect, angle);
		float force = playerController_->calculateForce();
		chargeTexture_->render(destRect, angle, { emptyTexture_->getWidth() * int((playerController_->calculateForce() / IMPULSE_GRABBED) * 11), 0, emptyTexture_->getWidth(), emptyTexture_->getHeight() });
	}
}