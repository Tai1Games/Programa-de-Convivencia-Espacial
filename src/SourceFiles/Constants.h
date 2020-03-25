#pragma once
#include <string>
#include "checkML.h"


/*Agregar aqu� todas las constantes del juego. Cada vez que haya que hacer uso de las constantes,
simplemente hay que hacer #include "Constants.h" en el archivo en el que estemos programando.*/

//Constantes referentes a la ventana del juego
const int WINDOW_HEIGHT = 720;
const int WINDOW_WIDTH =1280;
const std::string WINDOW_NAME = "PCE";
const double MS_PER_FRAME = 1000.0/60.0; //Asumiendo 60fps
const double SECONDS_PER_FRAME = 1.0 / 60.0;

//Constantes Generales
const double PI = 3.141592653589793238;
const int MAX_MUSIC_VOLUME = 100;

//Constantes Escala Render
const double PIXELS_PER_METER = 60.0;

//UI
const int IMPULSE_SIZE = 100;

//Limites de fuerza para impactos
const int lowDamage = 35;
const int mediumDamage = 50;
const int hightDamage = 70;

//Constantes jugador
const float IMPULSE_GRABBED = 50.0;
const float IMPULSE_FLOATING = 30.0;

//Constantes de armas
const float WEAPON_THROW_SPEED = 100;
const float WEAPON_SPIN_SPEED = 8;

const double STAPLER_DENSITY = 1;
const double STAPLER_FRICTION = 0.1;
const double STAPLER_RESTITUTION = 0.2;
const double STAPLER_LINEAR_DRAG = 0;
const double STAPLER_ANGULAR_DRAG = 0;

const double FLIPFLOP_DENSITY = 1;
const double FLIPFLOP_FRICTION = 0.1;
const double FLIPFLOP_RESTITUTION = 0.2;
const double FLIPFLOP_LINEAR_DRAG = 0;
const double FLIPFLOP_ANGULAR_DRAG = 0;

const double BOUNCINGBALL_DENSITY = 1;
const double BOUNCINGBALL_FRICTION = 0;
const double BOUNCINGBALL_RESTITUTION = 0.99;
const double BOUNCINGBALL_LINEAR_DRAG = 0;
const double BOUNCINGBALL_ANGULAR_DRAG = 0;

const double CONTROLLER_DENSITY = 1;
const double CONTROLLER_FRICTION = 0.1;
const double CONTROLLER_RESTITUTION = 0.2;
const double CONTROLLER_LINEAR_DRAG = 0;
const double CONTROLLER_ANGULAR_DRAG = 0;

//Constantes referentes al HealthViewer
const int LIFE_DRAW_OFFSET = 10;
const int LIFE_WIDTH = 40;
const int LIFE_HEIGTH = 50;
const int LIFE_MARGIN_H = 30;
const int LIFE_MARGIN_V = 10;


//Constantes referentes a StonksGameMode
const int STOCK_INITIAL_OFFSET = 15;
const int STOCK_OFFSET = 10;
const int STOCK_WIDTH = 20;
const int STOCK_HEIGTH = 20;

//Constantes referentes a ControllerGameMode
const double TIME_TO_WIN = 2;

//Constantes de hands

const double HAND_BODY_OFFSET = 120;



//Modos de juegos
enum States
{
	menu,
	play,
	pause,
	//No toques
	NUMBER_OF_STATES
};

enum WeaponID {
	NoWeapon,
	Piedra,
	Pelota,
	Mancuerna,
	Grapadora,
	Extintor,
	Chancla,
	Mando,

	WEAPON_NUMBER
};