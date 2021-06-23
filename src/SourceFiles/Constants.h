#pragma once

#include <string>
#include "checkML.h"
#include "json.hpp"
#include "checkML.h"
#include "Serializable.h"

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

//Mathz
const double PI = 3.14159265358979323846264338327950288;
const int FRAMES_PER_SECOND = 60;

//Pools
const int COIN_POOL_SIZE = 140;
const int FIREBALL_POOL_SIZE = 5;
const int TOMATO_POOL_SIZE = 10;
const int BANANA_POOL_SIZE = 5;
const int CONFETTI_POOL_SIZE = 5;
const int STAPLER_POOL_SIZE = 5;
const int BODY_POOL_SIZE = 5;

//Estados de juego
enum States
{
	menu,
	play,
	pause,
	midGame,
	transition,
	lobby,
	onlineMenu,
	client,
	playableMenu,
	credits,
	endGame,
	options,
	//No toques
	NUMBER_OF_STATES
};

enum GamemodeID {
	Capitalism,
	Controller,
	Stocks,
	WiFight,
	Timed,
	Tutorial,
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
	Tomato,
	Banana,
	Confetti,

	WEAPON_NUMBER
};

// no s� por qu� peta al hacer un array de strings jorge suspenso
/*std::string mapNames[] = {
	"LivingRoom",
	"Gym",
	"BoilerRoom"
};

enum MapID {
	LivingRoom,
	Gym,
	BoilerRoom,
	//Menu,
	//Garden,
	//Kitchen,
	//Entrance,

	// No toques
	NUMBER_OF_MAPS
};*/

/*
Identificadores de paquetes
A -> Audio
C -> Conectado correctamente
I -> Input
L -> Error, el servidor no puede recibir tantos jugadores
F -> Final de stream de paquetes
S -> Sprite
P -> Informacion de jugadores
	- Si lo envía el cliente indica el numero de jugadores que tiene
	- Si lo envía el servidor indica la id de los jugadores para el cliente en orden
M -> Musica
*/
#pragma pack(push,2)

//Lo mejor es asegurarse de que los elementos que son multiplos de dos vayan en su propia palabra
//Con la instruccion que tenemos queda así, que es la manera mas eficiente y evita errores
/*
	|char|char|
	|  short  |
	|  short  |
*/

class SpritePacket : public Serializable
{
private:
	char packetId = 'S'; //Sprite
	unsigned char textureId;
	short posX, posY;
	short velX, velY;
	short width, height;
	short rotationDegrees = 0;
	unsigned char frameNumberX = 0;
	unsigned char frameNumberY = 0;
	unsigned char flip = 0;

public:
	SpritePacket(unsigned char tId, short posx, short posy, short w, short h,
	unsigned char flip = 0,
	short velx = 0, short vely = 0, short rotDeg = 0,
	unsigned char fX = 0, unsigned char fY = 0) :
	packetId('S'),
	textureId(tId),
	posX(posx),
	posY(posy),
	velX(velx),
	velY(vely),
	width(w),
	height(h),
	rotationDegrees(rotDeg),
	frameNumberX(fX),
	frameNumberY(fY) {

	}
};

class AudioPacket : public Serializable
{
private:
	char packetId = 'A'; //Audio
	bool isMusic;
	char soundId;
	char nLoops = 0; //cambiar en cliente

public:
	AudioPacket(bool ismsic, char id, char loops = 0) :
	packetId('A'),
	isMusic(ismsic),
	soundId(id),
	nLoops(loops) {

	}
};

class PlayerInfoPacket : public Serializable
{
private:
	char packetId = 'P';
	char numberOfPlayers;
	char player1Info;
	char player2Info;
	char player3Info;

public:
	PlayerInfoPacket(char num, char p1, char p2, char p3) : 
	packetId('P'),
	numberOfPlayers(num),
	player1Info(p1),
	player2Info(p2),
	player3Info(p3)
};

#pragma pack(pop)

class InputPacket : public Serializable
{
private:
	char packetId = 'I'; //Input
	char playerId;
	bool holdGrab = false;
	bool releaseGrab = false;
	bool pressThrow = false;
	bool pressPick = false;
	bool holdImpulse = false;
	bool pressImpulse = false;
	float aimDirX = 0;
	float aimDirY = 0;
	bool releaseImpulse = false;
	bool pressAttack = false;
	bool menuForward = false;
	bool menuBack = false;
	bool pressPause = false;
	char menuMove = false;

public:
	InputPacket(char id,
	bool hG = false, bool rG = false,
	bool pT = false, bool pP = false,
	bool hI = false, bool pI = false,
	float dirX = 0, float dirY = 0,
	bool rI = false, bool pA = false,
	bool mF = false, bool mB = false,
	bool pPause = false, bool mM = false
	) :
	packetId('I'),
	playerId(id),
	holdGrab(hG),
	releaseGrab(rG),
	pressThrow(pT),
	pressPick(pP),
	holdImpulse(hI),
	pressImpulse(pI),
	aimDirX(dirX), aimDirY(dirY),
	releaseImpulse(rI),
	pressAttack(pA),
	menuForward(mF),
	menuBack(mB),
	pressPause(pPause),
	menuMove(mM)
	{}

};
