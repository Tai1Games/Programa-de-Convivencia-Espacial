#include "PlayState.h"
#include "Transform.h"
#include "Viewer.h"
#include "Health.h"
#include "HealthViewer.h"
#include "InputHandler.h"

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
	Collider* collTinky = tinky->addComponent<Collider>(physicsWorld_, b2_dynamicBody, 150, 80, 50, 50, 50, 0, false);
	Collider* collSuelo = ground->addComponent<Collider>(physicsWorld_, b2_staticBody, 0, 500, 1000, 10, 50, 0, false);
	Collider* collRock = rock->addComponent<Collider>(physicsWorld_, b2_dynamicBody, 500, 80, 20, 20, 10, 0, false);
	//Transform* tr = tinky->addComponent<Transform>(tinkyBody);
	//Transform* trG = ground->addComponent<Transform>(wallBody);
	tinky->addComponent<Viewer>(Resources::Tinky);		//  <-- se puede poner un sprite con esta constructora, pero por defecto sale un tinky.
	tinky->addComponent<Health>(3);
	tinky->addComponent<HealthViewer>(Resources::ActiveHealth, Resources::DisableHealth, b2Vec2(20, 20));

	ground->addComponent<Viewer>();						//  también se puede poner un SDL_Rect para el clip (después de la textura)
	rock->addComponent < Viewer >();
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
	DebugInput();


}

void PlayState::DebugInput() {
	InputHandler* ih = SDL_Game::instance()->getInputHandler();
	ih->update();
	if (ih->isButtonJustDown(0, SDL_CONTROLLER_BUTTON_A)) {
		cout << "just pressed A" << endl;
	}
	if (ih->isButtonJustDown(0, SDL_CONTROLLER_BUTTON_B)) {
		cout << "just pressed B" << endl;
	}
	if (ih->isButtonJustUp(0, SDL_CONTROLLER_BUTTON_A)) {
		cout << "just released A" << endl;
	}
	if (ih->isButtonJustUp(0, SDL_CONTROLLER_BUTTON_B)) {
		cout << "just released B" << endl;
	}
	if (ih->isButtonDown(0, SDL_CONTROLLER_BUTTON_A)) {
		cout << "AAAAAAAAA" << endl;
	}
	if (ih->isButtonDown(0, SDL_CONTROLLER_BUTTON_B)) {
		cout << "BBBBBBB" << endl;
	}
	b2Vec2 vI = ih->getStickDir(0, InputHandler::GAMEPADSTICK::LEFTSTICK);
	b2Vec2 vD = ih->getStickDir(0, InputHandler::GAMEPADSTICK::RIGHTSTICK);
	if (vI.Length() != 0 || vD.Length() != 0) {
		b2Vec2 vI = ih->getStickDir(0, InputHandler::LEFTSTICK);
		b2Vec2 vD = ih->getStickDir(0, InputHandler::RIGHTSTICK);
		cout << "Izq: " << vI.x << " " << vI.y << endl;
		cout << "Der: " << vD.x << " " << vD.y << endl;
		cout << endl;
	}
	double tD = ih->getTrigger(0, InputHandler::GAMEPADTRIGGER::LEFTTRIGGER);
	double tI = ih->getTrigger(0, InputHandler::GAMEPADTRIGGER::RIGHTTRIGGER);
	if (tD != 0 || tI != 0) {
		cout << "Izq: " << tI<< endl;
		cout << "Der: " << tD << endl;
		cout << endl;
	}
}