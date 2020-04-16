#pragma once
#include "GameMode.h"
#include "checkML.h"
#include "Health.h"
#include "HealthViewer.h"

class TimeGameMode : public GameMode
{
private:
	vector<int> playerKills_; //Kills of each player
	vector<Entity*> roundResults_; //Used to determine winner and mode end
	vector<Health*> playersHealth_; //Reference to the Health component of each player
	vector<b2Vec2> playersPointsPos_; //Position in which the Stocks will be drawn FOR EACH DIFFERENT PLAYER.
	int healtWidth_;

	Texture* canvasTimerTexture_ = nullptr;
	SDL_Rect canvasTimerRect_;
	double timeSinceStart_ = 0;

	double suddenDeathRenderTime = 0;
	double suddenDeathRenderTimer = 0;
	bool suddenDeathRendering = true;

	//Constantes que inicializamos en init.
	double sPerFrame_ = 0;
	double timeToEnd_ = 0;
	int winWidth_ = 0;
	int winHeigth_ = 0;

	int killsMarkerWidth_ = 0;
	int killsMarkerHeight_ = 0;

	void renderTimer(int seconds, int minutes);
	void renderKillMarker();
	int calculateDigits(int points);

public:
	TimeGameMode(int nPlayers, int time = 6);
	~TimeGameMode();
	virtual void init(PlayState* game);
	virtual void render();
	virtual void update();
	virtual bool onPlayerDead(int id); //Returns false when players runs out of stocks.
};

