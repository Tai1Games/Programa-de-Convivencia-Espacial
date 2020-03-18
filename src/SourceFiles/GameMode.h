#pragma once
#include "PlayState.h"

class GameMode {
protected:
	PlayState* game_ = nullptr;
	GameMode() {};
	virtual ~GameMode() {};
	vector<Entity*> players_;
private:
public:
	virtual void init(PlayState* game);
	virtual void render() {};
	virtual void update() {};
	virtual void onPlayerDead() {};
};