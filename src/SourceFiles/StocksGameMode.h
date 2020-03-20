#pragma once
#include "GameMode.h"
#include "Health.h"
#include "HealthViewer.h"
#include "box2d.h"
class StocksGameMode : public GameMode
{
private:
	vector<int> playerStocks_;
	vector<Health*> playersHealth_;
	vector<b2Vec2> playersStocksPos_;
	int healtWidth_;
	int maxStocks_;
public:
	StocksGameMode(int stocks = 3);
	virtual void init(PlayState* game);
	virtual void render();
	virtual void update();
	virtual bool onPlayerDead(Health* player);  //returns false when player runs out of stocks
};