#include "PlayerFactory.h"
#include "CapitalismGameMode.h"
#include "ColliderViewer.h"
#include "ImpulseViewer.h"
#include "HealthViewer.h"
#include "Viewer.h"
#include "PlayerData.h"

Entity* PlayerFactory::createBasePlayer(EntityManager* eMan, b2World* physicsWorld, int playerID, int playerTextureID, int posX, int posY) {
	Entity* p = eMan->addEntity();
	Collider* collP = p->addComponent<Collider>(physicsWorld, b2_dynamicBody, posX, posY, CONST(double, "PLAYER_HEIGTH"), CONST(double, "PLAYER_WIDTH"), CONST(double, "PLAYER_DENSITY"), CONST(double, "PLAYER_FRICTION"), CONST(double, "PLAYER_RESTITUTION"), CONST(double, "PLAYER_LINEAR_DRAG"), CONST(double, "PLAYER_ANGULAR_DRAG"), Collider::CollisionLayer::Player, false);
	p->addComponent<PlayerData>(playerID);
	p->addComponent<Viewer>(playerTextureID);
	if (playerID == 0) {
	p->addComponent<Hands>(Resources::Hands);
	p->addComponent<AttachesToObjects>();
	p->addComponent<PlayerController>();
	p->addComponent<ImpulseViewer>(Resources::ImpulseArrow, Resources::ImpulseBackground);
	}
	p->addComponent<ColliderViewer>();

	return p;
}

Entity* PlayerFactory::createPlayerWithHealth(EntityManager* eMan, b2World* physicsWorld, int playerID, int playerTextureID, int posX, int posY, int healthPoints) {
	Entity* p = createBasePlayer(eMan, physicsWorld, playerID, playerTextureID, posX, posY);
	p->addComponent<Health>(healthPoints);
	p->addComponent<HealthViewer>(Resources::ActiveHealth, Resources::DisableHealth);
	return p;
}

Entity* PlayerFactory::createPlayerWithWallet(EntityManager* eMan, b2World* physicsWorld, int playerID, int playerTextureID, int posX, int posY, CapitalismGameMode* gM) {
	Entity* p = createBasePlayer(eMan, physicsWorld, playerID, playerTextureID, posX, posY);
	p->addComponent<Wallet>(gM);
	return p;
}