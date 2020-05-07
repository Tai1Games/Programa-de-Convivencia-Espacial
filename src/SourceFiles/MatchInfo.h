#pragma once
#include "InputBinder.h"
#include "Constants.h"
#include "checkML.h"

struct PlayerLobbyInfo;

class MatchInfo
{
public:
	struct PlayerInfo {
		PlayerInfo(const PlayerLobbyInfo& info);
		~PlayerInfo() { delete inputBinder; };

		size_t playerId = 0;
		InputBinder* inputBinder = nullptr;
		size_t playerSkin = 0;
		vector<size_t> matchesWon;
	};
private:
	vector<PlayerInfo*> players_;	
	size_t numberOfPlayers_;

	vector<std::pair<GamemodeID, string>>* rounds_ = nullptr;
	size_t numberOfRounds_;
	size_t currentRoundNumber_=0;
public:

	MatchInfo(size_t numberOfPlayers) { players_.reserve(numberOfPlayers); };
	MatchInfo(const vector<PlayerLobbyInfo>& playerLobbyInfoVector);

	void setRounds(vector<pair<GamemodeID, string>>* roundsVector) { rounds_ = roundsVector; numberOfRounds_ = (*rounds_).size(); };

	vector<PlayerInfo*>* getPlayersInfo() { return &players_; };

	pair<GamemodeID, string> getCurrentRound();
	size_t getCurrentRoundNumber() { return currentRoundNumber_; };
	size_t getNumberOfRounds() { return numberOfRounds_; };
	size_t getNumberOfPlayers() { return numberOfPlayers_; };
	void AddVictory(size_t toPlayer, GamemodeID gameModeWon);
};
