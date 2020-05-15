#include "PlayableMenuState.h"
#include "Transform.h"
#include "AttachesToObjects.h"
#include "Texture.h"
#include "Viewer.h"
#include "Health.h"
#include "HealthViewer.h"
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
#include "Countdown.h"

#include "PlayerFactory.h"

PlayableMenuState::PlayableMenuState(string tmap) : tilemap(tmap) {}

PlayableMenuState::~PlayableMenuState()
{
	delete tmap;				tmap = nullptr;
	delete entityManager_;		entityManager_ = nullptr;
	delete collisionHandler_;	collisionHandler_ = nullptr;
	delete physicsWorld_;		physicsWorld_ = nullptr;
}

void PlayableMenuState::init()
{
	entityManager_ = new EntityManager();
	physicsWorld_ = new b2World(b2Vec2(0, 0));

	secondsPerFrame_ = CONST(double, "SECONDS_PER_FRAME");

	BulletPool bulletPool_;
	ConfettiPool confettiPool_;

	tmap = new TileMap(CONST(double, "WINDOW_WIDTH"), CONST(double, "WINDOW_HEIGHT"),
		"assets/game/tilemaps/TutorialRoom.json",
		entityManager_, physicsWorld_, &bulletPool_, &confettiPool_, nullptr);
	tmap->init();
	


	collisionHandler_ = new CollisionHandler(nullptr, tmap);
	physicsWorld_->SetContactListener(collisionHandler_);


	//FONDO
	fondo_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::LivingRoom);

	//MÚSICA
	SDL_Game::instance()->getAudioMngr()->playMusic(Resources::MainMenuMusic, -1);

	//Version estática de la factoria
	tmap->executeMapFactory();
	tmap->createWeapons();


	ObjectFactory::makeCarnivorousePlant(entityManager_, physicsWorld_, b2Vec2(15, 3), b2Vec2(6, 6));

	//gameMode_->init(this);

	playerInfo = SDL_Game::instance()->getStateMachine()->getMatchInfo()->getPlayersInfo();
	MatchInfo* aux = SDL_Game::instance()->getStateMachine()->getMatchInfo();
	Entity* player = PlayerFactory::createBasePlayer(entityManager_, physicsWorld_, 0,
		Resources::Body, 13, 13, aux->getPlayersInfo()->at(0)->inputBinder);
	
	
	player->addComponent<Hands>(Resources::Hands);
	player->addComponent<AttachesToObjects>();
	player->addComponent<PlayerController>();
	player->addComponent<ImpulseViewer>(Resources::ImpulseArrow, Resources::ImpulseBackground);
	
}

void PlayableMenuState::update()
{
	GameState::update();
	//double d = SDL_Game::instance()->getConstants()->getConstant<double>((std::string)"SECONDS_PER_FRAME");
	//el que vuelva tocar el step de physicsworld muere
	physicsWorld_->Step(secondsPerFrame_, 6, 2);
	
	collisionHandler_->SolveInteractions();
}

void PlayableMenuState::render()
{
	fondo_->render(0, 0);
	GameState::render();
}

void PlayableMenuState::handleInput()
{
	GameState::handleInput();
	for (MatchInfo::PlayerInfo* pInfo : *playerInfo)
	{
		if (pInfo->inputBinder->pressPause()) {
			SDL_Game::instance()->getAudioMngr()->pauseMusic();
			SDL_Game::instance()->getStateMachine()->setPauseOwner(pInfo->playerId);
			//SDL_Game::instance()->getStateMachine()->transitionToState(States::pause);
		}
	}
}
