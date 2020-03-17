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

PlayState::PlayState()  {
}

PlayState::~PlayState() {
}

void PlayState::init() {
	//aqui se crean todas las entidades necesarias
	//se podría JSONizar para evitar compilar
	entityManager_ = new EntityManager();
	physicsWorld_ = new b2World(b2Vec2(0, 0));
	collisionHandler_ = new CollisionHandler();
	physicsWorld_->SetContactListener(collisionHandler_);

	Entity* map = entityManager_->addEntity();
	Entity* tinky = entityManager_->addEntity();
	Entity* ground = entityManager_->addEntity();
	Entity* pared = entityManager_->addEntity();
	Entity* rock = entityManager_->addEntity();


	//Entity* spaceJunk = entityManager_->addEntity();

	map->addComponent<TileMap>(WINDOW_WIDTH, WINDOW_HEIGHT,
		"../../assets/game/tilemaps/TD_TilemapBitCSV.json");

	Entity* tonko = entityManager_->addEntity();
	Entity* spaceJunk = entityManager_->addEntity();

	//Colliders
	                                                                                      // x,  y,   width, height, density,	friction, restitution, linearDrag, angularDrag,	Layer,							        sensor canBeAttached
	Collider* collTinky = tinky->addComponent<Collider>(physicsWorld_, b2_dynamicBody,    4,    8,    1,     1,      1,         0.1,      0.2,         0,          0,           Collider::CollisionLayer::Player,       false, false);
	Collider* collSuelo = ground->addComponent<Collider>(physicsWorld_, b2_staticBody,    10.5, -0.5, 12,    1,      10,        0,        0.2,         0,          0,           Collider::CollisionLayer::NormalObject, false, true);
	Collider* collpared = pared->addComponent<Collider>(physicsWorld_, b2_staticBody,     21.5, 10,   1,     10,     10,        1,        0.2,         0,          0,           Collider::CollisionLayer::NormalObject, false, true);
	Collider* collRock = rock->addComponent<Collider>(physicsWorld_, b2_dynamicBody,      18,   8,    0.5,   0.5,    1,         10,       0,           0,          0.1,         Collider::CollisionLayer::NormalObject, false, true);
	Collider* collJunk = spaceJunk->addComponent<Collider>(physicsWorld_, b2_dynamicBody, 0,    8.25,   1,     1,    1,         0.1,      0.2,         0,          0,           Collider::CollisionLayer::NormalObject, false, true);
	Collider* collTonko = tonko->addComponent<Collider>(physicsWorld_, b2_dynamicBody,    7,    3,    1,     1,      1,         0.1,      0.2,         0,          0,           Collider::CollisionLayer::Player,       false, false);

	//Players
	tinky->addComponent<Viewer>(Resources::Tinky);		//  <-- se puede poner un sprite con esta constructora, pero por defecto sale un cuadrado de debug.
	tinky->addComponent<Health>(3);
	tinky->addComponent<HealthViewer>(Resources::ActiveHealth, Resources::DisableHealth, b2Vec2(20, 20));
	tinky->addComponent<Hands>(0, Resources::Hands);
	tinky->addComponent<AttachesToObjects>(0);
	collTinky->setUserData(tinky);
	tinky->addComponent<PlayerController>(0);

	tonko->addComponent<Viewer>(Resources::Tinky);
	tonko->addComponent<Health>(3);
	tonko->addComponent<HealthViewer>(Resources::ActiveHealth, Resources::DisableHealth, b2Vec2(250, 20));
	collTonko->setUserData(tonko);
	//Muros
	ground->addComponent<Viewer>();
	collSuelo->setUserData(ground);
	pared->addComponent<Viewer>();
	collpared->setUserData(pared);

	//Objetos flotantes
	rock->addComponent <Viewer>(Resources::PinkTinky);
	rock->addComponent<Weapon>(WeaponID::PinkTinky);
	collRock->setUserData(rock);

	spaceJunk->addComponent<Viewer>();
	collJunk->setUserData(spaceJunk);

	//Fuerzas iniciales
	collTinky->applyLinearImpulse(b2Vec2(20, -10), b2Vec2(1, 1));
	//collTonko->applyLinearImpulse(b2Vec2(0, 1000), b2Vec2(0.1, 0));
	collJunk->applyLinearImpulse(b2Vec2(150, 0), b2Vec2(0.1, 0));

}

void PlayState::update() {
	GameState::update();
	//el que vuelva tocar el step de physicsworld muere
	physicsWorld_->Step(SECONDS_PER_FRAME, 6, 2);
	collisionHandler_->SolveInteractions();
	//también debería actualizar la lógica de modo de juego
	//spawners de monedas, carga de objetivos...
}
