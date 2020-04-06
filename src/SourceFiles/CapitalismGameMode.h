#pragma once
#include "GameMode.h"
#include "PlayState.h"
#include "CoinsPool.h"

class CapitalismGameMode : public GameMode
{
private:
	CoinsPool coinPool_;
	double timeSinceStart = 0;
	double msPerFrame_; //Se inicializa en el init
	double timeToEnd_; //Se inicaliza en el init
public:
	CapitalismGameMode(int nPlayers) : GameMode(nPlayers){};
	~CapitalismGameMode() {};
	virtual void init(PlayState* game);
	virtual void render() {};
	virtual void update();
	virtual bool onPlayerDead(int id) { return true; }; //Returns false when players runs out of stocks.

	void createCoin(b2Vec2 spawnPos, int player = -1, int val = 1);
};

