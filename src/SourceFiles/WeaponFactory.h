#pragma once

#include "Entity.h"

class BulletPool;
class GameMode;
class ConfettiPool;
class WeaponFactory
{
public:
	WeaponFactory() {}

	~WeaponFactory() {}

	//Crea una chancla (Podemos pasarle los p�rametros que queramos segun las necesidades del objeto)
	static Entity* makeSlipper(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	static Entity* makeConfetti(Entity* e, EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size, GameMode* gM);

	//Crea una pelota saltarina (Podemos pasarle los p�rametros que queramos segun las necesidades del objeto)
	static Entity* makeBall(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	//Crea una grapadora (Podemos pasarle los p�rametros que queramos segun las necesidades del objeto)
	static Entity* makeStapler(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size, BulletPool* bp);

	static Entity* makeExtinguisher(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	static Entity* makeTomato(Entity* e, EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos);

	static Entity* makeDumbbell(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	static Entity* makeBanana(Entity* e, EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, BulletPool* bp);

	static void makeLowTierWeapon(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, GameMode* gM, ConfettiPool* confettiPool);

	static Entity* makeMidTierWeapon(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos);

	static Entity* makeHighTierWeapon(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos);

};

