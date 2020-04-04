#pragma once
#include <vector>
#include "box2d.h"
#include "TileMap.h"
#include "checkML.h"

class Entity;
class PlayState;

//Abstract class from which every GameMode will inherit (Stocks, TimeBased, Capitalism ... )
class GameMode {
protected:
	PlayState* state_ = nullptr;
	std::vector<Entity*> players_; //Player vector. We use Entity because we will need multiple components from them.
	Entity* winner_ = nullptr; //Player who wins the round.
	bool roundFinished_ = false;
	TileMap* tilemap_;
private:
public:
	GameMode() {};
	virtual ~GameMode() {};
	virtual void init(PlayState* state);
	virtual void render() {};
	virtual void update() {};
	virtual bool onPlayerDead(int id) { return true; };
	Entity* getRoundResults() { return winner_; }
	virtual void setTileMap(TileMap* tm) { tilemap_ = tm; };
};
