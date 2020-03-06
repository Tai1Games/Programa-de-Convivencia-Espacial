#pragma once
#include <list>
#include "GameState.h"
#include "Entity.h"
#include "checkML.h"


using namespace std;

// esta clase es equivalente a un nivel del juego
//se espera que herede de gamestate en un futuro
//tambien deberia convertirse en un template de modo de juego y mapa
class PlayState : public GameState
{
private:
public:
	PlayState();
	~PlayState();
	virtual void init();
	virtual void update();
	virtual void render();
	virtual void handleInput();
private:
	EntityManager* entityManager_;
	b2World* physicsWorld_;
	vector<b2Body*> physicalEntities_; //almacena los punteros a los colliders de b2
	//puede que no sea necesario si cogemos la referencia en cuanto los creamos con addPhysicalEntity
	b2Body* addPhysicalEntity(/*PAR�METROS PARA PODER CREAR UN BODY*/);  //a�ade una entidad fisica
	//HUD
	void DebugInput();
};
