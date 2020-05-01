#pragma once
#include "GameState.h"
#include "InputBinder.h"
#include "checkML.h"
#include <vector>

// todav�a falta darle un owner a este State, para que s�lo lo maneje el server
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
	void clear2();
protected:
	int maxPlayers_ = 4;
	int verticalIniPoint_ = 0;
	int horizontalOffset_ = 0;
	int horizontalIniPoint_ = 0;
	int playerIdVerticalOffset_ = 0;
	int iconHorizontalOffset_ = 0;
	Texture* playerTexture_ = nullptr;
	Texture* voidTexture_ = nullptr;
	Texture* ctrlTexture_ = nullptr;
	Texture* kbTexture_ = nullptr;
	Texture* mouseTexture_ = nullptr;

	InputHandler* ih_ = nullptr;
	std::vector<PlayerLobbyInfo> joinedPlayers_;
	bool joinedGamepads_[4]; //indica los gamepads que se ha unido
	bool joinedKb_[2]; //indica los teclados que se han unido
	bool joinedMouse_; //indica si se ha unido el mouse

	void renderPlayerLobbyInfo(PlayerLobbyInfo* playerInfo, int index);
	void playerOut(std::vector<PlayerLobbyInfo>::iterator it);
	void kbPlayerOut(int index);
	void ctrlPlayerOut(int index);
public:
	LobbyState() {};
	~LobbyState();
	void init() override;
	void handleInput() override;
	void update() override;
	void render() override;
};

