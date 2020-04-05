#include "Wallet.h"
#include "Entity.h"
#include "CapitalismGameMode.h"

void Wallet::init()
{
	collPlayer_ = GETCMP1_(Collider);
}

void Wallet::dropCoins(int damage, int player)
{
	int coinsToDrop = numCoins_ * (damage * CONST(double, "COIN_DROP_RATE"));
	if (coinsToDrop == 0 && damage > 0) coinsToDrop = numCoins_;
	numCoins_ -= coinsToDrop;
	if (numCoins_ < 0) numCoins_ = 0;
	cout << "HE SOLTADO " << coinsToDrop << endl;
	for (int k = 0; k < coinsToDrop; k++) {
		double a = ((double)SDL_Game::instance()->getRng()->nextInt(0, 360) * CONST(double, "PI")) / 180;
		double x = (collPlayer_->getH(0) + CONST(double, "COIN_BASE_SIZE"))* cos(a);
		double y = (collPlayer_->getH(0) + CONST(double, "COIN_BASE_SIZE")) * sin(a);
		gameMode_->createCoin(b2Vec2(x + collPlayer_->getTransform().p.x, y +collPlayer_->getTransform().p.y), player);
	}
}