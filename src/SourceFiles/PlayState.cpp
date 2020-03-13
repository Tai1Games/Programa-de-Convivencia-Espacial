#include "PlayState.h"
#include "Transform.h"
#include "Viewer.h"
#include "Health.h"
#include "HealthViewer.h"
#include "InputHandler.h"
#include "CollisionHandler.h"
#include "Weapon.h"
#include "PickObjectListener.h"
#include "Hands.h"

PlayState::PlayState()  {
}

PlayState::~PlayState() {
}

void PlayState::init() {
	//aqui se crean todas las entidades necesarias
	//se podría JSONizar para evitar compilar
	entityManager_ = new EntityManager();
	physicsWorld_ = new b2World(b2Vec2(0, 0));
	collisionHandler_ = new CollisionHandler();
	physicsWorld_->SetContactListener(collisionHandler_);

	Entity* tinky = entityManager_->addEntity();
	Entity* ground = entityManager_->addEntity();
	Entity* pared = entityManager_->addEntity();
	Entity* rock = entityManager_->addEntity();
	//Entity* spaceJunk = entityManager_->addEntity();
	
																			// x, y, width, height,			density,	friction,	restitution,	linearDrag,		angularDrag,		Layer,								sensor
	Collider* collTinky = tinky->addComponent<Collider>(physicsWorld_, b2_dynamicBody, 2, 2, 1, 1,			1,			0.1,		0.2,			0,				0,					Collider::CollisionLayer::Player,	false);
	Collider* collSuelo = ground->addComponent<Collider>(physicsWorld_, b2_staticBody, 10.5, -0.5, 12,1,	10,			0,			0.2,			0,				0,					Collider::CollisionLayer::Normal,	false);
	Collider* collpared = pared->addComponent<Collider>(physicsWorld_, b2_staticBody, 21.5, 10, 1, 10,		10,			1,			0.2,			0,				0,					Collider::CollisionLayer::Normal,	false);
	Collider* collRock = rock->addComponent<Collider>(physicsWorld_, b2_dynamicBody, 10, 2, 0.5, 0.5,		1,			0,			0.2,			0,				0,					Collider::CollisionLayer::Normal,	false);
	//Collider* collJunk = spaceJunk->addComponent<Collider>(physicsWorld_, b2_dynamicBody, 300, 60, 30, 30,   20, 1000000000000000, 0.8, 0, false);

	tinky->addComponent<Hands>(0);
	cout<<collTinky->getMass();

	tinky->addComponent<Viewer>(Resources::Tinky);		//  <-- se puede poner un sprite con esta constructora, pero por defecto sale un cuadrado de debug.
	tinky->addComponent<Health>(3);
	tinky->addComponent<HealthViewer>(Resources::ActiveHealth, Resources::DisableHealth, b2Vec2(20, 20));
	ground->addComponent<Viewer>();
	pared->addComponent<Viewer>();
	rock->addComponent <Viewer>(Resources::Tinky);
	collRock->setUserData(rock);
	rock->addComponent<Weapon>();

	collpared->setUserData(pared);
	collSuelo->setUserData(ground);

	//spaceJunk->addComponent<Viewer>();

	collTinky->setUserData(tinky);
	

	//cout << collJunk->getMass();

	//collTinky->applyLinearImpulse(b2Vec2(40, -30), b2Vec2(0.1, 0));
	collTinky->applyLinearImpulse(b2Vec2(10, 0), b2Vec2(0, 0));
	//collRock->applyLinearImpulse(b2Vec2(10, 0), b2Vec2(0, 0));
	//tr->getBody()->ApplyForce(b2Vec2 (0, -200), b2Vec2(0, 0), true);
	//tr->getBody()->ApplyLinearImpulse(b2Vec2(0, -100), b2Vec2(0, 0),true);

	//collRock->createFixture(100, 100, 10, 0, 0, 0, true);

}

void PlayState::update() {
	GameState::update();
	//el que vuelva tocar el step de physicsworld muere
	physicsWorld_->Step(SECONDS_PER_FRAME, 6, 2);
	//también debería actualizar la lógica de modo de juego
	//spawners de monedas, carga de objetivos...
}
