#include "MatchInfo.h"
#include "LobbyState.h"

MatchInfo::MatchInfo(const vector<PlayerLobbyInfo>& playerLobbyInfoVector) {
	players_.reserve(playerLobbyInfoVector.size());
	for (PlayerLobbyInfo player : playerLobbyInfoVector) {
		players_.push_back(new PlayerInfo(player));
	}
	numberOfPlayers_ = players_.size();
}

MatchInfo::~MatchInfo()
{
	for (PlayerInfo* player : players_) {
		delete player;	player = nullptr;
	}
	players_.clear();
}

MatchInfo::PlayerInfo::PlayerInfo(const PlayerLobbyInfo& info) :
	playerId(info.id),
	inputBinder(info.inputBinder),
	playerSkin(info.playerSkin) {
	matchesWon.reserve(GamemodeID::NUMBER_OF_GAMEMODES);
	for (int i = 0; i < GamemodeID::NUMBER_OF_GAMEMODES; i++)
		matchesWon.push_back(0);
}

void MatchInfo::AddVictory(size_t toPlayer, GamemodeID gameModeWon) {
	players_[toPlayer]->matchesWon[gameModeWon]++;
	currentRoundNumber_++;
	players_[toPlayer]->totalPoints++;
}

pair<GamemodeID, string> MatchInfo::getCurrentRound() {
	if (currentRoundNumber_ < rounds_->size())
		return (*rounds_)[currentRoundNumber_];
	else
		return { GamemodeID::NUMBER_OF_GAMEMODES,"" };
}