#include "CapitalismGameMode.h"

void CapitalismGameMode::init(PlayState* game)
{
	GameMode::init(game);
	coinPool_.init(game->getEntityManager(), game->getPhysicsWorld());

	for (int k = 0; k < nPlayers_; k++) {
		players_.push_back(PlayerFactory::createPlayerWithWallet(game->getEntityManager(), game->getPhysicsWorld(), k,
			Resources::Tinky, tilemap_->getPlayerSpawnPoint(k).x, tilemap_->getPlayerSpawnPoint(k).y, this));
	}

	createCoin(b2Vec2(1, 2));
}

void CapitalismGameMode::createCoin(b2Vec2 spawnPos, int val) {
	coinPool_.addCoin(spawnPos, val);
}