#include "Weapon.h"
#include <iostream>
#include "InputBinder.h"
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
	maxThrowSpeed_ = CONST(double, "WEAPON_MAX_THROW_SPEED");
	minThrowSpeed_ = CONST(double, "WEAPON_MIN_THROW_SPEED");
	spinOnThrowSpeed_ = CONST(double, "WEAPON_SPIN_SPEED");

	mainCollider_ = GETCMP1_(Collider);
	vw_ = GETCMP1_(Viewer);
	mainCollider_->createCircularFixture(2, 0, 0, 0, Collider::CollisionLayer::Trigger , true);
	//Tamaño del vector segun el numero de jugadores
	playerInfo_.resize(4);
	
	entity_->getEntityManager()->getWeaponVector()->push_back(this);

	throwCooldown_ = CONST(int, "THROW_COOLDOWN");
}

void Weapon::handleInput()
{
	if (currentHand_ == nullptr) {
		for (int i = 0; i < playerInfo_.size(); i++) {
			if (!IsPicked() && playerInfo_[i].isNear &&
				playerInfo_[i].playerBinder->pressPick()) {
				PickObjectBy(i);
			}
		}
	}
	else if (throwCooldownTimer_ >= throwCooldown_ && IsPicked() && playerInfo_[pickedIndex_].playerBinder->pressThrow())
	{
		throwCooldownTimer_ = 0;
		UnPickObject();
	}
}

void Weapon::PickObjectBy(int index)
{
	Hands* playerH = playerInfo_[index].playerHands;
	if (playerH->getWeaponID() == NoWeapon) {
		currentHand_ = playerH;
		picked_ = true;
		pickedIndex_ = index;
		currentHand_->setWeapon(weaponType_, this);
		mainCollider_->getBody()->SetEnabled(false);
		vw_->setDrawable(false);

		ThrownByPlayer* throwData = GETCMP1_(ThrownByPlayer);
		throwData->SetOwner(index);
	}
}

void Weapon::UnPickObject()
{
	//Si se tira un objeto, se guarda en el objeto lanzado la ID de quien lo lanza.
	GETCMP1_(ThrownByPlayer)->throwObject(pickedIndex_);

	currentHand_->setWeapon(NoWeapon, nullptr);
	picked_ = false;
	pickedIndex_ = -1;
	mainCollider_->getBody()->SetEnabled(true);
	vw_->setDrawable(true);

	cout << "dirHand: " << currentHand_->getDir().x << ", " << currentHand_->getDir().y << "\n";
	cout << "dirplayer: " << currentHand_->getVel().x << ", " << currentHand_->getVel().y << "\n";

	mainCollider_->setLinearVelocity(b2Vec2(0, 0));
	mainCollider_->setTransform(b2Vec2(currentHand_->getPos().x + currentHand_->getDir().x * currentHand_->getArmLengthPhysics(), currentHand_->getPos().y - currentHand_->getDir().y * currentHand_->getArmLengthPhysics()), currentHand_->getAngle());
	
	double actualMagnitude = currentHand_->getVel().Length();
	double resultThrowSpeed = minThrowSpeed_ + 
		((actualMagnitude*(maxThrowSpeed_ - minThrowSpeed_))/10/*Media de magnitud maxima del jugador*/);
	/*Hay que tener en cuenta el tamaño de la fixture principal del arma*/
	float tam =  mainCollider_->getW(0) +  mainCollider_->getH(0);
	resultThrowSpeed *= tam;
	mainCollider_->applyLinearImpulse(b2Vec2(currentHand_->getDir().x * resultThrowSpeed, -currentHand_->getDir().y * resultThrowSpeed), mainCollider_->getBody()->GetLocalCenter());
	mainCollider_->getBody()->SetAngularVelocity(spinOnThrowSpeed_);
	currentHand_ = nullptr;
}

void Weapon::letFallObject()
{
	//Si se tira un objeto, se guarda en el objeto lanzado la ID de quien lo lanza.
	GETCMP1_(ThrownByPlayer)->throwObject(pickedIndex_);

	currentHand_->setWeapon(NoWeapon, nullptr);
	picked_ = false;
	pickedIndex_ = -1;
	mainCollider_->getBody()->SetEnabled(true);
	vw_->setDrawable(true);

	mainCollider_->setLinearVelocity(b2Vec2(0, 0));
	mainCollider_->setTransform(b2Vec2(currentHand_->getPos().x + currentHand_->getDir().x * currentHand_->getArmLengthPhysics(), currentHand_->getPos().y - currentHand_->getDir().y * currentHand_->getArmLengthPhysics()), currentHand_->getAngle());
	double resultThrowSpeed = 1.5;
	mainCollider_->applyLinearImpulse(b2Vec2(currentHand_->getDir().x * resultThrowSpeed, -currentHand_->getDir().y * resultThrowSpeed), mainCollider_->getBody()->GetLocalCenter());
	//mainCollider_->getBody()->SetAngularVelocity(spinOnThrowSpeed_);
	currentHand_ = nullptr;
}

int Weapon::getPlayerId() {
	return currentHand_->getPlayerId();
}

void Weapon::onCollisionEnter(Collision* c)
{
	Entity* other = c->entity;
	Hands* otherHand = GETCMP2(other, Hands);
	Collider* coll = GETCMP1_(Collider);
	b2Fixture* auxF = coll->getFixture(1);

	if (otherHand != nullptr &&
		auxF->GetFilterData().categoryBits == Collider::CollisionLayer::Trigger) {
		SavePlayerInfo(otherHand->getPlayerId(), otherHand, GETCMP2(other, Health), GETCMP2(other, Wallet), GETCMP2(other, PlayerData)->getBinder());
	}
}

void Weapon::onCollisionExit(Collision* c)
{
	Hands* otherHand = GETCMP2(c->entity, Hands);

	if (otherHand != nullptr) {
		DeletePlayerInfo(otherHand->getPlayerId());
	}
}

void Weapon::SavePlayerInfo(int index, Hands* playerH, Health* healthAux, Wallet* walletAux,InputBinder* binderAux)
{
	playerInfo_[index].isNear = true;
	playerInfo_[index].playerHands = playerH;
	playerInfo_[index].playerBinder = binderAux;
	if (healthAux) playerInfo_[index].playerHealth = healthAux;
	else playerInfo_[index].playerWallet = walletAux;
}

void Weapon::DeletePlayerInfo(int index)
{
	playerInfo_[index].isNear = false;
	playerInfo_[index].playerHands = nullptr;
}

void Weapon::update() {
	if(picked_)
		throwCooldownTimer_++;
}