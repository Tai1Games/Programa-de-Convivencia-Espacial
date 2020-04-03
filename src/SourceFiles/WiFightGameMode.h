#pragma once
#include "GameMode.h"
#include "PlayState.h"
#include "RouterLogic.h"
#include "Constants.h"
#include <vector>
class WiFightGameMode : public GameMode
{
private:
	std::vector<double> playerProgress_;
	Entity* router = nullptr;
public:
	WiFightGameMode(int nPlayers): GameMode(nPlayers) {};
	~WiFightGameMode() {};
	virtual void init(PlayState* game);
	void addPoints(int player, double sumPoints);
};

