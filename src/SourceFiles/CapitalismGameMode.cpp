#include "CapitalismGameMode.h"
#include "FireBallGenerator.h"


void CapitalismGameMode::init(PlayState* game)
{
	GameMode::init(game);
	coinPool_.init(game->getEntityManager(), game->getPhysicsWorld());

	sPerFrame_ = CONST(double, "SECONDS_PER_FRAME");
	timeToEnd_ = CONST(double, "TIME_TO_END");
	spawnTime_ = CONST(double, "TIME_TO_SPAWN_COIN");
	minimumSpawnTime_ = CONST(double, "MINIMUM_SPAWN_COIN_TIME");
	maxCoins_ = CONST(int, "TOTAL_COIN_NUMBER");
	currentSpawnTime_ = spawnTime_;
	coinSpawnersPositions_ = tilemap_->getCoinsSpawnPoints();

	for (b2Vec2 pos : coinSpawnersPositions_) {
		roombaColliders_.push_back(ObjectFactory::createRoomba(game->getEntityManager(),
			game->getPhysicsWorld(), pos)->getComponent<Collider>(ComponentType::Collider));
	}

	for (int k = 0; k < nPlayers_; k++) {
		players_.push_back(PlayerFactory::createPlayerWithWallet(game->getEntityManager(), game->getPhysicsWorld(), k,
			Resources::Body, tilemap_->getPlayerSpawnPoint(k).x, tilemap_->getPlayerSpawnPoint(k).y, this));
	}



}

void CapitalismGameMode::update() {
	timeSinceStart_ += sPerFrame_;
	if (timeSinceStart_ >= timeToEnd_ && !roundFinished_) {
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
			cout << "PLAYER: " << winner_->getComponent<PlayerData>(ComponentType::PlayerData)->getPlayerNumber() << " WON." << endl;
		}

	}
	if (coinsSpawned_ < maxCoins_) {
		timeSinceSpawn_ += sPerFrame_;
		if (timeSinceSpawn_ >= currentSpawnTime_) {
			timeSinceSpawn_ = 0;
			if (timeToEnd_ < timeSinceStart_) currentSpawnTime_ = minimumSpawnTime_;
			else currentSpawnTime_ = spawnTime_ - ((timeSinceStart_ / timeToEnd_) * spawnTime_);
			b2Vec2 position = roombaColliders_[rand() % roombaColliders_.size()]->getPos();
			createCoin(position);
			coinsSpawned_++;
		}
	}
	
}

void CapitalismGameMode::createCoin(b2Vec2 spawnPos, int player,int val) {
	coinPool_.addCoin(spawnPos, player, val);
}