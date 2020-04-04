#include "CapitalismGameMode.h"

void CapitalismGameMode::init(PlayState* game)
{
	GameMode::init(game);
	for (int k = 0; k < nPlayers_; k++) {
		players_.push_back(PlayerFactory::createPlayerWithHealth(game->getEntityManager(), game->getPhysicsWorld(), k,
			Resources::Tinky, tilemap_->getPlayerSpawnPoint(k).x, tilemap_->getPlayerSpawnPoint(k).y, 3));
	}
}