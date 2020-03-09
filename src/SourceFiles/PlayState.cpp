#include "PlayState.h"
#include "Transform.h"
#include "Viewer.h"
#include "Health.h"
#include "HealthViewer.h"
#include "InputHandler.h"

PlayState::PlayState()  {
}

PlayState::~PlayState() {
}

void PlayState::init() {
	//aqui se crean todas las entidades necesarias
	//se podría JSONizar para evitar compilar
	entityManager_ = new EntityManager();
	physicsWorld_ = new b2World(b2Vec2(0, 0));

	Entity* tinky = entityManager_->addEntity();
	Entity* ground = entityManager_->addEntity();
	Entity* pared = entityManager_->addEntity();
	//Entity* rock = entityManager_->addEntity();
	//Entity* spaceJunk = entityManager_->addEntity();
																			// x, y, width, height,			density,	friction,	restitution,	linearDrag,		angularDrag,	groupIndex,	sensor
	Collider* collTinky = tinky->addComponent<Collider>(physicsWorld_, b2_dynamicBody, 1.7, 8, 1, 1,		1,			0.1,		0.2,			0,				0,				1,			false);
	Collider* collSuelo = ground->addComponent<Collider>(physicsWorld_, b2_staticBody, 10.5, -0.5, 12,1,	10,			0,			0.2,			0,				0,				1,			false);
	Collider* collpared = pared->addComponent<Collider>(physicsWorld_, b2_staticBody, 21.5, 10, 1, 10,		10,			1,			0.2,			0,				0,				1,			false);
	//Collider* collRock = rock->addComponent<Collider>(physicsWorld_, b2_dynamicBody, 500, 80, 20, 20,   10, 0, 0, 0.1, false);
	//Collider* collJunk = spaceJunk->addComponent<Collider>(physicsWorld_, b2_dynamicBody, 300, 60, 30, 30,   20, 1000000000000000, 0.8, 0, false);

	cout<<collTinky->getMass();

	tinky->addComponent<Viewer>(Resources::Tinky);		//  <-- se puede poner un sprite con esta constructora, pero por defecto sale un cuadrado de debug.
	tinky->addComponent<Health>(3);
	tinky->addComponent<HealthViewer>(Resources::ActiveHealth, Resources::DisableHealth, b2Vec2(20, 20));
	ground->addComponent<Viewer>();
	pared->addComponent<Viewer>();
	//rock->addComponent <Viewer>();

	//spaceJunk->addComponent<Viewer>();

	//cout << collJunk->getMass();

	collTinky->applyLinearImpulse(b2Vec2(40, -30), b2Vec2(0.1, 0));
	//tr->getBody()->ApplyForce(b2Vec2 (0, -200), b2Vec2(0, 0), true);
	//tr->getBody()->ApplyLinearImpulse(b2Vec2(0, -100), b2Vec2(0, 0),true);

	//collRock->createFixture(100, 100, 10, 0, 0, 0, true);

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
	GameState::handleInput();
	entityManager_->handleInput();

}
