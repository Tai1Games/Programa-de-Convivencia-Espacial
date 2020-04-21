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
	int modePointer_ = 0;
	int mapPointer_ = 0;
	int playerPointer_ = 0;
	int menuPointer_ = 0;
	bool holdingY_ = false;
	int ownerPlayerID_ = 0;

	int tinkyOffset_ = CONST(int, "WINDOW_WIDTH") / 4;

	int xOffset_ = CONST(int, "WINDOW_WIDTH")/3;
	int yOffset_ = CONST(int, "WINDOW_HEIGHT")/8;

	Viewer* menuCursor_ = nullptr;
	std::vector<Entity*> texts_;
	int i = Resources::Capitalism; //i y j son para colocar el texto en pantalla
	int j = Resources::SoundText;

	std::map<int, string> maps_ = { //añadir aquí los mapas que se vayan haciendo
		{ 0, "LivingRoom"},
		{ 1, "BoilerRoom"},
		{ 2, "GymRoom"}
	};

	void updatePointer(int n);
	void updateText();

public:
	MenuState(int playerID) : GameState(), ownerPlayerID_(playerID) {};
	~MenuState() {};

	virtual void init();
	virtual void handleInput();
};

