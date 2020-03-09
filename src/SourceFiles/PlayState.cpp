#include "PlayState.h"
#include "Transform.h"
#include "Viewer.h"
#include "Health.h"
#include "HealthViewer.h"
#include "Weapon.h"
#include "PickObjectListener.h"

PlayState::PlayState()  {
}

PlayState::~PlayState() {
	for (auto o : listenerVector_) {
		delete o;
	}
}

void PlayState::init() {
	//aqui se crean todas las entidades necesarias
	//se podría JSONizar para evitar compilar
	entityManager_ = new EntityManager();
	physicsWorld_ = new b2World(b2Vec2(0, 9.8));

	Entity* tinky = entityManager_->addEntity();
	Entity* ground = entityManager_->addEntity();
	Entity* rock = entityManager_->addEntity();

	Collider* collTinky = tinky->addComponent<Collider>(physicsWorld_, b2_dynamicBody, 240, 80, 50, 50, 50, 0, 1, 0, false);
	//Forma provisional de identificar al jugador, se pueden pasar otro tipo de datos.
	collTinky->setUserData((void*)0);
	Collider* collSuelo = ground->addComponent<Collider>(physicsWorld_, b2_staticBody, 0, 500, 1000, 10, 50, 0, 0, 0, false);
	Collider* collRock = rock->addComponent<Collider>(physicsWorld_, b2_dynamicBody, 250, 280, 20, 20, 10, 0, 0, 0, false);
	collSuelo->setUserData((void*)5);
	
	//if(!pickableObject->IsPicked()) pickableObject->PickObjectBy(collTinky);
	//Transform* tr = tinky->addComponent<Transform>(tinkyBody);
	//Transform* trG = ground->addComponent<Transform>(wallBody);

	tinky->addComponent<Viewer>(Resources::Tinky);		//  <-- se puede poner un sprite con esta constructora, pero por defecto sale un tinky.
	tinky->addComponent<Health>(3);
	tinky->addComponent<HealthViewer>(Resources::ActiveHealth, Resources::DisableHealth, b2Vec2(20, 20));
	ground->addComponent<Viewer>();
	rock->addComponent < Viewer >();
	Weapon* pickableObject = rock->addComponent<Weapon>();
	collRock->createFixture(100, 100, 10, 0, 0, 0, true);

	//Listeners
	PickObjectListener* pOListener = new PickObjectListener();
	physicsWorld_->SetContactListener(pOListener);
	listenerVector_.push_back(pOListener);
}

void PlayState::update() {
	GameState::update();
}
void PlayState::render() {
	GameState::render();
}
void PlayState::handleInput() {
	GameState::handleInput();
}
