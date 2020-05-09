#pragma once
#include "GameMode.h"
#include "PlayState.h"
#include "Constants.h"
#include "checkML.h"
#include <vector>

class WiFightGameMode : public GameMode
{
private:
	std::vector<double> playerProgress_;
	Entity* router = nullptr;
public:
	WiFightGameMode(int nPlayers): GameMode(nPlayers) {};
	virtual ~WiFightGameMode() {};
	virtual void init(PlayState* game);
	virtual void render();
	void addPoints(int player, double sumPoints);
};

