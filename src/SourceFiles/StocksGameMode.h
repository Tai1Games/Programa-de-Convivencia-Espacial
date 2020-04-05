#pragma once
#include "GameMode.h"
#include "Health.h"
#include "HealthViewer.h"
#include "checkML.h"

class StocksGameMode : public GameMode
{
private:
	vector<int> playerStocks_; //Remaining stocks of each player
	vector<Entity*> roundResults_; //Used to determine winner and mode end
	vector<Health*> playersHealth_; //Reference to the Health component of each player
	vector<b2Vec2> playersStocksPos_; //Position in which the Stocks will be drawn FOR EACH DIFFERENT PLAYER.
	int healtWidth_;
	int maxStocks_;
public:
	StocksGameMode(int stocks = 3);
	~StocksGameMode();
	virtual void init(PlayState* game);
	virtual void render();
	virtual void update();
	virtual bool onPlayerDead(int id); //Returns false when players runs out of stocks.
};