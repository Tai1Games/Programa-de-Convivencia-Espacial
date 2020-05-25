#pragma once
#include "GameState.h"
#include "SDL_net.h"
#include "Constants.h"
#include "MatchInfo.h"
#include <queue>

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

	std::vector<MatchInfo::PlayerInfo*>* playerInfoVector_;

	void receiveSprite();
	void receiveAudio();
	void connectToServer();
	void receivePlayerInfo();
public:
	ClientState(char* host);
	virtual ~ClientState() { SDLNet_Quit(); };

	virtual void init() override;
	virtual void update() override;
	virtual void render() override;
	virtual void handleInput() override;
};

