#include "PlayState.h"

PlayState::PlayState() :
	eManager_(nullptr),
	physicsWorld(new b2World(b2Vec2(0,0))) {
}

void PlayState::init() {
	//aqui se crean todas las entidades necesarias
	//se podría JSONizar para evitar compilar
}
void PlayState::update() {
	eManager_->update();
	//también debería actualizar la lógica de modo de juego
	//spawners de monedas, carga de objetivos...
}
void PlayState::render() {
	eManager_->render();
}
void PlayState::handleInput() {
	eManager_->handleInput();
}