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

	WeaponFactory(b2World* physicsWorld_, EntityManager* entityManager_) {}

	~WeaponFactory(){}

	//Crea una chancla (Podemos pasarle los párametros que queramos segun las necesidades del objeto)
	static void makeChancla(EntityManager* entityManager, b2World* physicsWorld , b2Vec2 pos, b2Vec2 size ) {
		Entity* e = entityManager->addEntity();
		Collider* aux=e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, 1, 0.1, 0.2, 0, 0, Collider::CollisionLayer::NormalObject, false, true);
		e->addComponent <Viewer>(Resources::Chancla);
		//e->addComponent<MeleeWeapon>(WeaponID::Chancla);
		e->addComponent<Weapon>(WeaponID::Chancla);		//Aun no se como hacerlo
		aux->setUserData(e);
	}

	//Crea una pelota saltarina (Podemos pasarle los párametros que queramos segun las necesidades del objeto)
	static void makePelota(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {
		Entity* e = entityManager->addEntity();
		// x,  y,   width, height, density,	friction, restitution, linearDrag, angularDrag,	Layer,							        sensor canBeAttached
		Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, 0.5, 0, 0.99, 0, 0, Collider::CollisionLayer::NormalObject, false, true);
		aux->getBody()->SetLinearDamping(0);
		aux->getBody()->SetAngularDamping(0);
		e->addComponent <Viewer>(Resources::Pelota);
		e->addComponent<Weapon>(WeaponID::Pelota);
		aux->setUserData(e);
	}

	//Crea una pelota saltarina (Podemos pasarle los párametros que queramos segun las necesidades del objeto)
	static void makeGrapadora(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {
		Entity* e = entityManager->addEntity();
		Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, 1, 0.1, 0.2, 0, 0, Collider::CollisionLayer::NormalObject, false, true);
		e->addComponent <Viewer>(Resources::Grapadora);
		e->addComponent<Weapon>(WeaponID::Grapadora);
		aux->setUserData(e);
	}
};

