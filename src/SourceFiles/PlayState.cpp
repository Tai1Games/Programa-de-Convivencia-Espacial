#include "PlayState.h"
#include "Transform.h"
#include "Viewer.h"
#include "Health.h"
#include "HealthViewer.h"

PlayState::PlayState() :
	entityManager_(nullptr),
	physicsWorld_(nullptr) {
}

PlayState::~PlayState() {
	delete entityManager_;
	delete physicsWorld_;
}

void PlayState::init() {
	//aqui se crean todas las entidades necesarias
	//se podría JSONizar para evitar compilar
	entityManager_ = new EntityManager();
	physicsWorld_ = new b2World(b2Vec2(0, 9.8));
	
	Entity* tinky = entityManager_->addEntity();
	Entity* ground = entityManager_->addEntity();
	Entity* rock = entityManager_->addEntity();

	Collider* collTinky = tinky->addComponent<Collider>(physicsWorld_, b2_dynamicBody, 150, 80, 50, 50, 50, 0, 0, 0, false);
	Collider* collSuelo = ground->addComponent<Collider>(physicsWorld_, b2_staticBody, 0, 500, 1000, 10, 50, 0, 0, 0, false);
	Collider* collRock = rock->addComponent<Collider>(physicsWorld_, b2_dynamicBody, 500, 80, 20, 20, 10, 0, 0, 0, false);
	tinky->addComponent<Viewer>(Resources::Tinky);		//  <-- se puede poner un sprite con esta constructora, pero por defecto sale un tinky.
	tinky->addComponent<Health>(3);
	tinky->addComponent<HealthViewer>(Resources::ActiveHealth, Resources::DisableHealth, b2Vec2(20, 20));
	ground->addComponent<Viewer>();
	rock->addComponent < Viewer >();
	collRock->createFixture(100, 100, 10, 0, 0, 0, true);
	std::cout << collRock->isSensor(0) << " " << collRock->isSensor(1);
}

void PlayState::update() {
	entityManager_->update();
	physicsWorld_->Step(1.0f / 60.0f, 6, 2);
	//también debería actualizar la lógica de modo de juego
	//spawners de monedas, carga de objetivos...
}
void PlayState::render() {
	SDL_RenderClear(SDL_Game::instance()->getRenderer());

	entityManager_->render();

	SDL_RenderPresent(SDL_Game::instance()->getRenderer());
}
void PlayState::handleInput() {
	entityManager_->handleInput();
}