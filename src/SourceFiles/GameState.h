#pragma once
#include "EntityManager.h"
#include "box2d.h"
#include "checkML.h"

class GameState
{
protected:
	EntityManager* entityManager_;
	//HUD
#pragma region Debug
	void DebugInput();
#pragma endregion

public:
	GameState();
	virtual ~GameState();
	virtual void init();
	virtual void update();
	virtual void render();
	virtual void handleInput();
	EntityManager* getEntityManager() { return entityManager_; }
};

