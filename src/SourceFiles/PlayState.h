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

};

