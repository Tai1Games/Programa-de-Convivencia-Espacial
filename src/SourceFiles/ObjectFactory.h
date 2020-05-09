#pragma once
#include "Entity.h"
#include "checkML.h"

class EntityManager;
class Weapon;
class FireBallPool;
class BulletPool;

class ObjectFactory
{
public:
	ObjectFactory() {}

	~ObjectFactory() {}

	//Crea una chancla (Podemos pasarle los p�rametros que queramos segun las necesidades del objeto)
	static Entity* makeSlipper(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	//Crea una pelota saltarina (Podemos pasarle los p�rametros que queramos segun las necesidades del objeto)
	static Entity* makeBall(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	//Crea una grapadora (Podemos pasarle los p�rametros que queramos segun las necesidades del objeto)
	static Entity* makeStapler(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size, BulletPool* bp);

	static Entity* makeExtinguisher(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	static Entity* makeTomato(Entity* e, EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos);

	static Entity* makeWall(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	static Entity* makePipe(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size, float rotation);

	static Entity* makeSpaceJunk(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	static Entity* makeFireball(Entity* e,EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos);
	
	static Entity* makeBoiler(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos);
	//Crea un mando de la tele (espec�fico para el modo Pelea Por El Mando)
	static Weapon* makeController(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);
	
	static Entity* makeDumbbell(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	static Entity* makePad(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);
	
	static Entity* makeCoin(Entity* e, EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, int val);
	
	static Entity* makeRoomba(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos);

	static Entity* makeBoilerButton(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, bool inc_dec);

	static Entity* makeTreadmill(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos);

	static Entity* makeCarnivorousePlant(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	static Entity* makeBanana(Entity* e, EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, BulletPool* bp);

	static Entity* makeBullet(Entity* e, EntityManager* entityManager, b2World* physicsWorld);
};
