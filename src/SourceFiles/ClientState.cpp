#include "ClientState.h"
#include "SDL_Game.h"
#include <iostream>

#define us unsigned short
#define uc unsigned char

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
	playerInfoVector_ = SDL_Game::instance()->getStateMachine()->getMatchInfo()->getPlayersInfo();
}

void ClientState::update()
{
	doneReceiving_ = false;
	while (!doneReceiving_) {
		if (SDLNet_CheckSockets(socketSet_, 0) > 0) {
			if (SDLNet_SocketReady(hostConnection_)) {
				if (SDLNet_TCP_Recv(hostConnection_, buffer, 1) <= 0) {
					std::cout << "error al recibir datos" << std::endl;
					throw;
				}
				switch (buffer[0]) {
				case 'A':
					//Audio
					receiveAudio();
					break;
				case 'C':
					connectToServer();
					break;
				case 'F':
					//Finished
					doneReceiving_ = true;
					break;
				case 'M':
					//Musica
					receiveMusic();
					break;
				case 'P':
					//Player ids info
					receivePlayerInfo();
					break;
				case 'S':
					//Sprite
					receiveSprite();
					break;
				}
			}
		}
	}
}

void ClientState::render()
{
	SpritePacket sprite;
	while (!spritesToRender_.empty()) {
		sprite = spritesToRender_.front();
		//SDL_Game::instance()->getTexturesMngr()->getTexture(sprite.textureId)->render({sprite.posX,sprite.posY,sprite.width,sprite.height},sprite.rotationDegrees,sprite.frameNumberX,sprite.frameNumberY,sprite.flip);
		spritesToRender_.pop();
	}
}

void ClientState::receiveSprite() {
	//Ya que se ha recibido el identificador de tipo es SpritePacketSize - 1
	receivedBytes_ = 0;
	int n = 0;
	while (receivedBytes_ < sizeof(SpritePacket) - 1) {
		n = SDLNet_TCP_Recv(hostConnection_, buffer + receivedBytes_, sizeof(SpritePacket) - 1 - receivedBytes_);
		receivedBytes_ += n;
	}

	//id      pos x			pos y		  width	         height		   rot				frameX		     frameY			flip
	spritesToRender_.push({ 'S', buffer[0],(us)buffer[1],(us)buffer[3],(us)buffer[5],(us)buffer[7],(us)buffer[9],(uc)buffer[11],(uc)buffer[12],(uc)buffer[13] });
}


void ClientState::handleInput()
{
	int schar = sizeof(char);
	int sbool = sizeof(bool);
	int sfloat = sizeof(float);
	for (MatchInfo::PlayerInfo* pInfo : *playerInfoVector_) {
		int offset = 0;
		InputPacket pInputPacket = pInfo->inputBinder->getInputPacket();
		buffer[offset] = pInputPacket.packetId;
		offset += schar;
		buffer[offset] = pInfo->playerId;
		offset += schar;
		buffer[offset] = pInputPacket.holdGrab;
		offset += sbool;
		buffer[offset] = pInputPacket.releaseGrab;
		offset += sbool;
		buffer[offset] = pInputPacket.pressThrow;
		offset += sbool;
		buffer[offset] = pInputPacket.pressPick;
		offset += sbool;
		buffer[offset] = pInputPacket.holdImpulse;
		offset += sbool;
		buffer[offset] = pInputPacket.aimDirX;
		offset += sfloat;
		buffer[offset] = pInputPacket.aimDirY;
		offset += sfloat;
		buffer[offset] = pInputPacket.pressImpulse;
		offset += sbool;
		buffer[offset] = pInputPacket.releaseImpulse;
		offset += sbool;
		buffer[offset] = pInputPacket.pressAttack;
		offset += sbool;
		buffer[offset] = pInputPacket.menuForward;
		offset += sbool;
		buffer[offset] = pInputPacket.menuBack;
		offset += sbool;
		buffer[offset] = pInputPacket.pressPause;
		offset += sbool;
		buffer[offset] = pInputPacket.menuMove;

		SDLNet_TCP_Send(hostConnection_, buffer, sizeof(InputPacket));
	}
}


void ClientState::receiveAudio()
{
	SDLNet_TCP_Recv(hostConnection_, buffer, sizeof(AudioPacket) - 1);
	SDL_Game::instance()->getAudioMngr()->playChannel(buffer[0], buffer[1], 0);
}

void ClientState::receiveMusic() {
	SDLNet_TCP_Recv(hostConnection_, buffer, sizeof(AudioPacket) - 1);
	SDL_Game::instance()->getAudioMngr()->playMusic(buffer[0],-1);
}

void ClientState::connectToServer() {
	buffer[0] = 'P';
	buffer[1] = SDL_Game::instance()->getStateMachine()->getMatchInfo()->getNumberOfPlayers();
	for (int i = 0; i < SDL_Game::instance()->getStateMachine()->getMatchInfo()->getNumberOfPlayers(); i++)
		buffer[2 + i] = (char)(*playerInfoVector_)[i]->playerSkin;

	SDLNet_TCP_Send(hostConnection_, buffer, sizeof(PlayerInfoPacket));
	memset(buffer, 0, 2048);
}

void ClientState::receivePlayerInfo() {
	SDLNet_TCP_Recv(hostConnection_, buffer, sizeof(PlayerInfoPacket) - 1);
	for (int i = 0; i < (int)buffer[0]; i++) {
		(*playerInfoVector_)[i]->playerId = (size_t)buffer[i + 1];
	}
	memset(buffer, 0, 2048);
}