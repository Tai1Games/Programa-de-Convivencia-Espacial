#include "MultiplayerHost.h"
#include <vector>
#include <sstream>

MultiplayerHost::MultiplayerHost() {
	if (SDLNet_Init() < 0) {
		throw;
	}

	hostIPAddress_ = getHostIpAddress();

	if (SDLNet_ResolveHost(&hostIp_, nullptr, 2000) < 0)
		throw;

	masterSocket_ = SDLNet_TCP_Open(&hostIp_);
	if (!masterSocket_) throw;

	socketSet_ = SDLNet_AllocSocketSet(4);
	SDLNet_TCP_AddSocket(socketSet_, masterSocket_);

	for (int i = 0; i < 3; i++)
		clients_[i] = nullptr;
}

MultiplayerHost::~MultiplayerHost() {
	SDLNet_Quit();
}

std::string MultiplayerHost::getHostIpAddress() {
	//Thanks Samir for all you've done for us
	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, "ipinfo.io", 80) < 0)
		throw;
	TCPsocket conn = SDLNet_TCP_Open(&ip);
	if (!conn) throw;

	// envia peticion para conseguir la ip
	const char* getter = "GET /ip HTTP/1.0\nHost: ipinfo.io\n\n";
	int size = strlen(getter);
	int result = SDLNet_TCP_Send(conn, getter, size);
	if (result != size) throw;

	// get the response, we assume it is at most bufferSize chars
	const int bufferSize = 255;
	char buffer[bufferSize + 1];
	int read = 0;
	memset(buffer, '\0', bufferSize + 1);
	while (read < bufferSize) {
		result = SDLNet_TCP_Recv(conn, buffer + read, bufferSize);
		if (result < 0) {
			throw;
		}
		else if (result == 0) {
			break;
		}
		else {
			read = read + result;
		}
	}

	// The IP is the last token of the response
	std::vector<std::string> tokens;
	std::stringstream iss(buffer);
	for (std::string s; iss >> s;) {
		tokens.push_back(s);
	}

	SDLNet_TCP_Close(conn);

	
	return tokens.back();
}

void MultiplayerHost::checkActivity() {
	if (SDLNet_CheckSockets(socketSet_, 0) > 0) {

		//Alguien se une
		if (SDLNet_SocketReady(masterSocket_)) {
			TCPsocket client = SDLNet_TCP_Accept(masterSocket_);
		}

		//Revisar actividad de los demas
	}
}