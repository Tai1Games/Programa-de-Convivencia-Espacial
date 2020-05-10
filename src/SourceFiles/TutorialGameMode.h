#pragma once
#include "GameMode.h"
#include "Health.h"
#include "HealthViewer.h"
#include "checkML.h"

class TutorialGameMode : public GameMode
{
private:

	//---------------------
	vector<int> playerStocks_; //Remaining stocks of each player
	vector<Entity*> roundResults_; //Used to determine winner and mode end
	vector<Health*> playersHealth_; //Reference to the Health component of each player
	vector<b2Vec2> playersStocksPos_; //Position in which the Stocks will be drawn FOR EACH DIFFERENT PLAYER.
	vector<InputBinder*> inputBinders_;
	int healtWidth_;
	int maxStocks_;

	//tutorial
	vector<Entity*> weapons_;
	int tutorialPointer_ = 0;
	vector<bool> tutorials_ [Resources::TutorialEnd - Resources::MoveTutorial]; //move, hold, grab, action, throw, death
	vector<Entity*> numberTexts_;
	vector<Entity*> tutorialTexts_;
	Entity* completed_;
	Entity* slash_;
	Entity* numPlayers_;
	int xOffset_ = CONST(int, "WINDOW_WIDTH") / 7.5;
	int yOffset_ = CONST(double, "WINDOW_HEIGHT") / 2.5;
	int xOffsetProgressText_ = CONST(double, "WINDOW_WIDTH") / 3.5 + CONST(double, "WINDOW_WIDTH") / 12;
	int xOffsetProgressCount_ = CONST(double, "WINDOW_WIDTH") / 2.45 + CONST(double, "WINDOW_WIDTH") / 8;
	int xOffsetProgressSlash_ = CONST(double, "WINDOW_WIDTH") / 2.35 +CONST(double, "WINDOW_WIDTH") / 8;
	int xOffsetProgressMax_ = CONST(double, "WINDOW_WIDTH") / 2.25 + CONST(double, "WINDOW_WIDTH") / 8;
	int yOffsetProgress_ = CONST(double, "WINDOW_HEIGHT") / 1.5;
	double scale_ = 0.75;
	int previousProgress_ = 0;

public:
	TutorialGameMode(MatchInfo* mInfo, int stocks = 5);
	~TutorialGameMode();
	virtual void init(PlayState* game);
	virtual void render();
	virtual void update();
	virtual bool onPlayerDead(int id); //Returns false when players runs out of stocks.
};