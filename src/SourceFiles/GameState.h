#pragma once
#include "EntityManager.h"
#include "box2d.h"
#include "checkML.h"

class GameState
{
protected:
	bool exit_ = false;
	EntityManager* entityManager_;
	//HUD
#pragma region Debug
	void DebugInput();
#pragma endregion

public:
	GameState();
	virtual ~GameState();
	virtual void init() {};
	virtual void update();
	virtual void render();
	virtual void handleInput();
	virtual bool isExit() { return exit_; };
	EntityManager* getEntityManager() { return entityManager_; }
};

