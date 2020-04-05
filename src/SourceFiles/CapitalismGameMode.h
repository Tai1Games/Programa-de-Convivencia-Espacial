#pragma once
#include "GameMode.h"
#include "PlayState.h"
#include "CoinsPool.h"

class CapitalismGameMode : public GameMode
{
private:
	CoinsPool coinPool_;
public:
	CapitalismGameMode(int nPlayers) : GameMode(nPlayers){};
	~CapitalismGameMode() {};
	virtual void init(PlayState* game);
	virtual void render() {};
	virtual void update() {
		std::cout << "jajasi";
	};
	virtual bool onPlayerDead(int id) { return true; }; //Returns false when players runs out of stocks.

	void createCoin(b2Vec2 pos, int val = 1);
};

