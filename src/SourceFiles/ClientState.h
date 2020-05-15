#pragma once
#include "GameState.h"
#include "SDL_net.h"
#include "Constants.h"
#include <queue>

/*
* Tipos de mensajes del servidor
* 1 -> Te has conectado correctamente
* 2 -> Lo que sigue es la informacion de un sprite
* 0 -> He acabado de enviar sprites
*/

class ClientState :
	public GameState
{
private:
	IPaddress hostIp_;
	TCPsocket hostConnection_;
	SDLNet_SocketSet socketSet_;

	bool doneReceiving_ = false;

	//1024 bytes a 16 bytes por sprite = 64 sprites
	//a 12 = 85 sprites
	//a 20 = 51 sprites
	char buffer[2048];
	int receivedBytes_ = 0;

	std::queue<SpritePacket> spritesToRender_;
public:
	ClientState(char* host);
	virtual ~ClientState() { SDLNet_Quit(); };

	virtual void init() override;
	virtual void update() override;
	virtual void render() override;
	virtual void handleInput() override;

	void receiveSprite();
};

