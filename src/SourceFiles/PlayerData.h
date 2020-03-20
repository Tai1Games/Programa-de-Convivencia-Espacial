#pragma once
#include "Component.h"
class PlayerData : public Component
{
private:
	int playerNumber_;
public:
	PlayerData(int playerNumber) : Component(ComponentType::PlayerData) { playerNumber_ = playerNumber; }
	~PlayerData() {};

	int getPlayerNumber() { return playerNumber_; }
};

