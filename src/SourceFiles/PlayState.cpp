#include "PlayState.h"
#include "Transform.h"
#include "Viewer.h"
#include "Health.h"
#include "HealthViewer.h"
#include "InputHandler.h"
#include "CollisionHandler.h"

PlayState::PlayState()  {
}

PlayState::~PlayState() {
}

void PlayState::init() {
	//aqui se crean todas las entidades necesarias
	//se podría JSONizar para evitar compilar
	entityManager_ = new EntityManager();
	physicsWorld_ = new b2World(b2Vec2(0, 9.8));
	
	Entity* tinky = entityManager_->addEntity();
	Entity* ground = entityManager_->addEntity();
	Entity* rock = entityManager_->addEntity();
	CollisionHandler* col = new CollisionHandler();
	physicsWorld_->SetContactListener(col);

	Collider* collTinky = tinky->addComponent<Collider>(physicsWorld_, b2_dynamicBody, 150, 80, 50, 50, 50, 0, 0,
		Collider::CollisionLayer::Normal, false);
	Collider* collSuelo = ground->addComponent<Collider>(physicsWorld_, b2_staticBody, 0, 500, 1000, 10, 50, 0, 0, 
		Collider::CollisionLayer::Normal, false);
	Collider* collRock = rock->addComponent<Collider>(physicsWorld_, b2_dynamicBody, 500, 80, 20, 20, 10, 0, 0, 
		Collider::CollisionLayer::Triggers, false);
	tinky->addComponent<Viewer>(Resources::Tinky);		//  <-- se puede poner un sprite con esta constructora, pero por defecto sale un tinky.
	tinky->addComponent<Health>(3);
	tinky->addComponent<HealthViewer>(Resources::ActiveHealth, Resources::DisableHealth, b2Vec2(20, 20));
	ground->addComponent<Viewer>();
	ground->addComponent<Health>(10);
	rock->addComponent < Viewer >();
}

void PlayState::update() {
	entityManager_->update();
	physicsWorld_->Step(1.0f / 1.0f, 6, 2);
	//también debería actualizar la lógica de modo de juego
	//spawners de monedas, carga de objetivos...
	
}
void PlayState::render() {
	SDL_RenderClear(SDL_Game::instance()->getRenderer());

	entityManager_->render();

	SDL_RenderPresent(SDL_Game::instance()->getRenderer());
}
void PlayState::handleInput() {
	GameState::handleInput();
	entityManager_->handleInput();
	//DebugInput();
}

