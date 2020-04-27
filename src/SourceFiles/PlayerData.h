#pragma once
#include "Component.h"
#include "checkML.h"
#include "InputBinder.h"

//Contains data needed by Player-related components
//ALWAYS add this component to the player before any other
class PlayerData : public Component
{
private:
	int playerNumber_;
	InputBinder* ib;
public:
	PlayerData(int playerNumber) : Component(ComponentType::PlayerData) {
		playerNumber_ = playerNumber;
		int gId = SDL_Game::instance()->getInputHandler()->getFreeGamePad();
		cout << "Player " << playerNumber << " got controller " << gId << endl;
		ib = new PureKeyboardBinder(1);
		//ib = new PureKeyboardBinder();
	}
	~PlayerData() { delete ib; };

	int getPlayerNumber() { return playerNumber_; }
	InputBinder* getBinder() { return ib; }
};

