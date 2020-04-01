#include "WeaponFactory.h"
#include "Transform.h"
#include "Texture.h"
#include "Viewer.h"
#include "Health.h"
#include "HealthViewer.h"
#include "InputHandler.h"
#include "Weapon.h"
#include "Hands.h"

Weapon* WeaponFactory::makeController(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "CONTROLLER_DENSITY"), CONST(double, "CONTROLLER_FRICTION"),
		CONST(double, "CONTROLLER_RESTITUTION"), CONST(double, "CONTROLLER_LINEAR_DRAG"), CONST(double, "CONTROLLER_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	e->addComponent<Viewer>();
	Weapon* controller = e->addComponent<Weapon>(WeaponID::Mando);
	aux->setUserData(e);
	return controller;
}


void WeaponFactory::makeChancla(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "FLIPFLOP_DENSITY"),
		CONST(double, "FLIPFLOP_FRICTION"), CONST(double, "FLIPFLOP_RESTITUTION"), 
		CONST(double, "FLIPFLOP_LINEAR_DRAG"), CONST(double, "FLIPFLOP_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	e->addComponent <Viewer>(Resources::Chancla);
	e->addComponent<Weapon>(WeaponID::Chancla);
	aux->setUserData(e);
}

void WeaponFactory::makePelota(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {
	Entity* e = entityManager->addEntity();
	// x,  y,   width, height, density,	friction, restitution, linearDrag, angularDrag,	Layer,							        sensor canBeAttached
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "BOUNCINGBALL_DENSITY"),
		CONST(double, "BOUNCINGBALL_FRICTION"), CONST(double, "BOUNCINGBALL_RESTITUTION"), CONST(double, "BOUNCINGBALL_LINEAR_DRAG"),
		CONST(double, "BOUNCINGBALL_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	aux->getBody()->SetLinearDamping(0);
	aux->getBody()->SetAngularDamping(0);
	e->addComponent <Viewer>(Resources::Pelota);
	e->addComponent<Weapon>(WeaponID::Pelota);
	aux->setUserData(e);
}

void WeaponFactory::makeGrapadora(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double,"STAPLER_DENSITY"), CONST(double, "STAPLER_FRICTION"), CONST(double, "STAPLER_RESTITUTION"), CONST(double, "STAPLER_LINEAR_DRAG"), CONST(double, "STAPLER_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	e->addComponent <Viewer>(Resources::Grapadora);
	e->addComponent<Weapon>(WeaponID::Grapadora);
	aux->setUserData(e);
}

