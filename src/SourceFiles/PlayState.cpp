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
#include "ParticleEmitter.h"

PlayState::PlayState(GameMode* gMode, string tmap):GameState(),
	gameMode_(gMode), tilemapName_(tmap) {}


PlayState::~PlayState() {
	//for (Entity* i : deadBodies) { delete i; }
	//for (Collider* i : collDeadBodies) { delete i; }
	delete gameMode_;			gameMode_ = nullptr;
	delete tilemap_;			tilemap_ = nullptr;
	delete entityManager_;		entityManager_ = nullptr;
	delete collisionHandler_;	collisionHandler_ = nullptr;
	delete physicsWorld_;		physicsWorld_ = nullptr;
}

void PlayState::init() {
	//aqui se crean todas las entidades necesarias
	//se podría JSONizar para evitar compilar
	entityManager_ = new EntityManager();
	physicsWorld_ = new b2World(b2Vec2(0, 0));

	tilemap_ = new TileMap(CONST(double, "WINDOW_WIDTH"), CONST(double, "WINDOW_HEIGHT"),
		"../../assets/game/tilemaps/"+tilemapName_+".json",
		entityManager_, physicsWorld_);
	tilemap_->init();
	gameMode_->setTileMap(tilemap_);

	collisionHandler_ = new CollisionHandler(gameMode_, tilemap_);
	physicsWorld_->SetContactListener(collisionHandler_);

	//PLAYERS
	vector<Collider*> colliders;
	for (int i = 0; i < 4; i++) {
		players_.push_back(entityManager_->addEntity());
		colliders.push_back(players_[i]->addComponent<Collider>(physicsWorld_, b2_dynamicBody, tilemap_->getPlayerSpawnPoint(i).x, tilemap_->getPlayerSpawnPoint(i).y,
			1, 1.55, 1, 0.1, 0.2, 0, 0, Collider::CollisionLayer::Player, false));
		players_[i]->addComponent<PlayerData>(i);
		players_[i]->addComponent<Viewer>(Resources::Body);
		players_[i]->addComponent<Health>(3);
		players_[i]->addComponent<HealthViewer>(Resources::ActiveHealth, Resources::DisableHealth);
		if (i == 0) { //si solo hay un mando
			players_[i]->addComponent<Hands>(Resources::Hands);
			players_[i]->addComponent<AttachesToObjects>();
			players_[i]->addComponent<PlayerController>();
			players_[i]->addComponent<ImpulseViewer>(Resources::FlechaImpulso, Resources::ImpulsoBackground);
		}
		colliders[i]->setUserData(players_[i]);
	}

	//Particle test
	ParticleEmitter* test = players_[0]->addComponent<ParticleEmitter>(Vector2D(.5,.5),Resources::Grapadora,3.5,1000, 25, 0,2,15);
	test->PlayStop();

	//FONDO
	fondo_ = SDL_Game::instance()->getTexturesMngr()->getTexture(resourceMap_[tilemapName_]);

	//Version estática de la factoria
	tilemap_->executeMapFactory();

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
		collDeadBodies.push_back(deadBodies.back()->addComponent<Collider>(physicsWorld_, b2_dynamicBody, bodies[i].pos.x, bodies[i].pos.y, 1, 1, 1, 0.1, 0.2, 0, 0, Collider::CollisionLayer::NormalAttachableObject, false));
		deadBodies.back()->addComponent<Viewer>(Resources::PinkTinky);
		collDeadBodies.back()->setUserData(deadBodies.back());
		collDeadBodies.back()->setTransform(b2Vec2(bodies[i].pos.x, bodies[i].pos.y), bodies[i].angle);
	}
	collisionHandler_->clearBodyData();
}
