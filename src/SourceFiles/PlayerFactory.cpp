#include "PlayerFactory.h"
#include "CapitalismGameMode.h"
#include "ColliderViewer.h"
#include "ImpulseViewer.h"
#include "HealthViewer.h"
#include "Viewer.h"
#include "AnimatedPlayer.h"
#include "PlayerData.h"

Entity* PlayerFactory::createBasePlayer(EntityManager* eMan, b2World* physicsWorld, int playerID, int playerTextureID, int posX, int posY, InputBinder* ib, int skin) {
	Entity* p = eMan->addEntity();
	Collider::CollisionLayer layer = (Collider::CollisionLayer)(Collider::CollisionLayer::Player1 * (int)pow(2, playerID));
	Collider* collP = p->addComponent<Collider>(physicsWorld, b2_dynamicBody, posX, posY, CONST(double, "PLAYER_W_PHYSICS"), CONST(double, "PLAYER_H_PHYSICS"), CONST(double, "PLAYER_DENSITY"), CONST(double, "PLAYER_FRICTION"), CONST(double, "PLAYER_RESTITUTION"), CONST(double, "PLAYER_LINEAR_DRAG"), CONST(double, "PLAYER_ANGULAR_DRAG"), layer, false);
	p->addComponent<PlayerData>(playerID, ib);
	p->addComponent<Transform>(SDL_Rect{ 0,0, CONST(int, "PLAYER_W_SPRITE"), CONST(int, "PLAYER_H_SPRITE") }, collP);
	p->addComponent<AnimatedPlayer>(Resources::PlayerAnimSheet, CONST(int, "PLAYER_TIME_PER_FRAME"), skin);

	return p;
}

Entity* PlayerFactory::createPlayerWithHealth(EntityManager* eMan, b2World* physicsWorld, int playerID, int playerTextureID, int posX, int posY, InputBinder* ib, int healthPoints, int skin) {
	Entity* p = createBasePlayer(eMan, physicsWorld, playerID, playerTextureID, posX, posY, ib, skin);
	p->addComponent<Health>(healthPoints);

	p->addComponent<HealthViewer>(Resources::ActiveHealth, Resources::DisableHealth, skin);
	return p;
}

Entity* PlayerFactory::createPlayerWithWallet(EntityManager* eMan, b2World* physicsWorld, int playerID, int playerTextureID, int posX, int posY, InputBinder* ib, CapitalismGameMode* gM, int skin) {
	Entity* p = createBasePlayer(eMan, physicsWorld, playerID, playerTextureID, posX, posY, ib, skin);
	p->addComponent<Wallet>(gM);
	return p;
}