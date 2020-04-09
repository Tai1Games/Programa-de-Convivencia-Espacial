#pragma once
#include "GameMode.h"
#include "PlayState.h"
#include "CoinsPool.h"
#include "Collider.h"
#include "FireBallPool.h"

class CapitalismGameMode : public GameMode
{
private:
	CoinsPool coinPool_;
	FireBallPool fireballPool_;
	double timeSinceStart_ = 0;
	double timeSinceSpawn_ = 0;
	double spawnTime_ = 0;
	double currentSpawnTime_ = 0;
	double minimumSpawnTime_ = 0;
	double sPerFrame_ = 0; //Se inicializa en el init
	double timeToEnd_ = 0; //Se inicaliza en el init
	int coinsSpawned_ = 0;
	int maxCoins_ = 0;

	std::vector<b2Vec2> coinSpawnersPositions_;
	std::vector<Collider*> roombaColliders_;
public:
	CapitalismGameMode(int nPlayers) : GameMode(nPlayers){};
	virtual ~CapitalismGameMode() {};
	virtual void init(PlayState* game);
	virtual void render() {};
	virtual void update();
	virtual bool onPlayerDead(int id) { return true; }; //Returns false when players runs out of stocks.

	void createCoin(b2Vec2 spawnPos, int player = -1, int val = 1);
};

