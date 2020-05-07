#pragma once
#include "Component.h"
#include "checkML.h"
#include "Entity.h"
#include "InputBinder.h"
//Contains data needed by Player-related components
//ALWAYS add this component to the player before any other
class InputBinder;
class Collider;
class PlayerData : public Component
{
private:
	int playerNumber_;
	InputBinder* ib;
public:
	PlayerData(int playerNumber, InputBinder* i) : Component(ComponentType::PlayerData),
		ib(i) {
		playerNumber_ = playerNumber;
		//ib = new PureKeyboardBinder();
	}
	~PlayerData() { ib->setPlayerCol(nullptr); ib = nullptr; };

	void init() override;
	int getPlayerNumber() { return playerNumber_; }
	InputBinder* getBinder() { return ib; }
};
