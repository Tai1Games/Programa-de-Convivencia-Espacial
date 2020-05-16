#include "WeaponFactory.h"

#include "BananaWeapon.h"
#include "ColliderViewer.h"
#include "ConfettiWeapon.h"
#include "ExtinguisherWeapon.h"
#include "ParticleEmitter.h"
#include "SlipperWeapon.h"
#include "StaplerWeapon.h"
#include "ThrownByPlayer.h"
#include "TomatoWeapon.h"
#include "Viewer.h"

Entity* WeaponFactory::makeSlipper(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {

	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "FLIPFLOP_DENSITY"),
		CONST(double, "FLIPFLOP_FRICTION"), CONST(double, "FLIPFLOP_RESTITUTION"),
		CONST(double, "FLIPFLOP_LINEAR_DRAG"), CONST(double, "FLIPFLOP_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	e->addComponent <Viewer>(Resources::Slipper);
	e->addComponent<SlipperWeapon>(WeaponID::Slipper, CONST(int, "FLIPFLOP_DAMAGE"), CONST(int, "FLIPFLOP_IMPACT_DAMAGE"), CONST(int, "FLIPFLOP_COOLDOWN_FRAMES"));
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* WeaponFactory::makeConfetti(Entity* e, EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size, GameMode* gM)
{
	entityManager->addExistingEntity(e);
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "CONFETTI_DENSITY"),
		CONST(double, "CONFETTI_FRICTION"), CONST(double, "CONFETTI_RESTITUTION"),
		CONST(double, "CONFETTI_LINEAR_DRAG"), CONST(double, "CONFETTI_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	e->addComponent <Viewer>(Resources::Confetti, SDL_Rect{ 0,0,32,32 });
	ParticleEmitter* pE = e->addComponent<ParticleEmitter>(Vector2D(0, -1), Resources::ConfettiParticles, 10, 4, 4, 200, 50, 500, 3, 30);
	pE->setOffset({ CONST(double, "CONFETTI_PARTICLE_OFFSET_X"), CONST(double, "CONFETTI_PARTICLE_OFFSET_Y") });
	e->addComponent<ConfettiWeapon>(WeaponID::Confetti, CONST(int, "CONFETTI_DAMAGE"), CONST(int, "CONFETTI_IMPACT_DAMAGE"), CONST(int, "CONFETTI_COOLDOWN_FRAMES"));
	e->addComponent<ColliderViewer>();
	e->addComponent<ThrownByPlayer>(gM);

	return e;
}

Entity* WeaponFactory::makeBall(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {

	Entity* e = entityManager->addEntity();
	// x,  y,   width, height, density,	friction, restitution, linearDrag, angularDrag,	Layer,							        sensor canBeAttached
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, CONST(double, "BOUNCINGBALL_DENSITY"),
		CONST(double, "BOUNCINGBALL_FRICTION"), CONST(double, "BOUNCINGBALL_RESTITUTION"), CONST(double, "BOUNCINGBALL_LINEAR_DRAG"),
		CONST(double, "BOUNCINGBALL_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	aux->getBody()->SetLinearDamping(0);
	aux->getBody()->SetAngularDamping(0);
	e->addComponent <Viewer>(Resources::Ball);
	e->addComponent<Weapon>(WeaponID::Pelota, CONST(int, "BOUNCINGBALL_IMPACT_DAMAGE"));
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* WeaponFactory::makeStapler(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size, BulletPool* bp) {
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "STAPLER_DENSITY"),
		CONST(double, "STAPLER_FRICTION"), CONST(double, "STAPLER_RESTITUTION"), CONST(double, "STAPLER_LINEAR_DRAG"),
		CONST(double, "STAPLER_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	e->addComponent <Viewer>(Resources::Stapler);
	e->addComponent<StaplerWeapon>(CONST(int, "STAPLER_IMPACT_DAMAGE"), bp);
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* WeaponFactory::makeExtinguisher(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size) {

	Entity* entity = entityManager->addEntity();
	Collider* aux = entity->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y,
		CONST(double, "EXTINGUISHER_DENSITY"), CONST(double, "EXTINGUISHER_FRICTION"), CONST(double, "EXTINGUISHER_RESTITUTION"),
		CONST(double, "EXTINGUISHER_LINEAR_DRAG"), CONST(double, "EXTINGUISHER_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	entity->addComponent<Viewer>(Resources::Extinguisher);
	entity->addComponent<ParticleEmitter>(Vector2D(0, -1), Resources::Coin, 10);
	entity->addComponent<ExtinguisherWeapon>(WeaponID::Extinguisher, CONST(int, "EXTINGUISHER_IMPACT_DAMAGE"),
		CONST(int, "EXTINGUISHER_COOLDOWN_FRAMES"));
	entity->addComponent<ColliderViewer>();

	return entity;
}

Entity* WeaponFactory::makeTomato(Entity* e, EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos)
{
	entityManager->addExistingEntity(e);
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, CONST(double, "TOMATO_RADIUS"), CONST(double, "TOMATO_DENSITY"),
		CONST(double, "TOMATO_FRICTION"), CONST(double, "TOMATO_RESTITUTION"),
		CONST(double, "TOMATO_LINEAR_DRAG"), CONST(double, "TOMATO_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	e->addComponent <Viewer>(Resources::Tomato, SDL_Rect{ 0, 0, 160, 160 });
	ParticleEmitter* pE = e->addComponent<ParticleEmitter>(Vector2D(0, -1), Resources::TomatoRing, 5, 1, 5, 1000, 20, 100, 0, 360);
	pE->setMaxParticles(1);
	e->addComponent<TomatoWeapon>();
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* WeaponFactory::makeDumbbell(EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, b2Vec2 size)
{
	Entity* e = entityManager->addEntity();
	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, pos.x, pos.y, size.x, size.y, CONST(double, "DUMBBELL_DENSITY"),
		CONST(double, "DUMBBELL_FRICTION"), CONST(double, "DUMBBELL_RESTITUTION"),
		CONST(double, "DUMBBELL_LINEAR_DRAG"), CONST(double, "DUMBBELL_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	e->addComponent <Viewer>(Resources::Dumbbell);
	e->addComponent<MeleeWeapon>(WeaponID::Mancuerna, CONST(int, "DUMBBELL_DAMAGE"), CONST(int, "DUMBBELL_IMPACT_DAMAGE"), CONST(int, "DUMBBELL_COOLDOWN_FRAMES"));
	e->addComponent<ColliderViewer>();

	return e;
}

Entity* WeaponFactory::makeBanana(Entity* e, EntityManager* entityManager, b2World* physicsWorld, b2Vec2 pos, BulletPool* pb)
{
	entityManager->addExistingEntity(e);

	Collider* aux = e->addComponent<Collider>(physicsWorld, b2_dynamicBody, 5, 5, CONST(double, "BANANA_X"), CONST(double, "BANANA_Y"),
		CONST(double, "BANANA_DENSITY"), CONST(double, "BANANA_FRICTION"), CONST(double, "BANANA_RESTITUTION"),
		CONST(double, "BANANA_ANGULAR_DRAG"), CONST(double, "BANANA_ANGULAR_DRAG"), Collider::CollisionLayer::NormalObject, false);
	e->addComponent<Viewer>(Resources::Banana);
	ParticleEmitter* pE = e->addComponent<ParticleEmitter>(Vector2D(0, -1), Resources::BananaSkin, 100, 1, 5, 1000, 50, 100, 0, 360);
	pE->setMaxParticles(1);
	e->addComponent<BananaWeapon>(pb, CONST(double, "BANANA_DAMAGE"));
	e->addComponent<ColliderViewer>();

	return e;
}