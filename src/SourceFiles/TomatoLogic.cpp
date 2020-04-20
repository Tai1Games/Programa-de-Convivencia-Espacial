#include "TomatoLogic.h"
#include "Collider.h"
#include "Entity.h"
#include "Collision.h"
#include "Health.h"
#include "Wallet.h"
#include "PlayerData.h"

void TomatoLogic::init() {
	colTomato_ = GETCMP1_(Collider);
}

void TomatoLogic::update() {
	if (!activated_) {
		if (SDL_Game::instance()->getTime() > timeForActivation_) {
			activated_ = true;
			colTomato_->createCircularFixture(3, 0, 0, 0, Collider::CollisionLayer::Trigger, true);
		}
	}
	else if (SDL_Game::instance()->getTime() > timeForActivation_ + 500) {
		
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