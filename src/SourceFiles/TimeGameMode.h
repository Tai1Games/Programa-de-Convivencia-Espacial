#pragma once
#include "AbstractTimedGameMode.h"
#include "checkML.h"
#include "Health.h"
#include "HealthViewer.h"
#include "TomatoPool.h"

class TimeGameMode : public AbstractTimedGameMode
{
private:
	vector<int> playerKills_; //Kills of each player
	vector<Entity*> roundResults_; //Used to determine winner and mode end
	vector<Health*> playersHealth_; //Reference to the Health component of each player
	vector<b2Vec2> playersPointsPos_; //Position in which the Stocks will be drawn FOR EACH DIFFERENT PLAYER.
	int healtWidth_ = 30;

	int skullUISize_ = 0;
	int skullUIMarginX_ = 0;
	Texture* skullTextureUI_ = nullptr;
	//Texture* canvasTimerTexture_ = nullptr;
	//SDL_Rect canvasTimerRect_ = {};
	//double timeSinceStart_ = 0;

	//double suddenDeathRenderTime = 0;
	//double suddenDeathRenderTimer = 0;
	//bool suddenDeathRendering = true;

	//Constantes que inicializamos en init.
	/*double sPerFrame_ = 0;
	double timeToEnd_ = 0;
	int winWidth_ = 0;
	int winHeigth_ = 0;*/

	int killsMarkerWidth_ = 0;
	int killsMarkerHeight_ = 0;

	//void renderTimer(int seconds, int minutes);
	void renderKillMarker();
	int calculateDigits(int points);

	TomatoPool tomatoPool_;

public:
	TimeGameMode(int nPlayers);
	~TimeGameMode();
	virtual void init(PlayState* game);
	virtual void render();
	virtual void update();
	void addPoints(int playerID);
	virtual void playerKillsPlayer(int killerId, int deadId = -1) override;
};

