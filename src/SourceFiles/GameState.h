#pragma once
#include "EntityManager.h"
#include "box2d.h"
#include "checkML.h"

class GameState
{
protected:
	EntityManager* entityManager_;
	b2World* physicsWorld_;
	std::vector<b2Body*> physicalEntities_; //almacena los punteros a los colliders de b2
	//puede que no sea necesario si cogemos la referencia en cuanto los creamos con addPhysicalEntity
	b2Body* addPhysicalEntity(/*PARÁMETROS PARA PODER CREAR UN BODY*/);  //añade una entidad fisica
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
};

