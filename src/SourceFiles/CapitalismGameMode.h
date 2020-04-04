#pragma once
#include "GameMode.h"
#include "PlayState.h"
class CapitalismGameMode : public GameMode
{
private:

public:
	CapitalismGameMode(int nPlayers) : GameMode(nPlayers) {};
	~CapitalismGameMode() {};
	virtual void init(PlayState* game);
	virtual void render();
	virtual void update();
	virtual bool onPlayerDead(int id); //Returns false when players runs out of stocks.
};

