#pragma once
#include "GameState.h"
#include "InputBinder.h"
#include <vector>

// todavía falta darle un owner a este State, para que sólo lo maneje el server
struct PlayerInfo {
	int id;
	InputBinder* inputBinder;
	int ctrlId = -1;
	int kbId = -1;
	int kbmId = -1;
	PlayerInfo(int i, InputBinder* ib) {
		id = i; inputBinder = ib;

	};
	~PlayerInfo() {
		delete inputBinder;
	};
};

class LobbyState : public GameState
{
protected:
	InputHandler* ih_;
	std::vector<PlayerInfo> joinedPlayers_;
	bool joinedGamepads_[4]; //indica los gamepads que se ha unido
public:
	LobbyState() {};
	~LobbyState() {};
	void init() override;
	void handleInput() override;
};

