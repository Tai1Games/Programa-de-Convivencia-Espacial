#pragma once

#include "Entity.h"
#include "checkML.h"
#include "Transform.h"
#include "Texture.h"
#include "Viewer.h"
#include "Health.h"
#include "HealthViewer.h"
#include "InputHandler.h"
#include "Weapon.h"
#include "Hands.h"
#include "Coin.h"

class ObjectFactory
{
private:
public:

	ObjectFactory() {}

	~ObjectFactory(){}

	//Crea una chancla (Podemos pasarle los p�rametros que queramos segun las necesidades del objeto)
	static void makeSlipper(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	//Crea una pelota saltarina (Podemos pasarle los p�rametros que queramos segun las necesidades del objeto)
	static void makeBall(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	//Crea una pelota saltarina (Podemos pasarle los p�rametros que queramos segun las necesidades del objeto)
	static void makeStapler(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	static void makeWall(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	static void makeSpaceJunk(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	static void makeCoin(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, int val);
	//Crea un mando de la tele (espec�fico para el modo Pelea Por El Mando)
	Weapon* makeController(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);
};
