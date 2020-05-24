#pragma once
#include "GameState.h"
#include "MatchInfo.h"

class InputHandler;
class Texture;
class EndGameState :
	public GameState
{
private:
	InputHandler* ih = nullptr;
	Texture* backgroundT_ = nullptr;
	vector<MatchInfo::PlayerInfo*> sortedPlayerInfo_;
	bool anyButtonPush = false;
	vector<Entity*> leaderboardUI;
public:
	virtual ~EndGameState();
	virtual void init();
	virtual void render();
	virtual void update();
	virtual void handleInput();
	virtual void onLoaded();
};
