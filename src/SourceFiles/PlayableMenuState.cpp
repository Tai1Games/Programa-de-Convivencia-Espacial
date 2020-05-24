#include "PlayableMenuState.h"
#include "Transform.h"
#include "AttachesToObjects.h"
#include "Texture.h"
#include "Viewer.h"
#include "InputBinder.h"
#include "CollisionHandler.h"
#include "TileMap.h"
#include "Tileson.h"
#include "Weapon.h"
#include "Hands.h"
#include "PlayerController.h"
#include "ObjectFactory.h"
#include "ImpulseViewer.h"
#include "PlayerData.h"
#include "ParticleEmitter.h"
#include "GameStateMachine.h"
#include "ThrownByPlayer.h"
#include "Component.h"

#include "PlayerFactory.h"


PlayableMenuState::~PlayableMenuState()
{
	delete tmap;				tmap = nullptr;
	delete entityManager_;		entityManager_ = nullptr;
	delete collisionHandler_;	collisionHandler_ = nullptr;
	delete physicsWorld_;		physicsWorld_ = nullptr;
	delete playerControl;       playerControl = nullptr;
}

void PlayableMenuState::init()
{
	entityManager_ = new EntityManager();
	physicsWorld_ = new b2World(b2Vec2(0, 0));

	secondsPerFrame_ = CONST(double, "SECONDS_PER_FRAME");

	BulletPool bulletPool_;
	ConfettiPool confettiPool_;
	StaplerPool staplerPool_;

	tmap = new TileMap(CONST(double, "WINDOW_WIDTH"), CONST(double, "WINDOW_HEIGHT"),
		"assets/game/tilemaps/MenuRoom.json",
		entityManager_, physicsWorld_, &bulletPool_, &confettiPool_, &staplerPool_, nullptr);
	tmap->init();

	collisionHandler_ = new CollisionHandler(nullptr, tmap);
	physicsWorld_->SetContactListener(collisionHandler_);

	//FONDO
	fondo_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::MenuRoom);

	//MÚSICA
	SDL_Game::instance()->getAudioMngr()->playMusic(Resources::MainMenuMusic, -1);

	//Version estática de la factoria
	tmap->executeMapFactory();
	tmap->createWeapons();


	if (SDL_Game::instance()->getInputHandler()->getNumControllers() > 0) {
		playerControl = new ControllerBinder(0);
		player = PlayerFactory::createBasePlayer(entityManager_, physicsWorld_, 0,
			Resources::Body, tmap->getPlayerSpawnPoint(0).x, tmap->getPlayerSpawnPoint(0).y, playerControl);
	}
	else {
		playerControl = new MouseKeyboardBinder(nullptr, 1);
		player = PlayerFactory::createBasePlayer(entityManager_, physicsWorld_, 0,
			Resources::Body, tmap->getPlayerSpawnPoint(0).x, tmap->getPlayerSpawnPoint(0).y, playerControl);

		playerControl->setPlayerCol(player->getComponent<Collider>(ComponentType::Collider));
	}

	player->addComponent<Hands>(Resources::Hands);
	player->addComponent<AttachesToObjects>();
	player->addComponent<PlayerController>();
	player->addComponent<ImpulseViewer>(Resources::ImpulseArrow, Resources::ImpulseBackground);
}

void PlayableMenuState::update()
{
	GameState::update();
	//el que vuelva tocar el step de physicsworld muere
	physicsWorld_->Step(secondsPerFrame_, 6, 2);
	
	collisionHandler_->SolveInteractions();
}

void PlayableMenuState::render()
{
	fondo_->render(0, 0);
	GameState::render();
}

void PlayableMenuState::onLoaded()
{
	player->getComponent<Collider>(ComponentType::Collider)->setTransform(b2Vec2(tmap->getPlayerSpawnPoint(0).x, tmap->getPlayerSpawnPoint(0).y), 0);
}
