#pragma once
#include "GameState.h"
#include "InputBinder.h"
#include "checkML.h"
#include <vector>

// todavía falta darle un owner a este State, para que sólo lo maneje el server
struct PlayerLobbyInfo {
	int id;
	InputBinder* inputBinder = nullptr;
	int ctrlId = -1;
	int kbId = -1;
	int kbmId = -1;
	PlayerLobbyInfo(int i, InputBinder* ib) {
		id = i; inputBinder = ib;

	};
	//se llama cuando no toca, hay que ver como recoger la basura
	//~PlayerLobbyInfo() {
	//	delete inputBinder;
	//};
};

class LobbyState : public GameState
{
private:
	void clear() {
		// CSI[2J clears screen, CSI[H moves the cursor to top-left corner
		std::cout << "\x1B[2J\x1B[H";
	}
protected:
	InputHandler* ih_ = nullptr;
	std::vector<PlayerLobbyInfo> joinedPlayers_;
	bool joinedGamepads_[4]; //indica los gamepads que se ha unido
	bool joinedKb_[2]; //indica los teclados que se han unido
	bool joinedMouse_; //indica si se ha unido el mouse

	void renderPlayerLobbyInfo(PlayerLobbyInfo* playerInfo);
public:
	LobbyState() {};
	~LobbyState() {};
	void init() override;
	void handleInput() override;
	void update() override;
	void render() override;
};

