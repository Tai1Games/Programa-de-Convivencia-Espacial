#pragma once

#include "Entity.h"

class BulletPool;
class GameMode;
class ConfettiPool;
class StaplerPool;

class WeaponFactory
{
public:
	WeaponFactory() {}

	~WeaponFactory() {}

	//Crea una chancla (Podemos pasarle los p�rametros que queramos segun las necesidades del objeto)
	static Entity* makeSlipper(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	static Entity* makeConfetti(Entity* e, EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	//Crea una pelota saltarina (Podemos pasarle los p�rametros que queramos segun las necesidades del objeto)
	static Entity* makeBall(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	//Crea una grapadora (Podemos pasarle los p�rametros que queramos segun las necesidades del objeto)
	static Entity* makeStapler(Entity* e, EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size, BulletPool* bp);

	static Entity* makeExtinguisher(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	static Entity* makeTomato(Entity* e, EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos);

	static Entity* makeDumbbell(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	static Entity* makeBanana(Entity* e, EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, BulletPool* bp);

	static Entity* makeLowTierWeapon(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, ConfettiPool* confettiPool, StaplerPool* staplerPool, BulletPool* bulletPool);

	static Entity* makeMidTierWeapon(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos);

	static Entity* makeHighTierWeapon(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos);

};

