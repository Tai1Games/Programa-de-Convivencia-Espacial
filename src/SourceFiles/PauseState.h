#pragma once
#include "GameState.h"
#include "Entity.h"
#include "checkML.h"

using namespace std;

enum Buttons {
	Resume = 0,
	Music,
	Effects,
	Exit
};

class InputBinder;
class UIViewer;
class PauseState : public GameState
{
private:
	UIViewer* buttonSelectorImage_ = nullptr;
	UIViewer* musicSliderImage_ = nullptr;
	UIViewer* effectsSliderImage_ = nullptr;
	UIViewer* musicSliderControlImage_ = nullptr;
	UIViewer* effectsSliderControlImage_ = nullptr;
	/*Evita que se mueva varias veces hacia izq/derch al mantener el joystick*/
	bool holdingX_ = false;
	/*Evita que se mueva varias veces hacia arriba/abajo al mantener el joystick*/
	bool holdingY_ = false;
	int ownerPlayerID_ = 0;
	InputBinder* ownerBinder_;
	vector<UIViewer*> btns_;
	/*Indice para el bot�n seleccionado en el vector de botones*/
	int selectedBtn_ = 0;
	int currentMusicVolume_;
	int currentEffectsVolume_;
	int maxMusicVolume_;
	int maxEffectsVolume_;

	int offsetBetweenButtons_;

	Texture* fondo_ = nullptr;

	/*Actualiza la posici�n de la selecci�n y el bot�n seleccionado*/
	void updateSelectedButton();
	/*Actualiza la posici�n del slider y el volumen del sonido*/
	void updateSoundVolume();
	/*Gestiona el input en el Slider*/
	bool handleSlider(int& currentVolumeValue, const int& maxVolumeValue);

	void resumeGame();
public:
	PauseState() : GameState() {};
	~PauseState() {};

	virtual void init();
	virtual void render() override;
	virtual void handleInput();

	void setOwner(int ownerID);
};
