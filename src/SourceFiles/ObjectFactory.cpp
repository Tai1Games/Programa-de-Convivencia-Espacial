#include "ObjectFactory.h"

#include "AnimatedViewer.h"
#include "BoilerButtonLogic.h"
#include "Bullet.h"
#include "BulletPool.h"
#include "CarnivorousPlant.h"
#include "Coin.h"
#include "ColliderViewer.h"
#include "EntityManager.h"
#include "FireBallGenerator.h"
#include "Fireball.h"
#include "GameMode.h"
#include "Hands.h"
#include "Health.h"
#include "HealthViewer.h"
#include "InputHandler.h"
#include "Pad.h"
#include "ParticleEmitter.h"
#include "SpawnTree.h"
#include "Texture.h"
#include "ThrownByPlayer.h"
#include "Transform.h"
#include "Treadmill.h"
#include "Viewer.h"
#include "Weapon.h"
#include "WeaponPool.h"
#include "WiFiBullet.h"
#include "WeaponSpawner.h"
#include "ConfettiPool.h"

Entity* ObjectFactory::makeTable(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size)
{
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "TABLE_DENSITY"),
		CONST(double, "TABLE_FRICTION"), CONST(double, "TABLE_RESTITUTION"),
		CONST(double, "TABLE_LINEAR_DRAG"), CONST(double, "TABLE_ANGULAR_DRAG"), Collider::CollisionLayer::NormalAttachableObject, false);
	e->addComponent<Viewer>(Resources::Table);

	e->addComponent<ColliderViewer>();

	return e;
}

Entity* ObjectFactory::makeLamp(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size)
{
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "LAMP_DENSITY"),
		CONST(double, "LAMP_FRICTION"), CONST(double, "LAMP_RESTITUTION"),
		CONST(double, "LAMP_LINEAR_DRAG"), CONST(double, "LAMP_ANGULAR_DRAG"), Collider::CollisionLayer::NormalAttachableObject, false);
	e->addComponent<Viewer>(Resources::Lamp);

	e->addComponent<ColliderViewer>();

	return e;
}

Entity* ObjectFactory::makeSofa(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size)
{
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "SOFA_DENSITY"),
		CONST(double, "SOFA_FRICTION"), CONST(double, "SOFA_RESTITUTION"),
		CONST(double, "SOFA_LINEAR_DRAG"), CONST(double, "SOFA_ANGULAR_DRAG"), Collider::CollisionLayer::NormalAttachableObject, false);
	e->addComponent<Viewer>(Resources::Sofa);

	e->addComponent<ColliderViewer>();

	return e;
}

Weapon* ObjectFactory::makeController(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "CONTROLLER_DENSITY"), CONST(double, "CONTROLLER_FRICTION"),
		CONST(double, "CONTROLLER_RESTITUTION"), CONST(double, "CONTROLLER_LINEAR_DRAG"), CONST(double, "CONTROLLER_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	e->addComponent<Viewer>(Resources::Remote);
	Weapon* controller = e->addComponent<Weapon>(WeaponID::Mando, CONST(int, "CONTROLLER_IMPACT_DAMAGE"));
	e->addComponent<ColliderViewer>();

	return controller;
}

Entity* ObjectFactory::makeWall(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size)
{
	Entity* e = entityManager->addEntity();								 // x, y,width, height, density,friction, restitution, linearDrag, angularDrag,	Layer, sensor
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_staticBody, pos.x, pos.y, size.x, size.y, 10, 1, 0.2, 0, 0, Collider::CollisionLayer::Wall, false);
	e->addComponent<Viewer>(Resources::Negro);
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* ObjectFactory::makePipe(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size, float rotation) {

	Entity* e = entityManager->addEntity();								 // x, y,width, height, density,friction, restitution, linearDrag, angularDrag,	Layer, sensor
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_staticBody, pos.x, pos.y, size.x, size.y, 10, 1, 0.2, 0, 0, Collider::CollisionLayer::Wall, false);

	//Por si se debe de invertir la imagen en tuberias horizontales
	if (size.x > size.y) {
		e->addComponent<Viewer>(Resources::PipeHor);
		if (pos.y > CONST(int, "WINDOW_HEIGHT") / CONST(double, "PIXELS_PER_METER") / 2) {
			aux->getBody()->SetTransform(pos, PI);
		}
	}
	//Por si se debe de invertir la imagen en tuberias verticales
	else {
		e->addComponent<Viewer>(Resources::PipeVer);
		if (pos.x > CONST(int, "WINDOW_WIDTH") / CONST(double, "PIXELS_PER_METER") / 2) {
			aux->getBody()->SetTransform(pos, PI);
		}
	}
	//Si la tuberia tiene una rotacion especial se la aplicamos
	if (rotation != 0) { aux->getBody()->SetTransform(pos, rotation * (-PI) / 180); }

	e->addComponent<ColliderViewer>();

	return e;
}

Entity* ObjectFactory::makeSpaceJunk(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size)
{
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, 1, 1, 1, 0.1, 0.2, 0, 0, Collider::CollisionLayer::NormalObject, false);
	e->addComponent<Viewer>(Resources::Stone);

	aux->applyLinearImpulse(b2Vec2(rand() % 4, rand() % 4), b2Vec2(0, 0));
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* ObjectFactory::makePad(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size)
{
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_staticBody, pos.x, pos.y, size.x, size.y, 0, 0, 1, 0, 0, Collider::CollisionLayer::NonGrababbleWall, false);
	e->addComponent<Viewer>(Resources::PadSpriteSheet, SDL_Rect{ 0,0,32,32 });
	e->addComponent<Pad>();
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* ObjectFactory::makeCoin(Entity* e, EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, int value)
{
	entityManager->addExistingEntity(e);
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, CONST(double, "COIN_BASE_SIZE"), CONST(double, "COIN_DENSITY"), CONST(double, "COIN_FRICTION"), CONST(double, "COIN_ANGULAR_DRAG"), 1, 1, Collider::CollisionLayer::Trigger, true);
	e->addComponent<Viewer>(Resources::Coin);
	e->addComponent<Coin>();
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* ObjectFactory::makeFireball(Entity* e, EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos)
{
	entityManager->addExistingEntity(e);
	Collider* auxCol = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, CONST(double, "FIREBALL_RADIUS"), CONST(double, "FIREBALL_DENSITY"), CONST(double, "FIREBALL_FRICTION"), CONST(double, "FIREBALL_RESTITUTION"), CONST(double, "FIREBALL_LINEAR_DRAG"), CONST(double, "FIREBALL_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	e->addComponent<Viewer>(Resources::Fireball);
	e->addComponent<Fireball>();
	e->addComponent<Weapon>(WeaponID::Piedra, 999);//Si, el fuego es una piedra muy caliente. Mucho m�s que el magma, esta caldera echa bolas de PLASMA, el cuarto estado de la materia
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* ObjectFactory::makeRoomba(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos)
{
	Entity* e = entityManager->addEntity();
	Collider* collRoomba = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, CONST(double, "ROOMBA_RADIUS"), CONST(double, "ROOMBA_DENSITY"), CONST(double, "ROOMBA_FRICTION"),
		CONST(double, "ROOMBA_RESTITUTION"), CONST(double, "ROOMBA_LINEAR_DRAG"), CONST(double, "ROOMBA_ANGULAR_DRAG"), Collider::CollisionLayer::UnInteractableObject, false);

	e->addComponent<AnimatedViewer>(Resources::RoombaSpriteSheet, SDL_Rect{ 0,0,34,34 }, CONST(int, "ROOMBA_TIMEPERFRAME"));

	double velocityX = rand() % CONST(int, "ROOMBA_VELOCITY");
	double velocityY = CONST(int, "ROOMBA_VELOCITY") - velocityX;

	if (rand() % 2 == 1)velocityX *= -1;
	if (rand() % 2 == 1) velocityY *= -1;

	collRoomba->applyLinearImpulse(b2Vec2(velocityX, velocityY), b2Vec2(0, 0));
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* ObjectFactory::makeBoiler(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos)
{
	Entity* e = entityManager->addEntity();
	Collider* collRoomba = e->addComponent<Collider>(physicsWorld, b2_staticBody, pos.x, pos.y, CONST(double, "BOILER_WIDTH"), CONST(double, "BOILER_HEIGHT"), CONST(double, "BOILER_DENSITY"), CONST(double, "BOILER_FRICTION"),
		CONST(double, "BOILER_RESTITUTION"), CONST(double, "BOILER_LINEAR_DRAG"), CONST(double, "BOILER_ANGULAR_DRAG"), Collider::CollisionLayer::NonGrababbleWall, false);
	int nFrames = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::Smoke)->getWidth() / SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::Smoke)->getHeight();
	e->addComponent<ParticleEmitter>(Vector2D(0, -1), Resources::Smoke, CONST(int, "FBGEN_PARTICLE_SPEED"), nFrames, CONST(int, "FBGEN_PARTICLE_GEN_ODDS"), CONST(int, "FBGEN_PARTICLE_LIFETIME"), CONST(int, "FBGEN_PARTICLE_SIZE"), 0, CONST(int, "FBGEN_PARTICLE_SPEED_VARIATION"), 180);
	e->addComponent<Viewer>(Resources::Boiler);
	e->addComponent<FireBallGenerator>(physicsWorld);
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* ObjectFactory::makeBoilerButton(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, bool inc_dec) {
	Entity* e = entityManager->addEntity();
	Collider* collBoilerButton = e->addComponent<Collider>(physicsWorld, b2_staticBody, pos.x, pos.y, CONST(double, "BOILER_BUTTON_RADIUS"), 0, 0,
		0, 0, 0, Collider::CollisionLayer::NormalObject, true);
	if (inc_dec) e->addComponent<Viewer>(Resources::IncreasingFreqButton, SDL_Rect{ 0,0,100,100 });
	else e->addComponent<Viewer>(Resources::DecreasingFreqButton, SDL_Rect{ 0,0,100,100 });
	e->addComponent<BoilerButtonLogic>(inc_dec);
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* ObjectFactory::makeTreadmill(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos)
{
	float offset = CONST(double, "TREADMILL_MILL_WIDTH") + CONST(double, "TREADMILL_HANDLE_WIDTH");

	Entity* h = entityManager->addEntity();
	Collider* collHandle = h->addComponent<Collider>(physicsWorld, b2_kinematicBody, pos.x, pos.y, CONST(double, "TREADMILL_HANDLE_WIDTH"), CONST(double, "TREADMILL_HANDLE_HEIGHT"), CONST(double, "TREADMILL_DENSITY"), CONST(double, "TREADMILL_FRICTION"),
		CONST(double, "TREADMILL_RESTITUTION"), CONST(double, "TREADMILL_LINEAR_DRAG"), CONST(double, "TREADMILL_ANGULAR_DRAG"), Collider::CollisionLayer::NormalAttachableObject, false);

	Entity* m = entityManager->addEntity();
	Collider* collMill = m->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x + offset, pos.y, CONST(double, "TREADMILL_MILL_WIDTH"), CONST(double, "TREADMILL_MILL_HEIGHT"), CONST(double, "TREADMILL_DENSITY"), CONST(double, "TREADMILL_FRICTION"),
		CONST(double, "TREADMILL_RESTITUTION"), CONST(double, "TREADMILL_LINEAR_DRAG"), CONST(double, "TREADMILL_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, true);

	m->addComponent<Viewer>(Resources::TreadmillSpriteSheet, SDL_Rect{ 0,0,82,46 });
	h->addComponent<Viewer>(Resources::TreadmillPanel);
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
	h->addComponent<ColliderViewer>();
	m->addComponent<ColliderViewer>();

	return m;
}

Entity* ObjectFactory::makeCarnivorousPlant(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size)
{
	Entity* planta = entityManager->addEntity();
	planta->addComponent<Collider>(physicsWorld, b2_staticBody, pos.x, pos.y, size.x, size.y, 0, 0, 0, 0, 0, Collider::CollisionLayer::Trigger, true);
	planta->addComponent<Viewer>(Resources::CarnivorousPlant, SDL_Rect{ 0,0,32,32 });
	planta->addComponent<CarnivorousPlant>();
	planta->addComponent<ColliderViewer>();

	return planta;
}

Entity* ObjectFactory::makeBullet(Entity* e, EntityManager* entityManager, b2World* physicsWorld, GameMode* gameMode)
{
	entityManager->addExistingEntity(e);

	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, 0, 0, 0.7, 0.7, //estos 0.7 son la escala, es provisional hasta que se pueda cambiar mas adelante en el setActive
		CONST(double, "BULLET_DENSITY"), CONST(double, "BULLET_FRICTION"), CONST(double, "BULLET_RESTITUTION"),
		CONST(double, "BULLET_LINEAR_DRAG"), CONST(double, "BULLET_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, true);
	e->addComponent<Viewer>(Resources::Negro);
	e->addComponent<Bullet>();
	e->addComponent<ColliderViewer>();
	e->addComponent<ThrownByPlayer>(gameMode);

	return e;
}

Entity* ObjectFactory::makeTomatoTree(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, WeaponPool* pool) {
	Texture* tomatoTex = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::TreeTomato);
	Entity* e = entityManager->addEntity();
	Collider* col = e->addComponent<Collider>(physicsWorld, b2_kinematicBody, pos.x, pos.y, CONST(double, "SPAWN_TREE_WIDTH"),
		CONST(double, "SPAWN_TREE_HEIGHT"), CONST(double, "SPAWN_TREE_DENSITY"), CONST(double, "SPAWN_TREE_FRICTION"),
		CONST(double, "SPAWN_TREE_RESTITUTION"), CONST(double, "SPAWN_TREE_LINEAR_DRAG"), CONST(double, "SPAWN_TREE_ANGULAR_DRAG"),
		Collider::CollisionLayer::UnInteractableObject, false);
	e->addComponent<Viewer>();
	SDL_Rect clip;
	clip.h = tomatoTex->getHeight();
	clip.w = tomatoTex->getWidth() / 17;
	clip.x = 0; clip.y = 0;
	e->addComponent<SpawnTree>(tomatoTex, CONST(double, "TOMATO_RADIUS"),
		CONST(double, "TOMATO_RADIUS"), pool, entityManager, physicsWorld);

	return e;
}

Entity* ObjectFactory::makeBananaTree(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, WeaponPool* pool) {
	Texture* bananaTex = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::Banana);
	Entity* e = entityManager->addEntity();
	Collider* col = e->addComponent<Collider>(physicsWorld, b2_kinematicBody, pos.x, pos.y, CONST(double, "SPAWN_TREE_WIDTH"),
		CONST(double, "SPAWN_TREE_HEIGHT"), CONST(double, "SPAWN_TREE_DENSITY"), CONST(double, "SPAWN_TREE_FRICTION"),
		CONST(double, "SPAWN_TREE_RESTITUTION"), CONST(double, "SPAWN_TREE_LINEAR_DRAG"), CONST(double, "SPAWN_TREE_ANGULAR_DRAG"),
		Collider::CollisionLayer::UnInteractableObject, false);
	e->addComponent<Viewer>();
	SDL_Rect clip;
	clip.h = bananaTex->getHeight(); clip.w = bananaTex->getWidth() / 17;
	clip.x = 0; clip.y = 0;
	e->addComponent<SpawnTree>(bananaTex, CONST(double, "BANANA_X"),
		CONST(double, "BANANA_Y"), pool, entityManager, physicsWorld);

	return e;
}

Entity* ObjectFactory::makeWifiWave(Entity* e, EntityManager* entityManager, b2World* physicsWorld, Collider* colRouter)
{
	entityManager->addExistingEntity(e);

	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, 0, 0, 0.7, 0.7, //estos 0.7 son la escala, es provisional hasta que se pueda cambiar mas adelante en el setActive
		CONST(double, "BULLET_DENSITY"), CONST(double, "BULLET_FRICTION"), CONST(double, "BULLET_RESTITUTION"),
		CONST(double, "BULLET_LINEAR_DRAG"), CONST(double, "BULLET_ANGULAR_DRAG"), Collider::CollisionLayer::Trigger, true);


	Texture* t = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::WiFiWave);
	SDL_Rect r = { 0, 0, t->getWidth(), t->getHeight() };

	e->addComponent<AnimatedViewer>(Resources::WiFiWave, r, 100);
	e->addComponent<WiFiBullet>(colRouter);
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* ObjectFactory::makeWeaponSpawner(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 position, ConfettiPool* confettiPool, StaplerPool* staplerPool, BulletPool* bulletPool)
{
	Entity* e = entityManager->addEntity();
	e->addComponent<WeaponSpawner>(position, entityManager, physicsWorld, confettiPool, staplerPool, bulletPool);

	return e;
}
