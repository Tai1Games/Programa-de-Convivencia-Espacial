#pragma once

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


struct SpritePacket {
	char packetId = 'S'; //Sprite
	unsigned char textureId;
	short posX;
	short posY;
	short width;
	short height;
	short rotationDegrees = 0;
	unsigned char frameNumberX = 0;
	unsigned char frameNumberY = 0;
	unsigned char flip = 0;
};

struct AudioPacket {
	char packetId = 'A'; //Audio
	bool isMusic;
	char soundId;
	char nLoops = 0; //cambiar en cliente
};

struct PlayerInfoPacket {
	char packetId = 'P';
	char numberOfPlayers;
	char player1Info;
	char player2Info;
	char player3Info;
};

#pragma pack(pop)

struct InputPacket {
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
};
