#include "GameState.h"
#include "Constants.h"
#include "SDL.h"
#include "SDL_Game.h"

GameState::GameState() :
	entityManager_(nullptr),
	physicsWorld_(nullptr) {

}

GameState::~GameState() {
	delete entityManager_;
	entityManager_ = nullptr;
	delete physicsWorld_;
	physicsWorld_ = nullptr;
}

void GameState::init() {

}

void GameState::update() {
	entityManager_->update();
	physicsWorld_->Step(MS_PER_FRAME, 6, 2);
	//también debería actualizar la lógica de modo de juego
	//spawners de monedas, carga de objetivos...
}

void GameState::render() {
	SDL_RenderClear(SDL_Game::instance()->getRenderer());

	entityManager_->render();

	SDL_RenderPresent(SDL_Game::instance()->getRenderer());
}

void GameState::handleInput() {
	entityManager_->handleInput();
}