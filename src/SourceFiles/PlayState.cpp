#include "PlayState.h"
#include "Transform.h"
#include "AttachesToObjects.h"
#include "Texture.h"
#include "Viewer.h"
#include "Health.h"
#include "HealthViewer.h"
#include "InputHandler.h"
#include "CollisionHandler.h"
#include "Weapon.h"
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
	tonko->addComponent<Health>(3);
	tonko->addComponent<HealthViewer>(Resources::ActiveHealth, Resources::DisableHealth, b2Vec2(250, 20));

	tinky->addComponent<Hands>(0, Resources::Hands);
	cout << collTinky->getMass();

	tinky->addComponent<Viewer>(Resources::Tinky);		//  <-- se puede poner un sprite con esta constructora, pero por defecto sale un cuadrado de debug.
	tinky->addComponent<Health>(3);
	tinky->addComponent<HealthViewer>(Resources::ActiveHealth, Resources::DisableHealth, b2Vec2(20, 20));
	ground->addComponent<Viewer>();
	tinky->addComponent<Hands>(0, Resources::Hands);
	tinky->addComponent<AttachesToObjects>(0);
	pared->addComponent<Viewer>();


	rock->addComponent <Viewer>(Resources::PinkTinky);
	collRock->setUserData(rock);
	rock->addComponent<Weapon>(WeaponID::PinkTinky);

	collpared->setUserData(pared);
	collSuelo->setUserData(ground);

	spaceJunk->addComponent<Viewer>();

	collTinky->setUserData(tinky);
	collTonko->setUserData(tonko);


	collTinky->applyLinearImpulse(b2Vec2(15, 0), b2Vec2(1, 1));

	collTonko->applyLinearImpulse(b2Vec2(-40, -10), b2Vec2(0.1, 0));

	
	//collRock->applyLinearImpulse(b2Vec2(10, 0), b2Vec2(0, 0));
	//tr->getBody()->ApplyForce(b2Vec2 (0, -200), b2Vec2(0, 0), true);
	//tr->getBody()->ApplyLinearImpulse(b2Vec2(0, -100), b2Vec2(0, 0),true);

	//collRock->createFixture(100, 100, 10, 0, 0, 0, true);

}

void PlayState::update() {
	GameState::update();
	//el que vuelva tocar el step de physicsworld muere
	physicsWorld_->Step(SECONDS_PER_FRAME, 6, 2);
	collisionHandler_->SolveInteractions();
	//también debería actualizar la lógica de modo de juego
	//spawners de monedas, carga de objetivos...
}
