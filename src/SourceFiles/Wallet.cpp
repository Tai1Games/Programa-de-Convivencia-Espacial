#include "Wallet.h"
#include "Entity.h"
#include "CapitalismGameMode.h"
#include "Collision.h"

void Wallet::init()
{
	numCoins_ = CONST(int, "INITIAL_COINS");
	collPlayer_ = GETCMP1_(Collider);
	coinBaseSize_ = CONST(double, "COIN_BASE_SIZE");
}

void Wallet::dropCoins(int damage, int player)
{
	int coinsToDrop = numCoins_ * (damage * CONST(double, "COIN_DROP_RATE"));
	if (coinsToDrop == 0) coinsToDrop = numCoins_;
	numCoins_ -= coinsToDrop;
	if (numCoins_ < 0) numCoins_ = 0;
	cout << "HE SOLTADO " << coinsToDrop << endl;
	for (int k = 0; k < coinsToDrop; k++) {
		gameMode_->createCoin(b2Vec2(collPlayer_->getTransform().p.x, collPlayer_->getTransform().p.y), player);
	}
}

void Wallet::onCollisionEnter(Collision* c)
{
	b2Fixture* fix = GETCMP1_(Collider)->getFixture(0);
	if (!fix->IsSensor())
	{
		//Measure de impact of an object with the player
		b2Vec2 force = fix->GetBody()->GetMass() * fix->GetBody()->GetLinearVelocity();

		int impact = force.Length();

		Weapon* w = GETCMP_FROM_FIXTURE_(fix, Weapon);
		//Si se impacta con un arma al umbral más alto de fuerza, se recibe su daño de impacto
		if (w != nullptr) {
			impact = (impact >= CONST(double, "HIGH_DAMAGE")) ? w->getImpactDamage() : 0;
		}
		else {
			//Depending on the force of impact we apply damage to the player

			if (impact < CONST(int, "LOW_DAMAGE")) impact = 0;

			else if (impact >= CONST(int, "LOW_DAMAGE") && impact < CONST(double, "MEDIUM_DAMAGE")) impact = 1;

			else if (impact >= CONST(double, "MEDIUM_DAMAGE") && impact < CONST(double, "HIGH_DAMAGE")) impact = 2;

			else if (impact >= CONST(double, "HIGH_DAMAGE")) /*&& impact < CONST(double, "HIGH_DAMAGE"))*/ impact = 3;
		}

		if (impact > 0)
			c->collisionHandler->addCoinDrop(std::make_tuple(this, GETCMP1_(PlayerData), impact));
	}

}
