#pragma once
#include <vector>
#include "box2d.h"
#include "TileMap.h"
#include "PlayerFactory.h"
#include "checkML.h"
#include "FireBallPool.h"
#include "MatchInfo.h"

class Entity;
class PlayState;

//Abstract class from which every GameMode will inherit (Stocks, TimeBased, Capitalism ... )
class GameMode {
protected:
	PlayState* state_ = nullptr;
	std::vector<Entity*> players_; //Player vector. We use Entity because we will need multiple components from them.
	int winnerId_ = -1; //id of the player who wins the round
	bool roundFinished_ = false;
	TileMap* tilemap_ = nullptr;

	MatchInfo* matchInfo_ = nullptr;
	int nPlayers_ = 0;
	GamemodeID gamemodeId_ = GamemodeID::NUMBER_OF_GAMEMODES;
	//Barras de progreso usadas por WiFightGameMode y ControllerGameMode(subidas a GameMode por herencia para no copiar y pegar dos veces)
	vector<Texture*> emptyProgressBars_;
	vector<Texture*> progressBars_;
	vector<b2Vec2> healthViewerPos_;
	void initProgressBars();
	void renderProgressBars(const std::vector<double>& progressValues, const double& goalScore);

private:
public:
	GameMode(MatchInfo* matchinfo, GamemodeID id) : matchInfo_(matchinfo),nPlayers_(matchInfo_->getNumberOfPlayers()),gamemodeId_(id) {};
	virtual ~GameMode() {};
	virtual void init(PlayState* state);
	virtual void render() {};
	virtual void update();
	virtual bool onPlayerDead(int id) { return true; };
	virtual void setTileMap(TileMap* tm) { tilemap_ = tm; };
	virtual void playerKillsPlayer(int killerId, int deadId = -1) {};
	virtual void createPlayers(PlayState* state);
};
