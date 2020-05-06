#pragma once
#include "GameState.h"
#include "checkML.h"
#include "Entity.h"
#include "Resources.h"

class Viewer;
class MenuState:
	public GameState
{
private:
	int menuPointer_ = 0;
	int pointers_[3] = { 0,0,0 };
	bool holdingY_ = false;
	int ownerPlayerID_ = 0;
	
	int tinkyOffset_ = CONST(int, "WINDOW_WIDTH") / 4;

	int xOffset_ = CONST(int, "WINDOW_WIDTH")/3;
	int yOffset_ = CONST(int, "WINDOW_HEIGHT")/9;

	Viewer* menuCursor_ = nullptr;
	std::vector<Entity*> texts_ [3];

	std::map<int, string> maps_ = { //añadir aquí los mapas que se vayan haciendo, tutorial no
		{ 0, "LivingRoom"},
		{ 1, "BoilerRoom"},
		{ 2, "GymRoom"},
		{ 3, "GardenRoom"}
	};

	void updatePointer(int n);
	void updateText(int previous);
	void createText();

public:
	MenuState(int playerID) : GameState(), ownerPlayerID_(playerID) {};
	virtual ~MenuState() {};

	virtual void init() override;
	virtual void onLoaded() override;
	virtual void handleInput() override;
};

