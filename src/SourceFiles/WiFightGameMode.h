#pragma once
#include "GameMode.h"
#include "PlayState.h"
#include <vector>
class WiFightGameMode : public GameMode
{
private:
	std::vector<int> playerProgress_;
	Entity* router = nullptr;
public:
	WiFightGameMode() {};
	~WiFightGameMode() {};
	virtual void init(PlayState* game);
};

