#pragma once

#include "SDL_net.h"
#include <string>

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
};

