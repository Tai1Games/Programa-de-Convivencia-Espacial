#pragma once
#include "GameState.h"
#include "checkML.h"
#include "Entity.h"
#include "Resources.h"

class InputBinder;
class UIViewer;
class MenuState:
	public GameState
{
private:
	int menuPointer_ = 0; //En que screen del men� est� (0 escogiendo modo, 1 escogiendo mapa)
	int pointers_[2] = { 0, 0 }; //Que seleccion dentro de la screen est�
	bool holdingY_ = false;
	int ownerPlayerID_ = 0;
	InputBinder* ownerPlayerBinder_ = nullptr;

	int tinkyOffset_ = CONST(int, "WINDOW_WIDTH") / 4;

	int xOffset_ = CONST(int, "WINDOW_WIDTH")/3;
	int yOffset_ = CONST(int, "WINDOW_HEIGHT")/9;

	int numberOfRounds_ = 3;

	UIViewer* menuCursor_ = nullptr;
	std::vector<Entity*> texts_ [3];
	vector<pair<GamemodeID, string>>* roundsVector_ = new vector<pair<GamemodeID, string>>();  //vector de rondas

	std::map<int, string> maps_ = { //a�adir aqu� los mapas que se vayan haciendo, tutorial no
		{ 0, "LivingRoom"},
		{ 1, "BoilerRoom"},
		{ 2, "GymRoom"},
		{ 3, "GardenRoom"}
	};

	void updatePointer(int n);
	void updateText();
	void createText();
	void addRound(GamemodeID gMode, string map);

public:
	MenuState(int playerID) : GameState(), ownerPlayerID_(playerID) {};
	virtual ~MenuState() {};

	virtual void init() override;
	virtual void onLoaded() override;
	virtual void handleInput() override;
};

