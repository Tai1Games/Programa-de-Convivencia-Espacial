#pragma once
#include <list>
#include "Entity.h"
#include "EntityManager.h"
#include "Box2D/include/box2d/box2d.h"

using namespace std;

// esta clase es equivalente a un nivel del juego
//se espera que herede de gamestate en un futuro
//tambien deberia convertirse en un template de modo de juego y mapa
class PlayState
{
public:
	PlayState();
	virtual void init();
	virtual void update();
	virtual void render();
	virtual void handleInput();
private:
	EntityManager* eManager_;
	b2World* physicsWorld;
	vector<b2Body*> physicalEntities; //almacena los punteros a los colliders de b2
	//puede que no sea necesario si cogemos la referencia en cuanto los creamos con addPhysicalEntity
	b2Body* addPhysicalEntity(/*PARÁMETROS PARA PODER CREAR UN BODY*/);  //añade una entidad fisica

	//HUD

};

