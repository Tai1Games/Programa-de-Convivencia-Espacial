#pragma once
#include "EntityManager.h"
#include "box2d.h"
#include "checkML.h"

class GameState
{
protected:
	EntityManager* entityManager_ = nullptr;
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
	virtual void resetScene();
	EntityManager* getEntityManager() { return entityManager_; }
};

