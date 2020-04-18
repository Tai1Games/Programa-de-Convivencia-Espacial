#pragma once
#include <string>
#include "checkML.h"
#include "json.hpp"
#include "checkML.h"

using json = nlohmann::json;

class Constants {
private:
	json data;  //coleccion de datos almacenados como json
	bool initialized_ = false;
public:
	Constants() {};
	Constants(const std::string& load);
	template<typename T>
	T getConstant(const std::string& key) const; //devuelve la constante pedida o su valor por defecto
};

//Estados de juego
enum States
{
	menu,
	play,
	pause,
	//No toques
	NUMBER_OF_STATES
};

enum GamemodeID {
	Capitalism,
	Controller,
	Stocks,
	WiFight,
	Timed,
	NUMBER_OF_GAMEMODES
};

enum WeaponID {
	NoWeapon,
	Piedra,
	Pelota,
	Mancuerna,
	Stapler,
	Extinguisher,
	Slipper,
	Mando,

	WEAPON_NUMBER
};