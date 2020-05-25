#pragma once

#include "Entity.h"
#include "Component.h"
#include "Health.h"
#include "Hands.h"
#include "AttachesToObjects.h"
#include "PlayerController.h"
#include "Wallet.h"
#include "Resource.h"
#include "EntityManager.h"
#include "b2_world.h"

class CapitalismGameMode;
class InputBinder;

class PlayerFactory {
public:
	static Entity* createBasePlayer(EntityManager* eMan, b2World* physicsWorld, int playerID, int playerTextureID, int posX, int posY, InputBinder* ib);

	PlayerFactory() {}
	~PlayerFactory() {}

	static Entity* createPlayerWithHealth(EntityManager* eMan, b2World* physicsWorld, int playerID, int playerTextureID, int posX, int posY, InputBinder* ib, int healthPoints);
	static Entity* createPlayerWithWallet(EntityManager* eMan, b2World* physicsWorld, int playerID, int playerTextureID, int posX, int posY, InputBinder* ib, CapitalismGameMode* gM);
};
