#pragma once
#include "box2d.h"
class Entity;
class CollisionHandler;
struct Collision
{
public:
	Collision(b2Fixture* other,b2Contact* contactInfo,Entity* e,CollisionHandler* hndler, b2Fixture* mFix) :
		entity(e),
		contact(contactInfo),
		hitFixture(other),
		collisionHandler(hndler),
		myFixture(mFix){}
	
	CollisionHandler* collisionHandler = nullptr; //Handler que detecta la colision
	Entity* entity = nullptr; //Entidad con la que se choca
	b2Contact* contact = nullptr; //datos del punto de contacto dados por el motor
	b2Fixture* hitFixture = nullptr;// fixture del objeto al que golpea este componente
	b2Fixture* myFixture = nullptr;// fixture con la que golpea este componente
};

