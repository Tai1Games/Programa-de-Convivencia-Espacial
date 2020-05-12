#include "ClientState.h"
#include <iostream>

ClientState::ClientState(char* host) {
	if (SDLNet_Init() < 0) {
		std::cout << "Algo salió mal :c" << std::endl;
		throw;
	}

	if (SDLNet_ResolveHost(&hostIp_, host, 2000) < 0) {
		std::cout << "Error al resolver host" << std::endl;
		throw;
	}

	hostConnection_ = SDLNet_TCP_Open(&hostIp_);
	if (!hostConnection_) {
		std::cout << "Error al conectar con host" << std::endl;
		throw;
	}

	//revisar si nos hemos conectado

	socketSet_ = SDLNet_AllocSocketSet(1);
	SDLNet_TCP_AddSocket(socketSet_, hostConnection_);
}

void ClientState::init() {

}

void ClientState::update()
{

}

void ClientState::render()
{
	while (!doneReceiving_) {
		if (SDLNet_CheckSockets(socketSet_, 0) > 0) {
			if (SDLNet_SocketReady(hostConnection_)) {
				if (SDLNet_TCP_Recv(hostConnection_, buffer, 1) <= 0) {
					std::cout << "error al recibir datos" << std::endl;
					throw;
				}
				switch (buffer[0]) {
				case 0:
					doneReceiving_ = true;
					break;
				case 2:
					//renderizar sprite
					SDLNet_TCP_Recv(hostConnection_, buffer, 16);
					renderBufferTexture();
					break;
				}
			}
		}
	}
}

void ClientState::renderBufferTexture() {
	//|idTex|x|x|y|y|w|w|h|h|rot|rot|frame| = 12 
	//|idTex|x|x|y|y|w|w|h|h|xc|xc|yc|yc|wc|wc|hc|hc|rot|rot|frame| = 20
}

void ClientState::handleInput()
{

}
