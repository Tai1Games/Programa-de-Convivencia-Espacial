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

	//Constantes que inicializamos en init.
	int killsMarkerWidth_ = 0;
	int killsMarkerHeight_ = 0;

	void renderKillMarker();

public:
	TimeGameMode(MatchInfo* mInfo);
	~TimeGameMode();
	virtual void init(PlayState* game) override;
	virtual void render() override;
	virtual void update() override;
	virtual void addPoints(int playerID);
	virtual void playerKillsPlayer(int killerId, int deadId = -1) override;
};

