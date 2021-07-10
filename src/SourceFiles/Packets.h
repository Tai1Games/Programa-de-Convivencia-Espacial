#pragma once

// -----------------------ONLINE PACKETS-----------------------------------------
#include "Serializable.h"
#include <algorithm>

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
public:
	const static int SIZE = (sizeof(char) + sizeof(unsigned char) * 4 + sizeof(short) * 5 + sizeof(float) * 3);

	char packetId = 'S'; //Sprite
	unsigned char textureId = 0;
	short posX = 0, posY = 0;
	float velX = 0, velY = 0, angVel = 0; 
	short width = 0, height = 0;
	short rotationDegrees = 0;
	unsigned char frameNumberX = 0, frameNumberY = 0;
	unsigned char flip = 0;

public:
	SpritePacket(){};
	SpritePacket(unsigned char tId, short posx, short posy, short w, short h,
	unsigned char flip = 0,
	float velx = 0, float vely = 0, float rotVel = 0, short rotDeg = 0,
	unsigned char fX = 0, unsigned char fY = 0);

	void to_bin() override;
	int from_bin(char* bobj) override;
};

class AudioPacket : public Serializable
{
public:
	const static int SIZE = sizeof(char) * 3 + sizeof(bool);

	char packetId = 'A'; //Audio
	bool isMusic = false;
	char soundId = 0;
	char nLoops = 0; //cambiar en cliente

public:
	AudioPacket(){};
	AudioPacket(bool ismsic, char id, char loops = 0);
	
	void to_bin() override;
	int from_bin(char* bobj) override;
};

class PlayerInfoPacket : public Serializable
{
public:
	const static int SIZE = sizeof(char) * 5;
	
	char packetId = 'P';
	char numberOfPlayers = 0;
	char player1Info = 0;
	char player2Info = 1;
	char player3Info = 2;

public:
	PlayerInfoPacket(){};
	PlayerInfoPacket(char num, char p1, char p2, char p3);

	void to_bin() override;
	int from_bin(char* bobj) override;

	void updatePlayersId(int amount){
		player1Info += amount;
		player2Info += amount;
		player3Info += amount;
	}
};

// class VerificationPacket : public Serializable
// {
// public:
// 	const static int SIZE = sizeof(uint32_t) + sizeof(unsigned int);

// 	char packetId = 'V';
// 	uint32_t id_ = 0;

// public:
// 	VerificationPacket(uint32_t id) : 
// 	packetId('V'),
// 	id_(id) {};

// 	void to_bin() override;
// 	int from_bin(char* bobj) override;
// };

#pragma pack(pop)

class InputPacket : public Serializable
{
public:
	const static int SIZE = sizeof(char) * 3 + sizeof(bool) * 11 + sizeof(float) * 2 + sizeof(unsigned int);

	char packetId = 'I'; //Input
	char playerId = 0;
	unsigned int instant = 0;
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
	InputPacket() {};
	InputPacket(char packtId, char id, unsigned int inst, bool hG = false, bool rG = false, bool pT = false,
	bool pP = false, bool hI = false, bool pI = false, float dirX = 0, float dirY = 0,
	bool rI = false, bool pA = false, bool mF = false, bool mB = false,
	bool pPause = false, bool mM = false);

	void to_bin() override;
	int from_bin(char* bobj) override;
};


using namespace std;

const static int MAX_PACKET_SIZE = max(SpritePacket::SIZE, max(AudioPacket::SIZE, max(PlayerInfoPacket::SIZE, InputPacket::SIZE)));