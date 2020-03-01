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
	tinky->addComponent<Transform>(Vector2D(200.0,200.0),0.0,100.0,100.0);
	tinky->addComponent<Viewer>();

}
void PlayState::update() {
	entityManager_->update();
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