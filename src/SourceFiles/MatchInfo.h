#pragma once
#include "InputBinder.h"
#include "Constants.h"
#include "checkML.h"

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
	size_t numberOfPlayers_;

public:
	MatchInfo(size_t numberOfPlayers) { players_.reserve(numberOfPlayers); };
	MatchInfo(const vector<PlayerLobbyInfo>& playerLobbyInfoVector);

	vector<PlayerInfo>* getPlayersInfo() { return &players_; };

	size_t getNumberOfPlayers() { return numberOfPlayers_; };
	void AddVictory(size_t toPlayer, GamemodeID gameModeWon) { players_[toPlayer].matchesWon[gameModeWon]++; };
};

