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
public:
	AbstractTimedGameMode(int nPlayers);
	~AbstractTimedGameMode() {};

	virtual void init(PlayState* game);
	virtual void render();
	virtual void renderTimer(int secs, int mins);
	virtual void update();
	virtual void updateTime(const vector<int>& playerPoints);
	virtual void playerKillsPlayer(int killerId, int deadId = -1) {};
};

