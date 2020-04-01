#pragma once
#include <vector>

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
private:
public:
	virtual void init(PlayState* state);
	virtual void render() {};
	virtual void update() {};
	virtual bool onPlayerDead(int id) { return true; };
	Entity* getRoundResults() { return winner_; }
};