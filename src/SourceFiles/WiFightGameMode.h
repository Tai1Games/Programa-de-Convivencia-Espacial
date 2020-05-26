#pragma once
#include "GameMode.h"
#include "PlayState.h"
#include "Constants.h"
#include "checkML.h"
#include <vector>
#include "WiFiWavePool.h"

class MatchInfo;
class WiFightGameMode : public GameMode
{
private:
	std::vector<double> playerProgress_;
	Entity* router = nullptr;
	WiFiWavePool wifiWavesPool_;
	int halfWinWidth_ = CONST(int, "WINDOW_WIDTH") / 2;
	int halfWinHeight_ = CONST(int, "WINDOW_HEIGHT") / 2;
	double pointsToWin_ = CONST(double, "POINTS_TO_WIN");

public:
	WiFightGameMode(MatchInfo* mInfo) : GameMode(mInfo, GamemodeID::WiFight) {};
	virtual ~WiFightGameMode() {};
	virtual void init(PlayState* game);
	virtual void render();
	void addPoints(int player, double sumPoints);
};

