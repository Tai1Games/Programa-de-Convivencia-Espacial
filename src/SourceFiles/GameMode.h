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
	std::vector<Entity*> roundResults_; //Player vector ordered by the position they rank at the end of the round.
	bool roundFinished_ = false;
private:
public:
	virtual void init(PlayState* state);
	virtual void render() {};
	virtual void update() {};
	virtual bool onPlayerDead(int id) { return true; };
	std::vector<Entity*> getRoundResults() { return roundResults_; }
};