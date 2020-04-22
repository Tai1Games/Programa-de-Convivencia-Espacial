#include "TomatoLogic.h"
#include "Collider.h"
#include "Entity.h"
#include "Collision.h"
#include "Health.h"
#include "Wallet.h"
#include "PlayerData.h"
#include "Viewer.h"
#include "InputHandler.h"

void TomatoLogic::init() {
	colTomato_ = GETCMP1_(Collider);
	tomatoViewer_ = GETCMP1_(Viewer);

	timeForExplosion_ = CONST(int, "TOMATO_TIME_CHARGE");
	timeForExplosionExpire_ = CONST(int, "TOMATO_TIME_EXPLOSION");
	nFramesCharge_ = CONST(int, "TOMATO_N_FRAMES_ACTIVATED");
	nFramesExplosion_ = CONST(int, "TOMATO_N_FRAMES_EXPLOSION");
	frameSize_ = tomatoViewer_->getTexture()->getHeight();

	frameSpeedCharge_ = timeForExplosion_ / nFramesCharge_;
	frameSpeedExplosion_ = timeForExplosionExpire_ / nFramesExplosion_;
}

void TomatoLogic::update() {
	if (!STOPYAJODER_) {
		if (activated_) {
			if (SDL_Game::instance()->getTime() > timeForExplosion_) {
				colTomato_->createCircularFixture(3, 0, 0, 0, Collider::CollisionLayer::Trigger, true);
				timeForExplosionExpire_ = SDL_Game::instance()->getTime() + timeForExplosionExpire_;
				timeExploded_ = SDL_Game::instance()->getTime();
				exploded_ = true;
				activated_ = false;
			}
			frame = 1 + (SDL_Game::instance()->getTime() - timeActivated_) / frameSpeedCharge_;
			tomatoViewer_->setClip(SDL_Rect{ frame * frameSize_, 0, frameSize_, frameSize_ });
		}
		else if (exploded_) {
			if (SDL_Game::instance()->getTime() > timeForExplosionExpire_) {
				colTomato_->destroyFixture(1);
				STOPYAJODER_ = true;
			}
			frame = 1 + nFramesCharge_ + (SDL_Game::instance()->getTime() - timeExploded_) / frameSpeedExplosion_;
			tomatoViewer_->setClip(SDL_Rect{ frame * frameSize_, 0, frameSize_, frameSize_ });
		}
	}
}

void TomatoLogic::onCollisionEnter(Collision* c) {
	if (activated_) {
		Entity* other = c->entity;

		Health* healthPlayer = GETCMP2(other, Health);
		Wallet* walletPlayer = GETCMP2(other, Wallet);
		PlayerData* playerData = GETCMP2(other, PlayerData);
		Collider* collPlayer = GETCMP2(other, Collider);

		bool hitPlayer = false;

		if (healthPlayer && collPlayer) {
			healthPlayer->subtractLife(1);
			hitPlayer = true;
		}
		else if (walletPlayer && collPlayer) {
			walletPlayer->dropCoins(1, playerData->getPlayerNumber());
			hitPlayer = true;
		}

		if (hitPlayer) {
			b2Vec2 dir = collPlayer->getPos() - colTomato_->getPos();
			float length = dir.Length();
			cout << "AAAA" << endl;
			float invLength = 1.0f / length;
			dir.x *= invLength;
			dir.y *= invLength;

			collPlayer->applyForce({ dir.x * 10000, dir.y * 10000 }, { 0,0 });
		}
	}	
}

void TomatoLogic::handleInput() {
	InputHandler* ih = SDL_Game::instance()->getInputHandler();
	//Empieza la carga
	if (ih->isButtonJustDown(0, SDL_CONTROLLER_BUTTON_B)) {
		activated_ = true;
		timeForExplosion_ = SDL_Game::instance()->getTime() + timeForExplosion_;
		timeActivated_ = SDL_Game::instance()->getTime();
	}
}