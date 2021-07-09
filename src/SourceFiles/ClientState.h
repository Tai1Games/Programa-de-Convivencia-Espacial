#pragma once
#include "GameState.h"
//#include "SDL_net.h"
#include "Constants.h"
#include "MatchInfo.h"
#include <queue>
#include "Socket.h"

class ClientState :
	public GameState
{
private:
	Socket socket;
	Socket* serverSocket = nullptr;

	char buffer[Socket::MAX_MESSAGE_SIZE];

	std::vector<SpritePacket> spritesToRender_;

	std::vector<MatchInfo::PlayerInfo*>* playerInfoVector_;

	int32_t currentFrameId_ = 0;

	double MS_PER_FRAME;
	int lastUpdateInstant = 0;

	void receiveSprite(char* aux);
	void receiveAudio(char* aux);
	void receivePlayerInfo(char* aux);
	void connectToServer();
public:
	ClientState(const char* addr = "localhost", const char* port = "2000");
	virtual ~ClientState();

	virtual void init() override;
	virtual void update() override;
	virtual void render() override;
	virtual void handleInput() override;
};
