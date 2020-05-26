#pragma once
#include "GameState.h"
#include "checkML.h"
#include "Entity.h"
#include "Resources.h"

class InputBinder;
class UIViewer;
class OnlineMenuState :
	public GameState
{
private:
	int pointer_ = 0; //Que opcion esta seleccionada
	bool holdingY_ = false;
	int ownerPlayerID_ = 0;
	InputBinder* ownerPlayerBinder_ = nullptr;

	int tinkyOffset_ = CONST(int, "WINDOW_WIDTH") / 4;

	int xOffset_ = CONST(int, "WINDOW_WIDTH") / 3;
	int yOffset_ = CONST(int, "WINDOW_HEIGHT") / 9;

	int numberOfRounds_ = 3;

	UIViewer* menuCursor_ = nullptr;
	std::vector<Entity*> texts_;

	void updatePointer(int n);
	void createText();

public:
	OnlineMenuState(int playerID = 0) : GameState(), ownerPlayerID_(playerID) {};
	virtual ~OnlineMenuState() {};

	virtual void init() override;
	virtual void onLoaded() override;
	virtual void handleInput() override;
};

