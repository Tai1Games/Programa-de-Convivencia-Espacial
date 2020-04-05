#include "CapitalismGameMode.h"

void CapitalismGameMode::init(PlayState* game)
{
	GameMode::init(game);
	coinPool_.init(game->getEntityManager(), game->getPhysicsWorld());

	for (int k = 0; k < nPlayers_; k++) {
		players_.push_back(PlayerFactory::createPlayerWithWallet(game->getEntityManager(), game->getPhysicsWorld(), k,
			Resources::Body, tilemap_->getPlayerSpawnPoint(k).x, tilemap_->getPlayerSpawnPoint(k).y, this));
	}
}

void CapitalismGameMode::update() {
	timeSinceStart += CONST(double, "MS_PER_FRAME");
	if (timeSinceStart >= CONST(double, "TIME_TO_END") && !roundFinished_) {
		int maxPoints = 0;
		bool draw = false;
		for (int k = 0; k < players_.size(); k++) {
			Wallet* playerWallet = players_[k]->getComponent<Wallet>(ComponentType::Wallet);
			if (playerWallet->getCoins() > maxPoints) {
				winner_ = players_[k];
				maxPoints = playerWallet->getCoins();
				draw = false;
			}
			else if (playerWallet->getCoins() == maxPoints) draw = true;
			cout << "PLAYER: " << players_[k]->getComponent<PlayerData>(ComponentType::PlayerData)->getPlayerNumber() << " HAS " << playerWallet->getCoins() << endl;
		}
		if (!draw) {
			roundFinished_ = true;
			cout << "PLAYER: " << winner_->getComponent<PlayerData>(ComponentType::PlayerData)->getPlayerNumber() << "WON." << endl;
		}
	}
}

void CapitalismGameMode::createCoin(b2Vec2 spawnPos, int player,int val) {
	coinPool_.addCoin(spawnPos, player, val);
}