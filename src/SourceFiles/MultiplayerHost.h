#pragma once

#include "SDL_net.h"
#include <string>
#include "Constants.h"
#include "Socket.h"

class MultiplayerHost
{
protected:

	std::unique_ptr<Socket> clients_[3];	//max 3 jugadores conectados + el host
	Socket* socket = nullptr;

	std::string hostIPAddress_;
	
	int receivedBytes_ = 0;

	char* buffer;
	
	char message[MAX_PACKET_SIZE];
	char* messagePtr = &message[0];

	std::string getHostIpAddress();

public:
	MultiplayerHost();
	MultiplayerHost(int port);
	MultiplayerHost(char* addr, char* port);
	void init();
	~MultiplayerHost();

	void checkActivity();
	void handlePlayerJoin(int clientNumber);
	void handlePlayerInput(int clientNumber);
	void addTexture(SpritePacket& sPacket);
	void addAudio(AudioPacket& aPacket);
	void send();
	void finishSending();
};
