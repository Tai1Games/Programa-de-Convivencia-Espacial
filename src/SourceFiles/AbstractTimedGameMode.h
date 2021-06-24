#pragma once
#include "GameMode.h"

class AbstractTimedGameMode : public GameMode
{
protected:
	Texture* canvasTimerTexture_ = nullptr;
	SDL_Rect canvasTimerRect_ = {};
	double timeSinceStart_ = 0;

	Texture* suddenDeathTexture_ = nullptr;
	double suddenDeathRenderTime_ = 0;
	double suddenDeathRenderTimer_ = 0;
	bool suddenDeathRendering_ = true;

	//Constantes que inicializamos en init.
	double sPerFrame_ = 0;
	double timeToEnd_ = 0;
	int winWidth_ = 0;
	int winHeigth_ = 0;
	const float minutesFreq_ = 0.016666667;

	int halfWinWidth_ = 0, halfWinHeight_ = 0;

	virtual void updateTime(const vector<int>& playerPoints);

private:
	bool activeTimer_ = false;

	virtual void renderTimer(int secs, int mins);
	void setActiveTimer(bool b) { activeTimer_ = b; };

public:
	AbstractTimedGameMode(MatchInfo* mInfo, GamemodeID id) : GameMode(mInfo, id) {};
	~AbstractTimedGameMode() {};

	virtual void init(PlayState* game);
	virtual void render();
	virtual void update();
	virtual void playerKillsPlayer(int killerId, int deadId = -1) {};
	virtual void activateControl();
};
