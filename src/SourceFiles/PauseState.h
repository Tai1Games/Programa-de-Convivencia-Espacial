#pragma once
#include "GameState.h"
#include "Entity.h"
#include "checkML.h"

using namespace std;

enum Buttons {
	Resume = 0,
	Sound,
	Exit
};

class Viewer;
class PauseState : public GameState
{
private:
	Viewer* onBtnImage_ = nullptr;
	Viewer* sliderControlImage_ = nullptr;
	/*Evita que se mueva varias veces hacia arriba/abajo al mantener el joystick*/
	bool holding_ = false;
	int ownerPlayerID_ = 0;
	vector<Viewer*> btns_;
	/*Indice para el botón seleccionado en el vector de botones*/
	int selectedBtn_ = 0;
public:
	PauseState() : GameState() {};
	~PauseState(){};

	void setOwner(int ownerID) { ownerPlayerID_ = ownerID; }

	virtual void init();
	virtual void handleInput();
	/*Actualiza la posición de la selección*/
	void updateSelection();
};

