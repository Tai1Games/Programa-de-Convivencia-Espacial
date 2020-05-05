#pragma once
#include "InputBinder.h"
#include "Constants.h"

struct PlayerLobbyInfo;

class MatchInfo
{
	struct PlayerInfo {
		PlayerInfo(const PlayerLobbyInfo& info);

		size_t playerId = 0;
		InputBinder* inputBinder = nullptr;
		size_t playerSkin = 0;
		vector<size_t> matchesWon;
	};

private:
	vector<PlayerInfo> players_;

public:
	MatchInfo(size_t numberOfPlayers) { players_.reserve(numberOfPlayers); };
	MatchInfo(const vector<PlayerLobbyInfo>& playerLobbyInfoVector);

	vector<PlayerInfo>* getPlayersInfo() { return &players_; };

	void AddVictory(size_t toPlayer, GamemodeID gameModeWon) { players_[toPlayer].matchesWon[gameModeWon]++; };
};

