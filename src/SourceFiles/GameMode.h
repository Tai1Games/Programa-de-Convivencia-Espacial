#pragma once
#include <vector>
#include "box2d.h"
#include "TileMap.h"

class Entity;
class PlayState;

//Abstract class from which every GameMode will inherit (Stocks, TimeBased, Capitalism ... )
class GameMode {
protected:
	PlayState* state_ = nullptr;
	GameMode() {};
	virtual ~GameMode() {};
	std::vector<Entity*> players_; //Player vector. We use Entity because we will need multiple components from them.
	Entity* winner_ = nullptr; //Player who wins the round.
	bool roundFinished_ = false;
	TileMap* tilemap_;
	//Barras de progreso usadas por WiFightGameMode y ControllerGameMode(subidas a GameMode por herencia para no copiar y pegar dos veces)
	vector<Texture*> emptyProgressBars_;
	vector<Texture*> progressBars_;
	vector<b2Vec2> healthViewerPos_;
	void initProgressBars();
	void renderProgressBars(const std::vector<double>& progressValues, const double& goalScore);
private:
public:
	virtual void init(PlayState* state);
	virtual void render() {};
	virtual void update() {};
	virtual bool onPlayerDead(int id) { return true; };
	Entity* getRoundResults() { return winner_; }
	virtual void setTileMap(TileMap* tm) { tilemap_ = tm; };
};
