#pragma once
#include "GameMode.h"
#include "PlayState.h"
#include "CoinsPool.h"
#include "Collider.h"
#include "FireBallPool.h"
#include "TomatoPool.h" //DELETE THIS

class CapitalismGameMode : public GameMode
{
private:
	CoinsPool coinPool_;
	Texture* coinTextureUI_ = nullptr;
	Texture* canvasTimerTexture_ = nullptr;
	SDL_Rect canvasTimerRect_;
	//NEED TO DELETE-------
	TomatoPool tomatoPool_;
	//---------------------
	double timeSinceStart_ = 0;
	double timeSinceSpawn_ = 0;
	double spawnTime_ = 0;
	double currentSpawnTime_ = 0;
	double minimumSpawnTime_ = 0;

	double suddenDeathRenderTime = 0;
	double suddenDeathRenderTimer = 0;
	bool suddenDeathRendering = true;
	int coinsSpawned_ = 0;

	//Constantes que inicializamos en init.
	double sPerFrame_ = 0;
	double timeToEnd_ = 0;
	int winWidth_ = 0;
	int winHeigth_ = 0;
	int coinUIRadius_ = 0;
	int coinUIMarginX_ = 0;
	int coinUIMarginY_ = 0;
	double coinUISpriteScale_ = 0;
	int maxCoins_ = 0;
	int fontCharacterWidth_ = 0;

	std::vector<b2Vec2> coinSpawnersPositions_;
	std::vector<Collider*> roombaColliders_;
	std::vector<Wallet*> playerWallets_;
public:
	CapitalismGameMode(MatchInfo* mInfo) : GameMode(mInfo){};
	virtual ~CapitalismGameMode() {};
	virtual void init(PlayState* game);
	virtual void render();
	virtual void update();
	virtual bool onPlayerDead(int id) { return true; }; //Returns false when players runs out of stocks.
	virtual void createPlayers(PlayState* game);


	void createCoin(b2Vec2 spawnPos, int player = -1, int val = 1);
};

