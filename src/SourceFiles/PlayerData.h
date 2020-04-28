#pragma once
#include "Component.h"
#include "checkML.h"
#include "InputBinder.h"
#include "Entity.h"

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
		//ib = new PureKeyboardBinder();
	}
	~PlayerData() { delete ib; };

	int getPlayerNumber() { return playerNumber_; }
	InputBinder* getBinder() { return ib; }

	void init() override {
		//se tiene que inicializar aquí para poder coger el collider
		int gId = SDL_Game::instance()->getInputHandler()->getFreeGamePad();
		cout << "Player " << playerNumber_ << " got controller " << gId << endl;
		ib = new ControllerBinder(gId);
	}
};

