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

class InputBinder;
class UIViewer;
class PauseState : public GameState
{
private:
	UIViewer* buttonSelectorImage_ = nullptr;
	UIViewer* sliderControlImage_ = nullptr;
	/*Evita que se mueva varias veces hacia izq/derch al mantener el joystick*/
	bool holdingX_ = false;
	/*Evita que se mueva varias veces hacia arriba/abajo al mantener el joystick*/
	bool holdingY_ = false;
	int ownerPlayerID_ = 0;
	InputBinder* ownerBinder_;
	vector<UIViewer*> btns_;
	/*Indice para el bot�n seleccionado en el vector de botones*/
	int selectedBtn_ = 0;
	int currentMusicVolume_ = CONST(double, "MAX_MUSIC_VOLUME");

	/*Actualiza la posici�n de la selecci�n y el bot�n seleccionado*/
	void updateSelectedButton();
	/*Actualiza la posici�n del slider y el volumen de la m�sica*/
	void updateMusicVolume();

	void resumeGame();
public:
	PauseState() : GameState() {};
	~PauseState(){};

	virtual void init();
	virtual void handleInput();

	void setOwner(int ownerID) { ownerPlayerID_ = ownerID; }
};

