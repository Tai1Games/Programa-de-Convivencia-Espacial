#pragma once

#include "SDL_net.h"
#include <string>
#include "Constants.h"

class MultiplayerHost
{
protected:
	IPaddress hostIp_;
	TCPsocket masterSocket_;
	SDLNet_SocketSet socketSet_;

	TCPsocket clients_[3]; //max 3 jugadores conectados + el host

	std::string hostIPAddress_;

	char buffer[2048];
	int receivedBytes_ = 0;

	std::string getHostIpAddress();
public:
	MultiplayerHost();
	~MultiplayerHost();

	void checkActivity();
	void handlePlayerJoin(int clientNumber);
	void handlePlayerInput(int clientNumber);
	void sendTexture(const SpritePacket& sPacket);
	void sendAudio(const AudioPacket& aPacket);
	void finishSending();
};
