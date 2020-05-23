#pragma once
#include <vector>
#include <string>
#include "GameState.h"
#include "checkML.h"
#include "Texture.h"
#include "Constants.h"

class MatchInfo;
class MultiplayerHost;

class GameStateMachine
{
private:
	std::vector<GameState*> states_;

	MatchInfo* matchInfo_ = nullptr;
	MultiplayerHost* mpHost_ = nullptr;

	int currentState_ = -1;

	void update();
	void render();
	void handleInput();
public:
	GameStateMachine();
	virtual ~GameStateMachine();
	/*Cambia al estado pausa con un owner*/
	void setPauseOwner(int ownerID);

	void setMatchInfo(MatchInfo* matchInfo) { matchInfo_ = matchInfo; };
	MatchInfo* getMatchInfo() { return matchInfo_; };

	void changeToState(int state, int gameMode = 0, std::string tileMap = "");
	void transitionToState(int state, int gameMode = 0, std::string tileMap = "");
	void loadState(int state, int gameMode, string tileMap);

	GameState* getCurrentState() const { return ((currentState_ != -1) ? states_[currentState_] : nullptr); };
	GameState* getStateById(int id) const { return ((id < States::NUMBER_OF_STATES) ? states_[id] : nullptr); };
	void deleteState(int state);

	void gameCycle();

	void setMpHost(MultiplayerHost* host);
};
