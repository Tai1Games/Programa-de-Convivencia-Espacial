#pragma once
#include <string>
#include "checkML.h"


/*Agregar aquí todas las constantes del juego. Cada vez que haya que hacer uso de las constantes,
simplemente hay que hacer #include "Constants.h" en el archivo en el que estemos programando.*/

//Constantes referentes a la ventana del juego
const int WINDOW_HEIGHT = 720;
const int WINDOW_WIDTH =1280;
const std::string WINDOW_NAME = "PCE";
const double MS_PER_FRAME = 1000.0/60.0; //Asumiendo 60fps
const double SECONDS_PER_FRAME = 1.0 / 60.0;

//Constantes Generales
const double PI = 3.14159265359;
const int MAX_MUSIC_VOLUME = 100;

//Constantes Escala Render
const double PIXELS_PER_METER = 40.0;

//Limites de fuerza para impactos
const int lowDamage = 35;
const int mediumDamage = 50;
const int hightDamage = 70;

//Constantes jugador
const int IMPULSE_FROM_OBJECT_FORCE = 50;

//Mano
const int HAND_BODY_OFFSET = 90;
const int HAND_WIDTH = 60;
const int HAND_HEIGHT = 60;

//Constantes referentes al HealthViewer
const int LIFE_DRAW_OFFSET = 10;
const int LIFE_WIDTH = 40;
const int LIFE_HEIGTH = 50;
const int LIFE_MARGIN_H = 30;
const int LIFE_MARGIN_V = 10;


//Constantes referentes a StoacksGameMode
const int STOCK_INITIAL_OFFSET = 15;
const int STOCK_OFFSET = 10;
const int STOCK_WIDTH = 20;
const int STOCK_HEIGTH = 20;

//Modos de juegos
enum States
{
	menu,
	play,
	pause,
	//No toques
	NUMBER_OF_STATES
};