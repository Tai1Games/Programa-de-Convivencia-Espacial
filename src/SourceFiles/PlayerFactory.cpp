#include "PlayerFactory.h"

Entity* PlayerFactory::createBasePlayer(EntityManager* eMan, b2World* physicsWorld, int playerID, int playerTextureID, int posX, int posY) {
	Entity* p = eMan->addEntity();
	Collider* collP = p->addComponent<Collider>(physicsWorld, b2_dynamicBody, posX, posY, 1, 1, 1, 0.1, 0.2, 0, 0, Collider::CollisionLayer::Player, false);
	collP->setUserData(p);
	p->addComponent<PlayerData>(playerID);
	p->addComponent<Viewer>(playerTextureID);
	if (playerID == 0) {
	p->addComponent<Hands>(Resources::Hands);
	p->addComponent<AttachesToObjects>();
	p->addComponent<PlayerController>();
	p->addComponent<ImpulseViewer>(Resources::FlechaImpulso, Resources::ImpulsoBackground);
	}
	return p;
}

Entity* PlayerFactory::createPlayerWithHealth(EntityManager* eMan, b2World* physicsWorld, int playerID, int playerTextureID, int posX, int posY, int healthPoints) {
	Entity* p = createBasePlayer(eMan, physicsWorld, playerID, playerTextureID, posX, posY);
	p->addComponent<Health>(healthPoints);
	p->addComponent<HealthViewer>(Resources::ActiveHealth, Resources::DisableHealth);
	return p;
}

Entity* PlayerFactory::createPlayerWithWallet(EntityManager* eMan, b2World* physicsWorld, int playerID, int playerTextureID, int posX, int posY) {
	Entity* p = createBasePlayer(eMan, physicsWorld, playerID, playerTextureID, posX, posY);
	p->addComponent<Wallet>();
	return p;
}