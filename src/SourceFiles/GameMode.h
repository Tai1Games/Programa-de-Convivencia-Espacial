#pragma once
#include <vector>

class Entity;
class PlayState;
class GameMode {
protected:
	PlayState* game_ = nullptr;
	GameMode() {};
	virtual ~GameMode() {};
	std::vector<Entity*> players_;
private:
public:
	virtual void init(PlayState* game);
	virtual void render() {};
	virtual void update() {};
	virtual void onPlayerDead() {};
};