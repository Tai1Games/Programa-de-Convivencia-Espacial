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
#include "MeleeWeapon.h"
#include "Hands.h"

class WeaponFactory
{
private:
public:

	WeaponFactory() {}

	~WeaponFactory(){}

	//Crea una chancla (Podemos pasarle los p�rametros que queramos segun las necesidades del objeto)
	static void makeChancla(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	//Crea una pelota saltarina (Podemos pasarle los p�rametros que queramos segun las necesidades del objeto)
	static void makePelota(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);

	//Crea una pelota saltarina (Podemos pasarle los p�rametros que queramos segun las necesidades del objeto)
	static void makeGrapadora(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size);
};

