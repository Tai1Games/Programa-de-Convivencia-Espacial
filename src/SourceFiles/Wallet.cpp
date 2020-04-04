#include "Wallet.h"
#include "Entity.h"

void Wallet::init()
{
	collPlayer_ = GETCMP1_(Collider);
}

void Wallet::dropCoins(int damage)
{
	int coinsToDrop = numCoins_ * (damage * CONST(double, "COIN_DROP_RATE"));
	numCoins_ -= coinsToDrop;
	if (numCoins_ < 0) numCoins_ = 0;
	cout << "HE SOLTADO " << coinsToDrop << endl;
}
