#pragma once
#include "GameState.h"
#include "checkML.h"
#include "Texture.h"
#include <vector>

class InputBinder;
class InputHandler;

// todav�a falta darle un owner a este State, para que s�lo lo maneje el server
const int MAX_SKINS_PLACEHOLDER = 10;
const int MAX_PLAYERS = 4;
const int MAX_KBPLAYERS = 2;

enum BinderType { ControllerB = 0, KeyboardB, MouseB, UNKNOWN };
struct PlayerLobbyInfo {
	int id;
	InputBinder* inputBinder = nullptr;
	int ctrlId = -1;
	int kbId = -1;
	int kbmId = -1;
	BinderType binderType = UNKNOWN;
	PlayerLobbyInfo(int i, InputBinder* ib) {
		id = i; inputBinder = ib;
	};
	int playerSkin = 0; //no hace nada pero ira cambiando
	bool ready = false;
};

class LobbyState : public GameState
{
private:
protected:
	std::vector<bool>holdingButtons_;
	std::vector<bool>isSkinPicked_;

	int verticalIniPoint_ = 0;
	int horizontalOffset_ = 0;
	int horizontalIniPoint_ = 0;
	int playerIdVerticalOffset_ = 0;
	int pressReadyOffset_ = 0;
	int iconHorizontalOffset_ = 0;
	Texture* playerTexture_ = nullptr;
	Texture* voidTexture_ = nullptr;
	Texture* ctrlTexture_ = nullptr;
	Texture* kbTexture_ = nullptr;
	Texture* mouseTexture_ = nullptr;
	Texture* pressReadyTexture_ = nullptr;
	Texture* readyTexture_ = nullptr;

	InputHandler* ih_ = nullptr;
	std::vector<PlayerLobbyInfo> joinedPlayers_;
	bool joinedGamepads_[4]; //indica los gamepads que se ha unido
	bool joinedKb_[2]; //indica los teclados que se han unido
	bool joinedMouse_; //indica si se ha unido el mouse

	SDL_Keycode joinKbKeys_[2] = { SDLK_w, SDLK_i };
	SDL_Keycode dcKbKeys_[2] = { SDLK_ESCAPE, SDLK_7 };
	SDL_GameControllerButton ctrJoinButton = SDL_CONTROLLER_BUTTON_A, ctrOutButton = SDL_CONTROLLER_BUTTON_B;

	void renderPlayerLobbyInfo(PlayerLobbyInfo* playerInfo, int index);
	void playerOut(std::vector<PlayerLobbyInfo>::iterator it); //elimina un jugador del vector jugadores
	void kbPlayerOut(int index); //desconecta a un jugador de teclado puro
	void mousePlayerOut();  //desconecta al jugador con input de ratob=n
	void changeMouseToKb(); //cambia al jugador con raton por pureKeyboard0
	void changeKbToMouse(); //anade raton al jugador de teclado 0 y desactiva, en caso de haberlo, al segundo jugador de teclado puro
	void ctrlPlayerOut(int index); //desconecta a un jugador con mando
	void handleJoinLeave();
	void handleJoinedPlayers();
	void outDebug();
	void setSkin(PlayerLobbyInfo& player);
public:
	LobbyState() {};
	~LobbyState();
	void init() override;
	void handleInput() override;
	void update() override;
	void render() override;
	bool ready(); //devuelve true si todos los jugadores estan listos
};
