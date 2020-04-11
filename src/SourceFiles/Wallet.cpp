#include "Wallet.h"
#include "Entity.h"
#include "CapitalismGameMode.h"

void Wallet::init()
{
	collPlayer_ = GETCMP1_(Collider);
	coinBaseSize_ = CONST(double, "COIN_BASE_SIZE");
	pi_ = CONST(double, "PI");
}

void Wallet::dropCoins(int damage, int player)
{
	int coinsToDrop = numCoins_ * (damage * CONST(double, "COIN_DROP_RATE"));
	if (coinsToDrop == 0) coinsToDrop = numCoins_;
	numCoins_ -= coinsToDrop;
	if (numCoins_ < 0) numCoins_ = 0;
	cout << "HE SOLTADO " << coinsToDrop << endl;
	for (int k = 0; k < coinsToDrop; k++) {
		double a = (rand() % 360 * pi_) / 180;
		double x = (collPlayer_->getH(0) + coinBaseSize_) * cos(a);
		double y = (collPlayer_->getH(0) + coinBaseSize_)  * sin(a);
		gameMode_->createCoin(b2Vec2(x + collPlayer_->getTransform().p.x, y +collPlayer_->getTransform().p.y), player);
	}
}