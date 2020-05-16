#include "ObjectFactory.h"

#include "EntityManager.h"
#include "Transform.h"
#include "Texture.h"
#include "Viewer.h"
#include "ColliderViewer.h"
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
#include "CarnivorousPlant.h"
#include "TomatoWeapon.h"
#include "AnimatedViewer.h"
#include "BananaWeapon.h"
#include "Bullet.h"
#include "BulletPool.h"
#include "StaplerWeapon.h"
#include "WiFiBullet.h"
#include "SpawnTree.h"
#include "ThrownByPlayer.h"
#include "GameMode.h"


Entity* ObjectFactory::makeSlipper(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {

	Entity* e = entityManager->addEntity();
	//Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "FLIPFLOP_DENSITY"),
	//	CONST(double, "FLIPFLOP_FRICTION"), CONST(double, "FLIPFLOP_RESTITUTION"),
	//	CONST(double, "FLIPFLOP_LINEAR_DRAG"), CONST(double, "FLIPFLOP_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	//e->addComponent<Transform>(SDL_Rect{0,0,CONST(int, "FLIPFLOP_W_SPRITE") ,CONST(int, "FLIPFLOP_W_SPRITE") }, aux);
	//e->addComponent <Viewer>(Resources::Slipper);
	//e->addComponent<SlipperWeapon>(WeaponID::Slipper, CONST(int, "FLIPFLOP_DAMAGE"), CONST(int, "FLIPFLOP_IMPACT_DAMAGE"), CONST(int, "FLIPFLOP_COOLDOWN_FRAMES"));
	//e->addComponent<ColliderViewer>();

	return e;
}

Entity* ObjectFactory::makeBall(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {

	Entity* e = entityManager->addEntity();
	// x,  y,   width, height, density,	friction, restitution, linearDrag, angularDrag,	Layer,							        sensor canBeAttached
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, CONST(double, "BOUNCINGBALL_DENSITY"),
		CONST(double, "BOUNCINGBALL_FRICTION"), CONST(double, "BOUNCINGBALL_RESTITUTION"), CONST(double, "BOUNCINGBALL_LINEAR_DRAG"),
		CONST(double, "BOUNCINGBALL_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	aux->getBody()->SetLinearDamping(0);
	aux->getBody()->SetAngularDamping(0);
	e->addComponent<Transform>(SDL_Rect{ 0,0, CONST(int, "BALL_W_SPRITE"), CONST(int, "BALL_H_SPRITE") }, aux);
	e->addComponent <Viewer>(Resources::Ball);
	e->addComponent<Weapon>(WeaponID::Pelota, CONST(int, "BOUNCINGBALL_IMPACT_DAMAGE"));
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* ObjectFactory::makeStapler(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size, BulletPool* bp) {
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "STAPLER_DENSITY"),
		CONST(double, "STAPLER_FRICTION"), CONST(double, "STAPLER_RESTITUTION"), CONST(double, "STAPLER_LINEAR_DRAG"),
		CONST(double, "STAPLER_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	e->addComponent<Transform>(SDL_Rect{ 0,0, CONST(int, "STAPLER_W_SPRITE"), CONST(int, "STAPLER_H_SPRITE") }, aux);
	e->addComponent <Viewer>(Resources::Stapler);
	e->addComponent<StaplerWeapon>(CONST(int, "STAPLER_IMPACT_DAMAGE"), bp);
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* ObjectFactory::makeExtinguisher(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {

	Entity* entity = entityManager->addEntity();
	Collider* aux = entity->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y,
		CONST(double, "EXTINGUISHER_DENSITY"), CONST(double, "EXTINGUISHER_FRICTION"), CONST(double, "EXTINGUISHER_RESTITUTION"),
		CONST(double, "EXTINGUISHER_LINEAR_DRAG"), CONST(double, "EXTINGUISHER_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	entity->addComponent<Transform>(SDL_Rect{ 0,0, CONST(int, "EXTINGUISHER_W_SPRITE"), CONST(int, "EXTINGUISHER_H_SPRITE") }, aux);
	entity->addComponent<Viewer>(Resources::Extinguisher);
	entity->addComponent<ParticleEmitter>(Vector2D(0, -1), Resources::Coin, 10);
	entity->addComponent<ExtinguisherWeapon>(WeaponID::Extinguisher, CONST(int, "EXTINGUISHER_IMPACT_DAMAGE"),
		CONST(int, "EXTINGUISHER_COOLDOWN_FRAMES"));
	entity->addComponent<ColliderViewer>();

	return entity;
}

Entity* ObjectFactory::makeTomato(Entity* e, EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos)
{
	entityManager->addExistingEntity(e);
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, CONST(double, "TOMATO_RADIUS_PHYSICS"), CONST(double, "TOMATO_DENSITY"),
		CONST(double, "TOMATO_FRICTION"), CONST(double, "TOMATO_RESTITUTION"),
		CONST(double, "TOMATO_LINEAR_DRAG"), CONST(double, "TOMATO_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	e->addComponent<Transform>(SDL_Rect{ 0,0, CONST(int, "TOMATO_RADIUS_SPRITE"), CONST(int, "TOMATO_RADIUS_SPRITE") }, aux);
	e->addComponent <Viewer>(Resources::Tomato, SDL_Rect{ 0, 0, 160, 160 });
	ParticleEmitter* pE = e->addComponent<ParticleEmitter>(Vector2D(0, -1), Resources::TomatoRing, 5, 1, 5, 1000, 20, 100, 0, 360);
	pE->setMaxParticles(1);
	e->addComponent<TomatoWeapon>();
	e->addComponent<ColliderViewer>();

	return e;
}

Weapon* ObjectFactory::makeController(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "CONTROLLER_DENSITY"), CONST(double, "CONTROLLER_FRICTION"),
		CONST(double, "CONTROLLER_RESTITUTION"), CONST(double, "CONTROLLER_LINEAR_DRAG"), CONST(double, "CONTROLLER_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	e->addComponent<Transform>(SDL_Rect{ 0,0, CONST(int, "CONTROLLER_W_SPRITE"),CONST(int, "CONTROLLER_H_SPRITE") }, aux);
	e->addComponent<Viewer>(Resources::Remote);
	Weapon* controller = e->addComponent<Weapon>(WeaponID::Mando, CONST(int, "CONTROLLER_IMPACT_DAMAGE"));
	e->addComponent<ColliderViewer>();

	return controller;
}

Entity* ObjectFactory::makeDumbbell(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size)
{
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "DUMBBELL_DENSITY"),
		CONST(double, "DUMBBELL_FRICTION"), CONST(double, "DUMBBELL_RESTITUTION"),
		CONST(double, "DUMBBELL_LINEAR_DRAG"), CONST(double, "DUMBBELL_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	e->addComponent<Transform>(SDL_Rect{ 0,0, CONST(int, "DUMBBELL_W_SPRITE"), CONST(int, "DUMBBELL_H_SPRITE") }, aux);
	e->addComponent <Viewer>(Resources::Dumbbell);
	e->addComponent<MeleeWeapon>(WeaponID::Mancuerna, CONST(int, "DUMBBELL_DAMAGE"), CONST(int, "DUMBBELL_IMPACT_DAMAGE"), CONST(int, "DUMBBELL_COOLDOWN_FRAMES"));
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* ObjectFactory::makeWall(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size)
{
	Entity* e = entityManager->addEntity();								 // x, y,width, height, density,friction, restitution, linearDrag, angularDrag,	Layer, sensor
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_staticBody, pos.x, pos.y, size.x, size.y, 10, 1, 0.2, 0, 0, Collider::CollisionLayer::Wall, false);
	e->addComponent<Transform>(SDL_Rect{ 0,0,	CONST(int, "WALLS_BASE_W_SPRITE") + (int)size.x * (int)CONST(double, "PIXELS_PER_METER") * CONST(int, "WALLS_SCALE_W_SPRITE"),
												CONST(int, "WALLS_BASE_H_SPRITE") + (int)size.y * (int)CONST(double, "PIXELS_PER_METER") * CONST(int, "WALLS_SCALE_W_SPRITE") }, aux);
	e->addComponent<Viewer>(Resources::Negro);
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* ObjectFactory::makePipe(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size, float rotation) {

	Entity* e = entityManager->addEntity();								 // x, y,width, height, density,friction, restitution, linearDrag, angularDrag,	Layer, sensor
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_staticBody, pos.x, pos.y, size.x, size.y, 10, 1, 0.2, 0, 0, Collider::CollisionLayer::Wall, false);
	e->addComponent<Transform>(SDL_Rect{ 0,0,(int)size.x * CONST(int, "PIXELS_PER_METER") ,(int)size.y * CONST(int, "PIXELS_PER_METER") }, aux);
	e->addComponent<Transform>(SDL_Rect{ 0,0,	CONST(int, "PIPES_BASE_W_SPRITE") + (int)size.x * (int)CONST(double, "PIXELS_PER_METER") * CONST(int, "PIPES_SCALE_W_SPRITE"),
												CONST(int, "PIPES_BASE_H_SPRITE") + (int)size.y * (int)CONST(double, "PIXELS_PER_METER") * CONST(int, "PIPES_SCALE_W_SPRITE") }, aux);
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
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, CONST(int, "SPACE_JUNK_H_PHYSICS"), CONST(int, "SPACE_JUNK_H_PHYSICS"), 1, 0.1, 0.2, 0, 0, Collider::CollisionLayer::NormalObject, false);
	e->addComponent<Transform>(SDL_Rect{ 0, 0, CONST(int, "SPACE_JUNK_H_SPRITE"), CONST(int, "SPACE_JUNK_W_SPRITE") }, aux);
	e->addComponent<Viewer>(Resources::Stone);

	aux->applyLinearImpulse(b2Vec2(0, 50), b2Vec2(0.1, 0));
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* ObjectFactory::makePad(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size)
{
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_staticBody, pos.x, pos.y, size.x, size.y, 0, 0, 1, 0, 0, Collider::CollisionLayer::NonGrababbleWall, false);
	e->addComponent<Transform>(SDL_Rect{ 0,0, CONST(int, "PAD_W_SPRITE"), CONST(int, "PAD_H_SPRITE") }, aux);
	e->addComponent<Viewer>(Resources::PadSpriteSheet, SDL_Rect{ 0,0,32,32 });
	e->addComponent<Pad>();
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* ObjectFactory::makeCoin(Entity* e, EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, int value)
{
	entityManager->addExistingEntity(e);
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, CONST(double, "COIN_BASE_SIZE"), CONST(double, "COIN_DENSITY"), CONST(double, "COIN_FRICTION"), CONST(double, "COIN_ANGULAR_DRAG"), 1, 1, Collider::CollisionLayer::Trigger, true);
	e->addComponent<Transform>(SDL_Rect{ 0,0,CONST(int, "COIN_RADIUS_SPRITE"),CONST(int, "COIN_RADIUS_SPRITE") }, aux);
	e->addComponent<Viewer>(Resources::Coin);
	e->addComponent<Coin>();
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* ObjectFactory::makeFireball(Entity* e, EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos)
{
	entityManager->addExistingEntity(e);
	Collider* auxCol = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, CONST(double, "FIREBALL_RADIUS_PHYSICS"), CONST(double, "FIREBALL_DENSITY"), CONST(double, "FIREBALL_FRICTION"), CONST(double, "FIREBALL_RESTITUTION"), CONST(double, "FIREBALL_LINEAR_DRAG"), CONST(double, "FIREBALL_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	e->addComponent<Transform>(SDL_Rect{ 0,0, CONST(int, "FIREBALL_RADIUS_SPRITE"),CONST(int, "FIREBALL_RADIUS_SPRITE") }, auxCol);
	e->addComponent<Viewer>(Resources::Fireball);
	e->addComponent<Fireball>();
	e->addComponent<Weapon>(WeaponID::Piedra, 999);//Si, el fuego es una piedra muy caliente. Mucho m�s que el magma, esta caldera echa bolas de PLASMA, el cuarto estado de la materia
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* ObjectFactory::makeRoomba(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos)
{
	Entity* e = entityManager->addEntity();
	Collider* collRoomba = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, CONST(double, "ROOMBA_RADIUS_PHYSICS"), CONST(double, "ROOMBA_DENSITY"), CONST(double, "ROOMBA_FRICTION"),
		CONST(double, "ROOMBA_RESTITUTION"), CONST(double, "ROOMBA_LINEAR_DRAG"), CONST(double, "ROOMBA_ANGULAR_DRAG"), Collider::CollisionLayer::UnInteractableObject, false);

	e->addComponent<Transform>(SDL_Rect{ 0,0, CONST(int, "ROOMBA_RADIUS_SPRITE"), CONST(int, "ROOMBA_RADIUS_SPRITE") }, collRoomba);

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
	Collider* collBoiler = e->addComponent<Collider>(physicsWorld, b2_staticBody, pos.x, pos.y, CONST(double, "BOILER_W_PHYSICS"), CONST(double, "BOILER_H_PHYSICS"), CONST(double, "BOILER_DENSITY"), CONST(double, "BOILER_FRICTION"),
		CONST(double, "BOILER_RESTITUTION"), CONST(double, "BOILER_LINEAR_DRAG"), CONST(double, "BOILER_ANGULAR_DRAG"), Collider::CollisionLayer::NormalAttachableObject, false);
	int nFrames = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::Smoke)->getWidth() / SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::Smoke)->getHeight();
	e->addComponent<ParticleEmitter>(Vector2D(0, -1), Resources::Smoke, CONST(int, "FBGEN_PARTICLE_SPEED"), nFrames, CONST(int, "FBGEN_PARTICLE_GEN_ODDS"), CONST(int, "FBGEN_PARTICLE_LIFETIME"), CONST(int, "FBGEN_PARTICLE_SIZE"), 0, CONST(int, "FBGEN_PARTICLE_SPEED_VARIATION"), 180);
	e->addComponent<Transform>(SDL_Rect{ 0,0, CONST(int, "BOILER_W_SPRITE"), CONST(int, "BOILER_H_SPRITE") }, collBoiler);
	e->addComponent<Viewer>(Resources::Boiler);
	e->addComponent<FireBallGenerator>(physicsWorld);
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* ObjectFactory::makeBoilerButton(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, bool inc_dec) {
	Entity* e = entityManager->addEntity();
	Collider* collBoilerButton = e->addComponent<Collider>(physicsWorld, b2_staticBody, pos.x, pos.y, CONST(double, "BOILER_BUTTON_RADIUS_PHYSICS"), 0, 0,
		0, 0, 0, Collider::CollisionLayer::NormalObject, true);
	e->addComponent<Transform>(SDL_Rect{ 0,0, CONST(int, "BOILER_BUTTON_RADIUS_SPRITE"),CONST(int, "BOILER_BUTTON_RADIUS_SPRITE") }, collBoilerButton);
	if (inc_dec) e->addComponent<Viewer>(Resources::IncreasingFreqButton, SDL_Rect{ 0,0,100,100 });
	else e->addComponent<Viewer>(Resources::DecreasingFreqButton, SDL_Rect{ 0,0,100,100 });
	e->addComponent<BoilerButtonLogic>(inc_dec);
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* ObjectFactory::makeTreadmill(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos)
{
	float offset = CONST(double, "TREADMILL_MILL_W_PHYSICS") + CONST(double, "TREADMILL_HANDLE_W_PHYSICS");

	Entity* h = entityManager->addEntity();
	Collider* collHandle = h->addComponent<Collider>(physicsWorld, b2_kinematicBody, pos.x, pos.y, CONST(double, "TREADMILL_HANDLE_W_PHYSICS"), CONST(double, "TREADMILL_HANDLE_H_PHYSICS"), CONST(double, "TREADMILL_DENSITY"), CONST(double, "TREADMILL_FRICTION"),
		CONST(double, "TREADMILL_RESTITUTION"), CONST(double, "TREADMILL_LINEAR_DRAG"), CONST(double, "TREADMILL_ANGULAR_DRAG"), Collider::CollisionLayer::NormalAttachableObject, false);
	h->addComponent<Transform>(SDL_Rect{ 0,0,CONST(int, "TREADMILL_HANDLE_W_SPRITE"),CONST(int, "TREADMILL_HANDLE_H_SPRITE") }, collHandle);
	h->addComponent<Viewer>(Resources::TreadmillPanel);


	Entity* m = entityManager->addEntity();
	Collider* collMill = m->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x + offset, pos.y, CONST(double, "TREADMILL_MILL_W_PHYSICS"), CONST(double, "TREADMILL_MILL_H_PHYSICS"), CONST(double, "TREADMILL_DENSITY"), CONST(double, "TREADMILL_FRICTION"),
		CONST(double, "TREADMILL_RESTITUTION"), CONST(double, "TREADMILL_LINEAR_DRAG"), CONST(double, "TREADMILL_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, true);
	m->addComponent<Transform>(SDL_Rect{ 0,0,CONST(int, "TREADMILL_MILL_W_SPRITE"),CONST(int, "TREADMILL_MILL_H_SPRITE") }, collMill);
	m->addComponent<Viewer>(Resources::TreadmillSpriteSheet, SDL_Rect{ 0,0,82,46 });
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

Entity* ObjectFactory::makeCarnivorousePlant(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size)
{
	Entity* plant = entityManager->addEntity();
	Collider* collPlant = plant->addComponent<Collider>(physicsWorld, b2_staticBody, pos.x, pos.y, size.x, size.y, 0, 0, 0, 0, 0, Collider::CollisionLayer::Trigger, true);
	plant->addComponent<Transform>(SDL_Rect{ 0,0,CONST(int,"CARNIVOROUSPLANT_W_SPRITE"), CONST(int,"CARNIVOROUSPLANT_H_SPRITE") }, collPlant);
	plant->addComponent<Viewer>(Resources::CarnivorousPlant, SDL_Rect{ 0,0,32,32 });
	plant->addComponent<CarnivorousPlant>();
	plant->addComponent<ColliderViewer>();

	return plant;
}

Entity* ObjectFactory::makeBanana(Entity* e, EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, BulletPool* pb)
{
	entityManager->addExistingEntity(e);

	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, 5, 5, CONST(double, "BANANA_W_PHYSICS"), CONST(double, "BANANA_H_PHYSICS"),
		CONST(double, "BANANA_DENSITY"), CONST(double, "BANANA_FRICTION"), CONST(double, "BANANA_RESTITUTION"),
		CONST(double, "BANANA_ANGULAR_DRAG"), CONST(double, "BANANA_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	e->addComponent<Transform>(SDL_Rect{0,0, CONST(int, "BANANA_W_SPRITE") ,CONST(int, "BANANA_W_SPRITE") }, aux);
	e->addComponent<Viewer>(Resources::Banana);
	ParticleEmitter* pE = e->addComponent<ParticleEmitter>(Vector2D(0, -1), Resources::BananaSkin, 100, 1, 5, 1000, 50, 100, 0, 360);
	pE->setMaxParticles(1);
	e->addComponent<BananaWeapon>(pb, CONST(double, "BANANA_DAMAGE"));
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* ObjectFactory::makeBullet(Entity* e, EntityManager* entityManager, b2World* physicsWorld, GameMode* gameMode)
{
	entityManager->addExistingEntity(e);

	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, 0, 0, 0.7, 0.7, //estos 0.7 son la escala, es provisional hasta que se pueda cambiar mas adelante en el setActive
		CONST(double, "BULLET_DENSITY"), CONST(double, "BULLET_FRICTION"), CONST(double, "BULLET_RESTITUTION"),
		CONST(double, "BULLET_LINEAR_DRAG"), CONST(double, "BULLET_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, true);
	e->addComponent<Transform>(SDL_Rect{0,0, CONST(int, "BULLET_W_SPRITE"),CONST(int, "BULLET_H_SPRITE") }, aux);
	e->addComponent<Viewer>(Resources::Negro);

	e->addComponent<Bullet>();
	e->addComponent<ColliderViewer>();
	e->addComponent<ThrownByPlayer>(gameMode);

	return e;
}

Entity* ObjectFactory::makeTomatoTree(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, WeaponPool* pool) {
	Texture* tomatoTex = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::TreeTomato);
	Entity* e = entityManager->addEntity();
	Collider* col = e->addComponent<Collider>(physicsWorld, b2_kinematicBody, pos.x, pos.y, CONST(double, "SPAWN_TREE_W_PHYSICS"),
		CONST(double, "SPAWN_TREE_H_PHYSICS"), CONST(double, "SPAWN_TREE_DENSITY"), CONST(double, "SPAWN_TREE_FRICTION"),
		CONST(double, "SPAWN_TREE_RESTITUTION"), CONST(double, "SPAWN_TREE_LINEAR_DRAG"), CONST(double, "SPAWN_TREE_ANGULAR_DRAG"),
		Collider::CollisionLayer::UnInteractableObject, false);
	e->addComponent<Transform>(SDL_Rect{ 0,0,CONST(int, "SPAWN_TREE_W_SPRITE") , CONST(int, "SPAWN_TREE_H_SPRITE") }, col);
	e->addComponent<Viewer>();
	SDL_Rect clip;
	clip.h = tomatoTex->getHeight();
	clip.w = tomatoTex->getWidth() / 17;
	clip.x = 0; clip.y = 0;
	e->addComponent<SpawnTree>(tomatoTex, CONST(double, "TOMATO_RADIUS_PHYSICS"),
		CONST(double, "TOMATO_RADIUS_PHYSICS"), pool, entityManager, physicsWorld);

	return e;
}

Entity* ObjectFactory::makeBananaTree(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, WeaponPool* pool) {
	Texture* bananaTex = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::Banana);
	Entity* e = entityManager->addEntity();
	Collider* col = e->addComponent<Collider>(physicsWorld, b2_kinematicBody, pos.x, pos.y, CONST(double, "SPAWN_TREE_W_PHYSICS"),
		CONST(double, "SPAWN_TREE_H_PHYSICS"), CONST(double, "SPAWN_TREE_DENSITY"), CONST(double, "SPAWN_TREE_FRICTION"),
		CONST(double, "SPAWN_TREE_RESTITUTION"), CONST(double, "SPAWN_TREE_LINEAR_DRAG"), CONST(double, "SPAWN_TREE_ANGULAR_DRAG"),
		Collider::CollisionLayer::UnInteractableObject, false);
	e->addComponent<Transform>(SDL_Rect{ 0,0,CONST(int, "SPAWN_TREE_W_SPRITE") , CONST(int, "SPAWN_TREE_H_SPRITE") }, col);
	e->addComponent<Viewer>();
	SDL_Rect clip;
	clip.h = bananaTex->getHeight(); clip.w = bananaTex->getWidth() / 17;
	clip.x = 0; clip.y = 0;
	e->addComponent<SpawnTree>(bananaTex, CONST(double, "BANANA_W_PHYSICS"),
		CONST(double, "BANANA_H_PHYSICS"), pool, entityManager, physicsWorld);

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

	e->addComponent<Transform>(SDL_Rect{0,0,CONST(int, "WIFI_W_SPRITE"), CONST(int, "WIFI_H_SPRITE")}, aux);
	e->addComponent<AnimatedViewer>(Resources::WiFiWave, r, 100);
	e->addComponent<WiFiBullet>(colRouter);
	e->addComponent<ColliderViewer>();

	return e;
}
