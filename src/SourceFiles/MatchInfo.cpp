#include "MatchInfo.h"
#include "LobbyState.h"

MatchInfo::MatchInfo(const vector<PlayerLobbyInfo>& playerLobbyInfoVector) {
	players_.reserve(playerLobbyInfoVector.size());
	for (PlayerLobbyInfo player : playerLobbyInfoVector) {
		players_.push_back(PlayerInfo(player));
	}
}

MatchInfo::PlayerInfo::PlayerInfo(const PlayerLobbyInfo& info) :
	playerId(info.id),
	inputBinder(info.inputBinder),
	playerSkin(info.playerSkin) {
	matchesWon.reserve(GamemodeID::NUMBER_OF_GAMEMODES);
	for (int i = 0; i < GamemodeID::NUMBER_OF_GAMEMODES; i++)
		matchesWon.push_back(0);
}