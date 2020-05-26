#pragma once
#include "GameState.h"
#include "Entity.h"
#include "checkML.h"

using namespace std;

class InputBinder;
class UIViewer;
class OptionsMenuState : public GameState
{
private:
	enum Button {
		Music=0,
		Effects,
		Exit
	};

	UIViewer* buttonSelectorImage_ = nullptr;
	UIViewer* musicSliderImage_ = nullptr;
	UIViewer* effectsSliderImage_ = nullptr;
	UIViewer* musicSliderControlImage_ = nullptr;
	UIViewer* effectsSliderControlImage_ = nullptr;
	/*Evita que se mueva varias veces hacia izq/derch al mantener el joystick*/
	bool holdingX_ = false;
	/*Evita que se mueva varias veces hacia arriba/abajo al mantener el joystick*/
	bool holdingY_ = false;
	InputBinder* ownerBinder_;
	vector<UIViewer*> btns_;
	/*Indice para el bot�n seleccionado en el vector de botones*/
	int selectedBtn_ = 0;

	//Volúmenes de los canales
	int currentMusicVolume_ = 0;
	int currentEffectsVolume_ = 0;
	int maxMusicVolume_ = 0;
	int maxEffectsVolume_ = 0;
	//Separación entre los botones
	int offsetBetweenButtons_ = 0;

	Texture* fondo_ = nullptr;

	/*Actualiza la posici�n de la selecci�n y el bot�n seleccionado*/
	void updateSelectedButton();

	/*Actualiza la posici�n del slider y el volumen del sonido*/
	void updateSoundVolume();

	/*Gestiona el input en el Slider*/
	bool handleSlider(int& currentVolumeValue, const int& maxVolumeValue);

public:
	OptionsMenuState() : GameState() {};
	~OptionsMenuState();

	virtual void init();
	virtual void render() override;
	virtual void handleInput();
};


