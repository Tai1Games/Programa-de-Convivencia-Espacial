#include "Wallet.h"
#include "Entity.h"
#include "CapitalismGameMode.h"

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