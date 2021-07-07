#include "MultiplayerHost.h"
#include "SDL_Game.h"
#include "MatchInfo.h"
#include <vector>
#include <sstream>
#include <iostream>

MultiplayerHost::MultiplayerHost() : MultiplayerHost(2000) {
}


MultiplayerHost::MultiplayerHost(int port)
{
	hostIPAddress_ = getHostIpAddress();
	std::cout << "IP del host es: " << hostIPAddress_ << std::endl;

	socket = new Socket(hostIPAddress_.c_str(), std::to_string(port).c_str());
	init();
}

MultiplayerHost::MultiplayerHost(char* addr, char* port)
{
	socket = new Socket(addr, port);
	init();
}

void MultiplayerHost::init()
{
	if (!socket->correct()) {
		throw std::runtime_error("Socket initialization failed");
	}
	socket->bind();

	for (int i = 0; i < 3; i++)
		clients_[i] = nullptr;

	buffer = (char*)malloc(MAX_PACKET_SIZE);
	memset(&message, 0, MAX_PACKET_SIZE);
}

MultiplayerHost::~MultiplayerHost() {
	delete socket;
	socket = nullptr;
}

// este método hace uso de SDL_Net porque poco o nada tiene
// que ver con el resto del proyecto.
std::string MultiplayerHost::getHostIpAddress()
{
	if (SDLNet_Init() < 0) {
		throw std::runtime_error("Couldn't start SDLNet");
	}

	//Thanks Samir for all you've done for us
	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, "ipinfo.io", 80) < 0)
		throw std::runtime_error("Couldn't resolve host");
	TCPsocket conn = SDLNet_TCP_Open(&ip);
	if (!conn) throw std::runtime_error("Couldn't open TCP conn");

	// envia peticion para conseguir la ip
	const char* getter = "GET /ip HTTP/1.0\nHost: ipinfo.io\n\n";
	int size = strlen(getter);
	int result = SDLNet_TCP_Send(conn, getter, size);
	if (result != size) throw;

	// get the response, we assume it is at most bufferSize chars
	const int bufferSize = 255;
	char auxBuffer[bufferSize + 1];
	int read = 0;
	memset(auxBuffer, '\0', bufferSize + 1);
	while (read < bufferSize) {
		result = SDLNet_TCP_Recv(conn, auxBuffer + read, bufferSize);
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
	std::stringstream iss(auxBuffer);
	for (std::string s; iss >> s;) {
		tokens.push_back(s);
	}

	SDLNet_TCP_Close(conn);

	SDLNet_Quit();

	return tokens.back();
}

void MultiplayerHost::checkActivity()
{
	if (SDLNet_CheckSockets(socketSet_, 0) > 0)
	{
		//Alguien se une
		if (SDLNet_SocketReady(masterSocket_)) {
			TCPsocket client = SDLNet_TCP_Accept(masterSocket_);

			int clientPlace = 0;
			while (clientPlace < 3 && clients_[clientPlace] != nullptr)
				clientPlace++;

			if (clientPlace < 3) {
				//std::cout << "Jugador conectado, id asignada: " << clientPlace << std::endl;
				clients_[clientPlace] = client;
				SDLNet_TCP_AddSocket(socketSet_, client);
				SDLNet_TCP_Send(client, "C", 9);
			}
			else {
				SDLNet_TCP_Send(client, "L", 1);
			}
		}

		//Revisar actividad de los demas
		for (int i = 0; i < 3; i++)
		{
			if (clients_[i] != nullptr && SDLNet_SocketReady(clients_[i]))
			{
				memset(buffer, 0, MAX_PACKET_SIZE);

				receivedBytes_ = SDLNet_TCP_Recv(clients_[i], buffer, 1);
				if (receivedBytes_ <= 0) {
					//Usuario ha desconectado o perdido conexion
					SDLNet_TCP_Close(clients_[i]);
					SDLNet_TCP_DelSocket(socketSet_, clients_[i]);
					clients_[i] = nullptr;
				}
				else {
					//Tratamiento de mensajes de los jugadores
					switch (buffer[0]) {
					case 'P':
						handlePlayerJoin(i);
						break;
					case 'I':
						//Nos llega input del jugador
						handlePlayerInput(i);
						break;
					}
				}
			}
		}
	}
}


void MultiplayerHost::handlePlayerJoin(int clientNumber) 
{
	Socket* clientSocket = clients_[clientNumber].get();

	PlayerInfoPacket piPacket;
	if (socket->recv(piPacket, clientSocket) != 0)
	{
		std::cout << "Couldn't recv in handlePlayerJoin";
		clients_[clientNumber] = nullptr;
		return;
	}

	//Revisamos si caben el numero que quieren entrar
	int nStartingPlayers = SDL_Game::instance()->getStateMachine()->getMatchInfo()->getNumberOfPlayers();
	
	if (piPacket.numberOfPlayers + nStartingPlayers < 5)
	{
		//Aceptamos
		std::vector<MatchInfo::PlayerInfo*>* playersVector = SDL_Game::instance()->getStateMachine()->getMatchInfo()->getPlayersInfo();
		for (int i = 0; i < piPacket.numberOfPlayers; i++)
		{
			playersVector->push_back(new MatchInfo::PlayerInfo(SDL_Game::instance()->getStateMachine()->getMatchInfo()->getNumberOfPlayers(), new ClientBinder(), buffer[i + 1]));
			SDL_Game::instance()->getStateMachine()->getMatchInfo()->updateNumberOfPlayers();
		}

		//Enviamos de vuelta al cliente la informacion de los jugadores
		piPacket.updatePlayersId(nStartingPlayers);
		piPacket.to_bin();
		char* aux = piPacket.data();

		socket->send("L", *clientSocket, 1);
	}
	else { //Ya hay demasiados jugadores, avisamos que estamos llenos y tiramos la conexion

		socket->send("L", *clientSocket, 1);
		clients_[clientNumber] = nullptr;
	}
}

void MultiplayerHost::handlePlayerInput(int clientNumber)
{
	//receivedBytes_ = SDLNet_TCP_Recv(clients_[clientNumber], buffer, InputPacket::SIZE);

	InputPacket inputPacket;
	Socket* cSocket = clients_[clientNumber].get();
	if(socket->recv(inputPacket, cSocket) == -1) return;

	std::vector<MatchInfo::PlayerInfo*>* playersVector = SDL_Game::instance()->getStateMachine()->getMatchInfo()->getPlayersInfo();
	(*playersVector)[inputPacket.playerId]->inputBinder->syncInput(inputPacket);
}

void MultiplayerHost::addFrameId(uint32_t id)
{	
	memcpy(messagePtr, id, sizeof(uint32_t));
	messagePtr++;
}

void MultiplayerHost::addTexture(SpritePacket& sPacket)
{
	sPacket.to_bin();
	memcpy(messagePtr, sPacket.data(), sPacket.size());
	messagePtr += sPacket.size();
}

void MultiplayerHost::addAudio(AudioPacket& aPacket)
{
	aPacket.to_bin();
	memcpy(messagePtr, aPacket.data(), aPacket.size());
	messagePtr += aPacket.size();
}

void MultiplayerHost::finishSending()
{
	memcpy(messagePtr, "\0", 1);
	messagePtr++;
}

void MultiplayerHost::send()
{
	finishSending();

	for (int i = 0; i < 3; i++) {
		if (clients_[i] != nullptr) {
			clients_[i].get()->send(message, *clients_[i].get());
		}
	}
}


