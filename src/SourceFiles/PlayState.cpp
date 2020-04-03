#include "PlayState.h"
#include "Transform.h"
#include "AttachesToObjects.h"
#include "Texture.h"
#include "Viewer.h"
#include "Health.h"
#include "HealthViewer.h"
#include "InputHandler.h"
#include "CollisionHandler.h"
#include "TileMap.h"
#include "Tileson.h"
#include "Weapon.h"
#include "Hands.h"
#include "PlayerController.h"
#include "WeaponFactory.h"
#include "ImpulseViewer.h"
#include "PlayerData.h"

PlayState::PlayState(GameMode* gMode):GameState(),
	gameMode_(gMode) {}
PlayState::~PlayState() {
}

void PlayState::init() {
	//aqui se crean todas las entidades necesarias
	//se podría JSONizar para evitar compilar
	entityManager_ = new EntityManager();
	physicsWorld_ = new b2World(b2Vec2(0, 0));

	TileMap* tilemap = new TileMap(CONST(double, "WINDOW_WIDTH"), CONST(double, "WINDOW_HEIGHT"),
		"../../assets/game/tilemaps/SalaDeEstar.json",
		entityManager_, physicsWorld_);
	tilemap->init();
	gameMode_->setTileMap(tilemap);

	collisionHandler_ = new CollisionHandler(gameMode_, tilemap);
	physicsWorld_->SetContactListener(collisionHandler_);


	//Entity* tinky = entityManager_->addEntity();
	//Entity* tonko = entityManager_->addEntity();
	//Entity* tunko = entityManager_->addEntity();
	//Entity* tanko = entityManager_->addEntity();
	////Entity* spaceJunk = entityManager_->addEntity();

	///*players_.push_back(tinky);
	//players_.push_back(tonko);
	//players_.push_back(tunko);
	//players_.push_back(tanko);*/

	////Colliders
	//                                                                                      //             x,						    	  y,			     	width, height, density,	friction, restitution, linearDrag, angularDrag,	               Layer,			        sensor
	//Collider* collTinky = tinky->addComponent<Collider>(physicsWorld_, b2_dynamicBody,      tilemap->getPlayerSpawnPoint(0).x, tilemap->getPlayerSpawnPoint(0).y, 1,     1,      1,         0.1,      0.2,         0,          0,           Collider::CollisionLayer::Player,       false);
	//Collider* collTonko = tonko->addComponent<Collider>(physicsWorld_, b2_dynamicBody,	    tilemap->getPlayerSpawnPoint(1).x, tilemap->getPlayerSpawnPoint(1).y, 1,     1,      1,         0.1,      0.2,         0,          0,           Collider::CollisionLayer::Player,       false);
	//Collider* collTunko = tunko->addComponent<Collider>(physicsWorld_, b2_dynamicBody,		tilemap->getPlayerSpawnPoint(2).x, tilemap->getPlayerSpawnPoint(2).y, 1,     1,      1,         0.1,      0.2,         0,          0,           Collider::CollisionLayer::Player,       false);
	//Collider* collTanko = tanko->addComponent<Collider>(physicsWorld_, b2_dynamicBody,	    tilemap->getPlayerSpawnPoint(3).x, tilemap->getPlayerSpawnPoint(3).y, 1,	 1,		 1,		    0.1,	  0.2,		   0,		   0,			Collider::CollisionLayer::Player,		false);

	//FONDO
	fondo_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::SalaDeEstar);

	////Players
	//tinky->addComponent<PlayerData>(0);
	//tinky->addComponent<Viewer>(Resources::Tinky);		//  <-- se puede poner un sprite con esta constructora, pero por defecto sale un cuadrado de debug.
	//tinky->addComponent<Health>(3);
	//tinky->addComponent<HealthViewer>(Resources::ActiveHealth, Resources::DisableHealth);
	//tinky->addComponent<Hands>(Resources::Hands);
	//tinky->addComponent<AttachesToObjects>();
	//tinky->addComponent<PlayerController>();
	//collTinky->setUserData(tinky);
	//tinky->addComponent<ImpulseViewer>(Resources::FlechaImpulso,Resources::ImpulsoBackground);

	//tonko->addComponent<PlayerData>(1);
	//tonko->addComponent<Viewer>(Resources::Tinky);
	//tonko->addComponent<Health>(3);
	//tonko->addComponent<HealthViewer>(Resources::ActiveHealth, Resources::DisableHealth);
	//collTonko->setUserData(tonko);

	//tanko->addComponent<PlayerData>(3);
	//tanko->addComponent<Viewer>(Resources::Tinky);
	//tanko->addComponent<Health>(3);
	//tanko->addComponent<HealthViewer>(Resources::ActiveHealth, Resources::DisableHealth);
	//collTanko->setUserData(tanko);

	//tunko->addComponent<PlayerData>(2);
	//tunko->addComponent<Viewer>(Resources::Tinky);
	//tunko->addComponent<Health>(3);
	//tunko->addComponent<HealthViewer>(Resources::ActiveHealth, Resources::DisableHealth);
	//collTunko->setUserData(tunko);

	//Objetos flotantes


	//Fuerzas iniciales
	//collTinky->applyLinearImpulse(b2Vec2(20, -10), b2Vec2(1, 1));
	//collTonko->applyLinearImpulse(b2Vec2(0, 1000), b2Vec2(0.1, 0));

	//Version estática de la factoria
	tilemap->executeMapFactory();

	gameMode_->init(this);
}

void PlayState::update() {
	GameState::update();
	//double d = SDL_Game::instance()->getConstants()->getConstant<double>((std::string)"SECONDS_PER_FRAME");
	//el que vuelva tocar el step de physicsworld muere
	physicsWorld_->Step(CONST(double,"SECONDS_PER_FRAME"), 6, 2);
	collisionHandler_->SolveInteractions();
	createDeadBodies();
	//también debería actualizar la lógica de modo de juego
	//spawners de monedas, carga de objetivos...
	gameMode_->update();
}

void PlayState::render() {
	fondo_->render(0,0);
	GameState::render();
	gameMode_->render();
}

void PlayState::handleInput()
{
	GameState::handleInput();
	InputHandler* ih = SDL_Game::instance()->getInputHandler();
	for (int i = 0; i < ih->getNumControllers(); i++) {
		if (ih->isButtonJustUp(i, SDL_CONTROLLER_BUTTON_START) ||
			ih->isButtonJustUp(i, SDL_CONTROLLER_BUTTON_GUIDE)) {
			SDL_Game::instance()->getStateMachine()->setPauseOwner(i);
		}
	}
}

void PlayState::createDeadBodies() {
	auto bodies = collisionHandler_->getBodyData();
	for (int i = 0; i < bodies.size(); i++) {
		deadBodies.push_back(entityManager_->addEntity());
		collDeadBodies.push_back(deadBodies.back()->addComponent<Collider>(physicsWorld_, b2_dynamicBody, bodies[i].pos.x, bodies[i].pos.y, 1, 1, 1, 0.1, 0.2, 0, 0, Collider::CollisionLayer::NormalObject, false));
		deadBodies.back()->addComponent<Viewer>(Resources::PinkTinky);
		collDeadBodies.back()->setUserData(deadBodies.back());
		collDeadBodies.back()->setTransform(b2Vec2(bodies[i].pos.x, bodies[i].pos.y), bodies[i].angle);
	}
	collisionHandler_->clearBodyData();
}
