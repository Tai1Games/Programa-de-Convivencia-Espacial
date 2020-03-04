#include "PlayState.h"
#include "Transform.h"
#include "Viewer.h"

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
	physicsWorld_ = new b2World(b2Vec2(0, 0));

	Entity* tinky = entityManager_->addEntity();
	Entity* ground = entityManager_->addEntity();
	Entity* rock = entityManager_->addEntity();
	Entity* spaceJunk = entityManager_->addEntity();

	Collider* collTinky = tinky->addComponent<Collider>(physicsWorld_, b2_dynamicBody, 150, 80, 50, 50, 50, 0, 0, false);
	Collider* collSuelo = ground->addComponent<Collider>(physicsWorld_, b2_staticBody, 0, 500, 1000, 10, 0.1, 10, 0.0, false);
	Collider* collRock = rock->addComponent<Collider>(physicsWorld_, b2_dynamicBody, 150, 200, 20, 20, 10, 0, 0, false);
	Collider* collJunk = spaceJunk->addComponent<Collider>(physicsWorld_, b2_dynamicBody, 300, 60, 30, 30, 20, 0.1, 0.0, false);
	//Transform* tr = tinky->addComponent<Transform>(tinkyBody);
	//Transform* trG = ground->addComponent<Transform>(wallBody);
	tinky->addComponent<Viewer>(Resources::Tinky);		//  <-- se puede poner un sprite con esta constructora, pero por defecto sale un tinky.
	ground->addComponent<Viewer>();						//  también se puede poner un SDL_Rect para el clip (después de la textura)
	rock->addComponent < Viewer >();
	spaceJunk->addComponent<Viewer>();

	cout << collJunk->getMass();
	collJunk->applyForce(b2Vec2(0, 300000000), b2Vec2(0, 0), true);
	//tr->getBody()->ApplyForce(b2Vec2 (0, -200), b2Vec2(0, 0), true);
	//tr->getBody()->ApplyLinearImpulse(b2Vec2(0, -100), b2Vec2(0, 0),true);
}

void PlayState::update() {
	entityManager_->update();
	physicsWorld_->Step(1.0f / 240.0f, 6, 2);
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
