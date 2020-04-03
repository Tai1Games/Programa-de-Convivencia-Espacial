#pragma once

#include "Entity.h"
#include "Component.h"
#include "PlayerData.h"
#include "Viewer.h"
#include "Health.h"
#include "HealthViewer.h"
#include "Hands.h"
#include "AttachesToObjects.h"
#include "PlayerController.h"
#include "ImpulseViewer.h"
#include "Resource.h"
#include "EntityManager.h"
#include "b2_world.h"

class PlayerFactory {
private:
	static Entity* createBasePlayer(EntityManager* eMan, b2World* physicsWorld, int playerID, int playerTextureID, int posX, int posY);
public:
	PlayerFactory() {}
	~PlayerFactory() {}

	static Entity* createPlayerWithHealth(EntityManager* eMan, b2World* physicsWorld, int playerID, int playerTextureID, int posX, int posY, int healthPoints);
};
