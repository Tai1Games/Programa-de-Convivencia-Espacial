#include "WeaponFactory.h"

void WeaponFactory::makeChancla(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, FLIPFLOP_DENSITY, FLIPFLOP_FRICTION, FLIPFLOP_RESTITUTION, FLIPFLOP_LINEAR_DRAG, FLIPFLOP_ANGULAR_DRAG, Collider::CollisionLayer::NormalObject, false, true);
	e->addComponent <Viewer>(Resources::Chancla);
	e->addComponent<Weapon>(WeaponID::Chancla);
	aux->setUserData(e);
}

void WeaponFactory::makePelota(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {
	Entity* e = entityManager->addEntity();
	// x,  y,   width, height, density,	friction, restitution, linearDrag, angularDrag,	Layer,							        sensor canBeAttached
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, BOUNCINGBALL_DENSITY, BOUNCINGBALL_FRICTION, BOUNCINGBALL_RESTITUTION, BOUNCINGBALL_LINEAR_DRAG, BOUNCINGBALL_ANGULAR_DRAG, Collider::CollisionLayer::NormalObject, false, true);
	aux->getBody()->SetLinearDamping(0);
	aux->getBody()->SetAngularDamping(0);
	e->addComponent <Viewer>(Resources::Pelota);
	e->addComponent<Weapon>(WeaponID::Pelota);
	aux->setUserData(e);
}

void WeaponFactory::makeGrapadora(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double,"STAPLER_DENSITY"), STAPLER_FRICTION, STAPLER_RESTITUTION, STAPLER_LINEAR_DRAG, STAPLER_ANGULAR_DRAG, Collider::CollisionLayer::NormalObject, false, true);
	e->addComponent <Viewer>(Resources::Grapadora);
	e->addComponent<Weapon>(WeaponID::Grapadora);
	aux->setUserData(e);
}