#pragma once
#include "AbstractTimedGameMode.h"
#include "PlayState.h"
#include "CoinsPool.h"
#include "Collider.h"
#include "FireBallPool.h"
#include "TomatoPool.h" //DELETE THIS

class CapitalismGameMode : public AbstractTimedGameMode
{
private:
	CoinsPool coinPool_;
	Texture* coinTextureUI_ = nullptr;
	double timeSinceSpawn_ = 0;
	double spawnTime_ = 0;
	double currentSpawnTime_ = 0;
	double minimumSpawnTime_ = 0;
	int coinsSpawned_ = 0;

	//Constantes que inicializamos en init.
	int coinUIRadius_ = 0;
	int coinUIMarginX_ = 0;
	int coinUIMarginY_ = 0;
	double coinUISpriteScale_ = 0;
	int maxCoins_ = 0;
	int fontCharacterWidth_ = 0;
	int headUIWidth_ = 0;
	int headUIHeight_ = 0;

	std::vector<b2Vec2> coinSpawnersPositions_;
	std::vector<Collider*> roombaColliders_;
	std::vector<Wallet*> playerWallets_;
	std::vector<int> playerCoins_;

	void renderCoinsMarker();
public:
	CapitalismGameMode(MatchInfo* mInfo) : AbstractTimedGameMode(mInfo, GamemodeID::Capitalism) {};
	virtual ~CapitalismGameMode() {};
	virtual void init(PlayState* game) override;
	virtual void render() override;
	virtual void update() override;
	virtual void createPlayers(PlayState* game);

	void createCoin(b2Vec2 spawnPos, int player = -1, int val = 1);
};
