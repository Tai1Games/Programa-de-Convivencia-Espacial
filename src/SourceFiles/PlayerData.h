#pragma once
#include "Component.h"
#include "checkML.h"

//Contains data needed by Player-related components
//ALWAYS add this component to the player before any other
class PlayerData : public Component
{
private:
	int playerNumber_;
public:
	PlayerData(int playerNumber) : Component(ComponentType::PlayerData) { playerNumber_ = playerNumber; }
	~PlayerData() {};

	int getPlayerNumber() { return playerNumber_; }
};

