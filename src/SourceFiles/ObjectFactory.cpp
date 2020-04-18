#include "ObjectFactory.h"

#include "EntityManager.h"
#include "Transform.h"
#include "Texture.h"
#include "Viewer.h"
#include "Health.h"
#include "HealthViewer.h"
#include "InputHandler.h"
#include "Weapon.h"
#include "Hands.h"
#include "Coin.h"
#include "FireBallGenerator.h"
#include "Fireball.h"
#include "ExtinguisherWeapon.h"
#include "ParticleEmitter.h"
#include "BoilerButtonLogic.h"
#include "Pad.h"

void ObjectFactory::makeSlipper(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "FLIPFLOP_DENSITY"),
		CONST(double, "FLIPFLOP_FRICTION"), CONST(double, "FLIPFLOP_RESTITUTION"),
		CONST(double, "FLIPFLOP_LINEAR_DRAG"), CONST(double, "FLIPFLOP_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	e->addComponent <Viewer>(Resources::Slipper);
	e->addComponent<Weapon>(WeaponID::Slipper, CONST(int, "FLIPFLOP_DAMAGE"), CONST(int, "FLIPFLOP_IMPACT_DAMAGE"));
	aux->setUserData(e);
}

void ObjectFactory::makeBall(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {
	Entity* e = entityManager->addEntity();
	// x,  y,   width, height, density,	friction, restitution, linearDrag, angularDrag,	Layer,							        sensor canBeAttached
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "BOUNCINGBALL_DENSITY"),
		CONST(double, "BOUNCINGBALL_FRICTION"), CONST(double, "BOUNCINGBALL_RESTITUTION"), CONST(double, "BOUNCINGBALL_LINEAR_DRAG"),
		CONST(double, "BOUNCINGBALL_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	aux->getBody()->SetLinearDamping(0);
	aux->getBody()->SetAngularDamping(0);
	e->addComponent <Viewer>(Resources::Pelota);
	e->addComponent<Weapon>(WeaponID::Pelota, CONST(int, "BOUNCINGBALL_DAMAGE"), CONST(int, "BOUNCINGBALL_IMPACT_DAMAGE"));
	aux->setUserData(e);
}

void ObjectFactory::makeStapler(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "STAPLER_DENSITY"), CONST(double, "STAPLER_FRICTION"), CONST(double, "STAPLER_RESTITUTION"), CONST(double, "STAPLER_LINEAR_DRAG"), CONST(double, "STAPLER_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	e->addComponent <Viewer>(Resources::Stapler);
	e->addComponent<Weapon>(WeaponID::Stapler, CONST(int, "STAPLER_DAMAGE"), CONST(int, "STAPLER_IMPACT_DAMAGE"));
	aux->setUserData(e);
}

void ObjectFactory::makeExtinguisher(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {
	Entity* entity = entityManager->addEntity();
	Collider* aux = entity->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "EXTINGUISHER_DENSITY"), CONST(double, "EXTINGUISHER_FRICTION"), CONST(double, "EXTINGUISHER_RESTITUTION"), CONST(double, "EXTINGUISHER_LINEAR_DRAG"), CONST(double, "STAPLER_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	entity->addComponent<Viewer>(Resources::Extinguisher);
	entity->addComponent<ParticleEmitter>(Vector2D(0,-1),Resources::Coin,10);
	entity->addComponent<ExtinguisherWeapon>(WeaponID::Extinguisher, CONST(int, "EXTINGUISHER_DAMAGE"), CONST(int, "EXTINGUISHER_IMPACT_DAMAGE"));
	aux->setUserData(entity);
}

void ObjectFactory::makeWall(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size)
{
	Entity* e = entityManager->addEntity();								 // x, y,width, height, density,friction, restitution, linearDrag, angularDrag,	Layer, sensor
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_staticBody, pos.x, pos.y, size.x, size.y, 10, 1, 0.2, 0, 0, Collider::CollisionLayer::Wall, false);
	e->addComponent<Viewer>(Resources::Negro);
	aux->setUserData(e);
}

void ObjectFactory::makeSpaceJunk(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size)
{
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, 1, 1, 1, 0.1, 0.2, 0, 0, Collider::CollisionLayer::NormalObject, false);
	e->addComponent<Viewer>(Resources::Piedra);
	aux->setUserData(e);

	aux->applyLinearImpulse(b2Vec2(0, 50), b2Vec2(0.1, 0));
}


void ObjectFactory::makePad(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size)
{
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_staticBody, pos.x, pos.y, size.x, size.y, 0, 0, 1, 0, 0, Collider::CollisionLayer::NonGrababbleWall, false);
	e->addComponent<Viewer>(Resources::PadSpriteSheet, SDL_Rect{ 0,0,32,32 });
	aux->setUserData(e);
	e->addComponent<Pad>();
}

void ObjectFactory::makeCoin(Entity* e, EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, int value)
{
	entityManager->addExistingEntity(e);
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, CONST(double, "COIN_BASE_SIZE"), CONST(double, "COIN_DENSITY"), CONST(double, "COIN_FRICTION"), CONST(double, "COIN_ANGULAR_DRAG"), 1, 1, Collider::CollisionLayer::Trigger, true);
	e->addComponent<Viewer>(Resources::Coin);
	e->addComponent<Coin>();
	aux->setUserData(e);
}

void ObjectFactory::makeFireball(Entity* e, EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos)
{
	entityManager->addExistingEntity(e);
	Collider* auxCol = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, CONST(double, "FIREBALL_RADIUS"), CONST(double, "FIREBALL_DENSITY"), CONST(double, "FIREBALL_FRICTION"), CONST(double, "FIREBALL_ANGULAR_DRAG"), 1, 1, Collider::CollisionLayer::NormalObject, false);
	e->addComponent<Viewer>(Resources::Fireball);
	e->addComponent<Fireball>();
	e->addComponent<Weapon>(WeaponID::Piedra, 999, 999);//Si, el fuego es una piedra muy caliente. Mucho m�s que el magma, esta caldera echa bolas de PLASMA, el cuarto estado de la materia
	auxCol->setUserData(e);
}


Weapon* ObjectFactory::makeController(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "CONTROLLER_DENSITY"), CONST(double, "CONTROLLER_FRICTION"),
		CONST(double, "CONTROLLER_RESTITUTION"), CONST(double, "CONTROLLER_LINEAR_DRAG"), CONST(double, "CONTROLLER_ANGULAR_DRAG"), Collider::CollisionLayer::Trigger, false);
	e->addComponent<Viewer>();
	Weapon* controller = e->addComponent<Weapon>(WeaponID::Mando, CONST(int, "CONTROLLER_DAMAGE"), CONST(int, "CONTROLLER_IMPACT_DAMAGE"));
	aux->setUserData(e);
	return controller;
}

void ObjectFactory::makeDumbbell(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size)
{
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "DUMBBELL_DENSITY"),
		CONST(double, "DUMBBELL_FRICTION"), CONST(double, "DUMBBELL_RESTITUTION"),
		CONST(double, "DUMBBELL_LINEAR_DRAG"), CONST(double, "DUMBBELL_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	e->addComponent <Viewer>(Resources::Mancuerna);
	e->addComponent<Weapon>(WeaponID::Mancuerna, CONST(int, "DUMBBELL_DAMAGE"), CONST(int, "DUMBBELL_IMPACT_DAMAGE"));
	aux->setUserData(e);
}

Entity* ObjectFactory::createRoomba(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos)
{
	Entity* e = entityManager->addEntity();
	Collider* collRoomba = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, CONST(double, "ROOMBA_RADIUS"), CONST(double, "ROOMBA_DENSITY"), CONST(double, "ROOMBA_FRICTION"),
		CONST(double, "ROOMBA_RESTITUTION"), CONST(double, "ROOMBA_LINEAR_DRAG"), CONST(double, "ROOMBA_ANGULAR_DRAG"), Collider::CollisionLayer::UnInteractableObject, false);
	collRoomba->setUserData(e);
	e->addComponent<Viewer>();

	double velocityX = rand() % CONST(int, "ROOMBA_VELOCITY");
	double velocityY = CONST(int, "ROOMBA_VELOCITY") - velocityX;

	if (rand() % 2 == 1)velocityX *= -1;
	if (rand() % 2 == 1) velocityY *= -1;

	collRoomba->applyLinearImpulse(b2Vec2(velocityX, velocityY), b2Vec2(0, 0));
	return e;
}

Entity* ObjectFactory::createBoiler(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos)
{
	Entity* e = entityManager->addEntity();
	Collider* collRoomba = e->addComponent<Collider>(physicsWorld, b2_staticBody, pos.x, pos.y, CONST(double, "BOILER_WIDTH"), CONST(double, "BOILER_HEIGHT"), CONST(double, "BOILER_DENSITY"),CONST(double, "BOILER_FRICTION"),
		CONST(double, "BOILER_RESTITUTION"),CONST(double,"BOILER_LINEAR_DRAG"), CONST(double, "BOILER_ANGULAR_DRAG"), Collider::CollisionLayer::Trigger, false);
	collRoomba->setUserData(e);
	e->addComponent<Viewer>(Resources::Boiler);	
	e->addComponent<FireBallGenerator>(physicsWorld);

	return e;
}

Entity* ObjectFactory::makeBoilerButton(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, bool inc_dec) {
	Entity* e = entityManager->addEntity();
	Collider* collBoilerButton = e->addComponent<Collider>(physicsWorld, b2_staticBody, pos.x, pos.y, CONST(double, "BOILER_BUTTON_RADIUS"), 0, 0,
		0, 0, 0, Collider::CollisionLayer::NormalObject, true);
	collBoilerButton->setUserData(e);
	if (inc_dec) e->addComponent<Viewer>(Resources::IncreasingFreqButton, SDL_Rect{ 0,0,100,100 });
	else e->addComponent<Viewer>(Resources::DecreasingFreqButton, SDL_Rect{ 0,0,100,100 });
	e->addComponent<BoilerButtonLogic>(inc_dec);


	return e;
}