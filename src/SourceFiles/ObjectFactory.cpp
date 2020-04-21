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
#include "SlipperWeapon.h"
#include "MeleeWeapon.h"
#include "ParticleEmitter.h"
#include "BoilerButtonLogic.h"
#include "Pad.h"
#include "Treadmill.h"

Entity* ObjectFactory::makeSlipper(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {

	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "FLIPFLOP_DENSITY"),
		CONST(double, "FLIPFLOP_FRICTION"), CONST(double, "FLIPFLOP_RESTITUTION"),
		CONST(double, "FLIPFLOP_LINEAR_DRAG"), CONST(double, "FLIPFLOP_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	e->addComponent <Viewer>(Resources::Slipper);
	e->addComponent<SlipperWeapon>(WeaponID::Slipper, CONST(int, "FLIPFLOP_DAMAGE"), CONST(int, "FLIPFLOP_IMPACT_DAMAGE"), CONST(int, "FLIPFLOP_COOLDOWN_FRAMES"));

	return e;
}

Entity* ObjectFactory::makeBall(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {

	Entity* e = entityManager->addEntity();
	// x,  y,   width, height, density,	friction, restitution, linearDrag, angularDrag,	Layer,							        sensor canBeAttached
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "BOUNCINGBALL_DENSITY"),
		CONST(double, "BOUNCINGBALL_FRICTION"), CONST(double, "BOUNCINGBALL_RESTITUTION"), CONST(double, "BOUNCINGBALL_LINEAR_DRAG"),
		CONST(double, "BOUNCINGBALL_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	aux->getBody()->SetLinearDamping(0);
	aux->getBody()->SetAngularDamping(0);
	e->addComponent <Viewer>(Resources::Ball);
	e->addComponent<Weapon>(WeaponID::Pelota, CONST(int, "BOUNCINGBALL_IMPACT_DAMAGE"));
  
	return e;
}

Entity* ObjectFactory::makeStapler(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "STAPLER_DENSITY"), CONST(double, "STAPLER_FRICTION"), CONST(double, "STAPLER_RESTITUTION"), CONST(double, "STAPLER_LINEAR_DRAG"), CONST(double, "STAPLER_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	e->addComponent <Viewer>(Resources::Stapler);
	e->addComponent<Weapon>(WeaponID::Stapler, CONST(int, "STAPLER_IMPACT_DAMAGE"));

	return e;
}

Entity* ObjectFactory::makeExtinguisher(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {

	Entity* entity = entityManager->addEntity();
	Collider* aux = entity->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "EXTINGUISHER_DENSITY"), CONST(double, "EXTINGUISHER_FRICTION"), CONST(double, "EXTINGUISHER_RESTITUTION"), CONST(double, "EXTINGUISHER_LINEAR_DRAG"), CONST(double, "STAPLER_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	entity->addComponent<Viewer>(Resources::Extinguisher);
	entity->addComponent<ParticleEmitter>(Vector2D(0, -1), Resources::Coin, 10);
	entity->addComponent<ExtinguisherWeapon>(WeaponID::Extinguisher, CONST(int, "EXTINGUISHER_IMPACT_DAMAGE"), CONST(int, "EXTINGUISHER_COOLDOWN_FRAMES"));

	return entity;
}

Weapon* ObjectFactory::makeController(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "CONTROLLER_DENSITY"), CONST(double, "CONTROLLER_FRICTION"),
		CONST(double, "CONTROLLER_RESTITUTION"), CONST(double, "CONTROLLER_LINEAR_DRAG"), CONST(double, "CONTROLLER_ANGULAR_DRAG"), Collider::CollisionLayer::Trigger, false);
	e->addComponent<Viewer>();
	Weapon* controller = e->addComponent<Weapon>(WeaponID::Mando, CONST(int, "CONTROLLER_IMPACT_DAMAGE"));
	return controller;
}

Entity* ObjectFactory::makeDumbbell(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size)
{
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "DUMBBELL_DENSITY"),
		CONST(double, "DUMBBELL_FRICTION"), CONST(double, "DUMBBELL_RESTITUTION"),
		CONST(double, "DUMBBELL_LINEAR_DRAG"), CONST(double, "DUMBBELL_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	e->addComponent <Viewer>(Resources::Mancuerna);
	e->addComponent<MeleeWeapon>(WeaponID::Mancuerna, CONST(int, "DUMBBELL_DAMAGE"), CONST(int, "DUMBBELL_IMPACT_DAMAGE"), CONST(int,"DUMBBELL_COOLDOWN_FRAMES"));

	return e;
}

Entity* ObjectFactory::makeWall(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size)
{
	Entity* e = entityManager->addEntity();								 // x, y,width, height, density,friction, restitution, linearDrag, angularDrag,	Layer, sensor
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_staticBody, pos.x, pos.y, size.x, size.y, 10, 1, 0.2, 0, 0, Collider::CollisionLayer::Wall, false);
	e->addComponent<Viewer>(Resources::Negro);

	return e;
}

Entity* ObjectFactory::makePipe(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size, float rotation) {

	Entity* e = entityManager->addEntity();								 // x, y,width, height, density,friction, restitution, linearDrag, angularDrag,	Layer, sensor
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_staticBody, pos.x, pos.y, size.x, size.y, 10, 1, 0.2, 0, 0, Collider::CollisionLayer::Wall, false);

	//Por si se debe de invertir la imagen en tuberias horizontales
	if (size.x > size.y) {
		e->addComponent<Viewer>(Resources::PipeHor);
		if (pos.y > CONST(int, "WINDOW_HEIGHT") / CONST(double, "PIXELS_PER_METER") / 2) {
			aux->getBody()->SetTransform(pos, CONST(double, "PI"));
		}
	}
	//Por si se debe de invertir la imagen en tuberias verticales
	else {
		e->addComponent<Viewer>(Resources::PipeVer);
		if (pos.x > CONST(int, "WINDOW_WIDTH") / CONST(double, "PIXELS_PER_METER") / 2) {
			aux->getBody()->SetTransform(pos, CONST(double, "PI"));
		}
	}
	//Si la tuberia tiene una rotacion especial se la aplicamos
	if (rotation != 0) { aux->getBody()->SetTransform(pos, rotation * (-CONST(double, "PI")) / 180); }

	return e;
}





Entity* ObjectFactory::makeSpaceJunk(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size)
{
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, 1, 1, 1, 0.1, 0.2, 0, 0, Collider::CollisionLayer::NormalObject, false);
	e->addComponent<Viewer>(Resources::Stone);

	aux->applyLinearImpulse(b2Vec2(0, 50), b2Vec2(0.1, 0));

	return e;
}


Entity* ObjectFactory::makePad(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size)
{
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_staticBody, pos.x, pos.y, size.x, size.y, 0, 0, 1, 0, 0, Collider::CollisionLayer::NonGrababbleWall, false);
	e->addComponent<Viewer>(Resources::PadSpriteSheet, SDL_Rect{ 0,0,32,32 });
	e->addComponent<Pad>();

	return e;
}

Entity* ObjectFactory::makeCoin(Entity* e, EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, int value)
{
	entityManager->addExistingEntity(e);
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, CONST(double, "COIN_BASE_SIZE"), CONST(double, "COIN_DENSITY"), CONST(double, "COIN_FRICTION"), CONST(double, "COIN_ANGULAR_DRAG"), 1, 1, Collider::CollisionLayer::Trigger, true);
	e->addComponent<Viewer>(Resources::Coin);
	e->addComponent<Coin>();

	return e;
}

Entity* ObjectFactory::makeFireball(Entity* e, EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos)
{
	entityManager->addExistingEntity(e);
	Collider* auxCol = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, CONST(double, "FIREBALL_RADIUS"), CONST(double, "FIREBALL_DENSITY"), CONST(double, "FIREBALL_FRICTION"), CONST(double, "FIREBALL_RESTITUTION"), CONST(double, "FIREBALL_LINEAR_DRAG"), CONST(double, "FIREBALL_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	e->addComponent<Viewer>(Resources::Fireball);
	e->addComponent<Fireball>();
	e->addComponent<Weapon>(WeaponID::Piedra, 999);//Si, el fuego es una piedra muy caliente. Mucho m�s que el magma, esta caldera echa bolas de PLASMA, el cuarto estado de la materia

	return e;
}

Entity* ObjectFactory::createRoomba(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos)
{
	Entity* e = entityManager->addEntity();
	Collider* collRoomba = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, CONST(double, "ROOMBA_RADIUS"), CONST(double, "ROOMBA_DENSITY"), CONST(double, "ROOMBA_FRICTION"),
		CONST(double, "ROOMBA_RESTITUTION"), CONST(double, "ROOMBA_LINEAR_DRAG"), CONST(double, "ROOMBA_ANGULAR_DRAG"), Collider::CollisionLayer::UnInteractableObject, false);
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
	Collider* collRoomba = e->addComponent<Collider>(physicsWorld, b2_staticBody, pos.x, pos.y, CONST(double, "BOILER_WIDTH"), CONST(double, "BOILER_HEIGHT"), CONST(double, "BOILER_DENSITY"), CONST(double, "BOILER_FRICTION"),
		CONST(double, "BOILER_RESTITUTION"), CONST(double, "BOILER_LINEAR_DRAG"), CONST(double, "BOILER_ANGULAR_DRAG"), Collider::CollisionLayer::Trigger, false);
	e->addComponent<Viewer>(Resources::Boiler);
	e->addComponent<FireBallGenerator>(physicsWorld);

	return e;
}

Entity* ObjectFactory::makeBoilerButton(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, bool inc_dec) {
	Entity* e = entityManager->addEntity();
	Collider* collBoilerButton = e->addComponent<Collider>(physicsWorld, b2_staticBody, pos.x, pos.y, CONST(double, "BOILER_BUTTON_RADIUS"), 0, 0,
		0, 0, 0, Collider::CollisionLayer::NormalObject, true);
	if (inc_dec) e->addComponent<Viewer>(Resources::IncreasingFreqButton, SDL_Rect{ 0,0,100,100 });
	else e->addComponent<Viewer>(Resources::DecreasingFreqButton, SDL_Rect{ 0,0,100,100 });
	e->addComponent<BoilerButtonLogic>(inc_dec);


	return e;
}

Entity* ObjectFactory::createTreadmill(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos)
{
	float offset = CONST(double, "TREADMILL_MILL_WIDTH") + CONST(double, "TREADMILL_HANDLE_WIDTH");

	Entity* h = entityManager->addEntity();
	Collider* collHandle = h->addComponent<Collider>(physicsWorld, b2_kinematicBody, pos.x, pos.y, CONST(double, "TREADMILL_HANDLE_WIDTH"), CONST(double, "TREADMILL_HANDLE_HEIGHT"), CONST(double, "TREADMILL_DENSITY"), CONST(double, "TREADMILL_FRICTION"),
		CONST(double, "TREADMILL_RESTITUTION"), CONST(double, "TREADMILL_LINEAR_DRAG"), CONST(double, "TREADMILL_ANGULAR_DRAG"), Collider::CollisionLayer::NormalAttachableObject, false);

	Entity* m = entityManager->addEntity();
	Collider* collMill = m->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x + offset, pos.y, CONST(double, "TREADMILL_MILL_WIDTH"), CONST(double, "TREADMILL_MILL_HEIGHT"), CONST(double, "TREADMILL_DENSITY"), CONST(double, "TREADMILL_FRICTION"),
		CONST(double, "TREADMILL_RESTITUTION"), CONST(double, "TREADMILL_LINEAR_DRAG"), CONST(double, "TREADMILL_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, true);

	m->addComponent<Viewer>(Resources::TreadmillSpriteSheet, SDL_Rect{ 0,0,82,46 });
	h->addComponent<Viewer>(Resources::Debug);
	m->addComponent<Treadmill>(collHandle);

	b2Vec2 collPoint = b2Vec2(pos.x + offset, pos.y);
	b2WeldJointDef jointDef; //Definición del nuevo joint.
	jointDef.bodyA = collMill->getBody(); //Body del jugador.
	jointDef.bodyB = collHandle->getBody(); //Body del objeto al que se tiene que atar.
	jointDef.collideConnected = false; //Flag que decide si estos 2 objetos van a ejercer físicas el uno contra el otro.
	jointDef.localAnchorA = jointDef.bodyA->GetLocalPoint(collPoint); //Punto donde se ata el cuerpo A al cuerpo B
	jointDef.localAnchorB = jointDef.bodyB->GetLocalPoint(collPoint); //Punto donde se ata el cuerpo B al cuerpo A
	jointDef.referenceAngle = jointDef.bodyB->GetAngle() - jointDef.bodyA->GetAngle(); //Ángulo conjunto del cuerpo
	b2World* world = collMill->getWorld(); //Obtenemos el mundo físico para crear el joint
	world->CreateJoint(&jointDef); //Crea el joint con la definición que hemos definido previamente

	return m;
}
