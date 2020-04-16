#pragma once
#include "Entity.h"
#include "checkML.h"

class EntityManager;
class Weapon;
class FireBallPool;

class ObjectFactory
{
public:
	ObjectFactory() {}

	~ObjectFactory() {}

	//Crea una chancla (Podemos pasarle los p�rametros que queramos segun las necesidades del objeto)
	static void makeSlipper(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	//Crea una pelota saltarina (Podemos pasarle los p�rametros que queramos segun las necesidades del objeto)
	static void makeBall(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	//Crea una grapadora (Podemos pasarle los p�rametros que queramos segun las necesidades del objeto)
	static void makeStapler(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	static void makeExtinguisher(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	static void makeWall(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	static void makeSpaceJunk(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	static void makeFireball(Entity* e,EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos);
	
	static Entity* createBoiler(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos);
	//Crea un mando de la tele (espec�fico para el modo Pelea Por El Mando)
	static Weapon* makeController(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);
	
	static void makeDumbbell(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	static void makePad(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);
	
	static void makeCoin(Entity* e, EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, int val);
	
	static Entity* createRoomba(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos);

	static Entity* makeBoilerButton(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, bool inc_dec);

};
