#include "Weapon.h"
#include <iostream>
#include "InputHandler.h"
#include "Hands.h"
#include "Health.h"
#include "Wallet.h"
#include "Collision.h"
#include "ThrownByPlayer.h"

int Weapon::calculateCoinsDropped(int coinsPlayer)
{
	if (coinsPlayer <= CONST(int, "WEAPON_HIGH_TIER_COIN_DAMAGE")) return 3;
	else if (coinsPlayer <= CONST(int, "WEAPON_MID_TIER_COIN_DAMAGE")) return 2;
	else if (coinsPlayer > CONST(int, "WEAPON_MID_TIER_COIN_DAMAGE")) return 1;
	return 0;
}

void Weapon::init()
{
	ih_ = SDL_Game::instance()->getInputHandler();
	mainCollider_ = GETCMP1_(Collider);
	vw_ = GETCMP1_(Viewer);

	//Tamaño del vector segun el numero de jugadores
	playerInfo_.resize(4);
}

void Weapon::handleInput()
{
	if (currentHand_ == nullptr) {
		for (int i = 0; i < playerInfo_.size(); i++) {

			if (!IsPicked() && playerInfo_[i].isNear &&
				ih_->isButtonJustDown(i, SDL_CONTROLLER_BUTTON_Y)) {
				cout << "pickedUpWeapon";
				PickObjectBy(playerInfo_[i].playerHands);
			}
		}
	}
	else if (IsPicked() && ih_->isButtonJustDown(currentHand_->getPlayerId(), SDL_CONTROLLER_BUTTON_Y))
	{
		UnPickObject();
	}
}

void Weapon::PickObjectBy(Hands* playerH)
{
	if (playerH->getWeaponID() == NoWeapon) {
		currentHand_ = playerH;
		picked_ = true;
		currentHand_->setWeapon(weaponType_, this);
		mainCollider_->getBody()->SetEnabled(false);
		vw_->setDrawable(false);
	}
}

void Weapon::UnPickObject()
{
	currentHand_->setWeapon(NoWeapon, nullptr);
	picked_ = false;
	mainCollider_->getBody()->SetEnabled(true);
	vw_->setDrawable(true);

	cout << "dirHand: " << currentHand_->getDir().x << ", " << currentHand_->getDir().y << "\n";
	cout << "dirplayer: " << currentHand_->getVel().x << ", " << currentHand_->getVel().y << "\n";

	//Si se tira un objeto, se guarda en el objeto lanzado la ID de quien lo lanza.
	ThrownByPlayer* tObj = GETCMP_FROM_FIXTURE_(mainCollider_->getFixture(0), ThrownByPlayer);
	if (tObj != nullptr) tObj->throwObject(currentHand_->getPlayerId());

	mainCollider_->setLinearVelocity(b2Vec2(0, 0));
	mainCollider_->setTransform(b2Vec2(currentHand_->getPos().x + currentHand_->getDir().x * CONST(double, "ARM_LENGTH_PHYSICS"), currentHand_->getPos().y - currentHand_->getDir().y * CONST(double, "ARM_LENGTH_PHYSICS")), currentHand_->getAngle());
	mainCollider_->applyLinearImpulse(b2Vec2(currentHand_->getDir().x * CONST(double, "WEAPON_THROW_SPEED") + currentHand_->getVel().x, -currentHand_->getDir().y * CONST(double, "WEAPON_THROW_SPEED") + currentHand_->getVel().y), mainCollider_->getBody()->GetLocalCenter());
	mainCollider_->getBody()->SetAngularVelocity(CONST(double, "WEAPON_SPIN_SPEED"));
	currentHand_ = nullptr;
}

int Weapon::getPlayerId() {
	return currentHand_->getPlayerId();
}

void Weapon::onCollisionEnter(Collision* c)
{
	Entity* other = c->entity;
	Hands* otherHand = GETCMP2(other, Hands);
	Hands* myHand = getCurrentHand();

	if (otherHand != nullptr) {
		SavePlayerInfo(otherHand->getPlayerId(), otherHand, GETCMP2(other, Health), GETCMP2(other, Wallet));
		if (myHand != nullptr && otherHand != myHand) {
			detectPlayer(other, GETCMP2(other, PlayerData)->getId());
		}
	}
}

void Weapon::onCollisionExit(Collision* c)
{
	Hands* otherHand = GETCMP2(c->entity, Hands);

	if (otherHand != nullptr) {
		DeletePlayerInfo(otherHand->getPlayerId());
	}

	PlayerData* playerData = GETCMP2(c->entity, PlayerData);
	if (playerData != nullptr) {
		loseContactPlayer(c->entity, playerData->getPlayerNumber());
	}
}

void Weapon::SavePlayerInfo(int index, Hands* playerH, Health* healthAux, Wallet* walletAux)
{
	playerInfo_[index].isNear = true;
	playerInfo_[index].playerHands = playerH;
	if (healthAux) playerInfo_[index].playerHealth = healthAux;
	else playerInfo_[index].playerWallet = walletAux;
}
void Weapon::DeletePlayerInfo(int index)
{
	playerInfo_[index].isNear = false;
	playerInfo_[index].playerHands = nullptr;
}