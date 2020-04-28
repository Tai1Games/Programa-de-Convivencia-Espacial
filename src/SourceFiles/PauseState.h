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
	Viewer* buttonSelectorImage_ = nullptr;
	Viewer* sliderControlImage_ = nullptr;
	/*Evita que se mueva varias veces hacia izq/derch al mantener el joystick*/
	bool holdingX_ = false;
	/*Evita que se mueva varias veces hacia arriba/abajo al mantener el joystick*/
	bool holdingY_ = false;
	int ownerPlayerID_ = 0;
	vector<Viewer*> btns_;
	/*Indice para el botón seleccionado en el vector de botones*/
	int selectedBtn_ = 0;
	int currentMusicVolume_ = CONST(double, "MAX_MUSIC_VOLUME");

	/*Actualiza la posición de la selección y el botón seleccionado*/
	void updateSelectedButton();
	/*Actualiza la posición del slider y el volumen de la música*/
	void updateMusicVolume();

	void resumeGame();
public:
	PauseState() : GameState() {};
	~PauseState(){};

	virtual void init();
	virtual void handleInput();

	void setOwner(int ownerID) { ownerPlayerID_ = ownerID; }
};

