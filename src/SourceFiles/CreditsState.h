#pragma once
#include <list>
#include "GameMode.h"
#include "Entity.h"
#include "checkML.h"
#include "Resources.h"

using namespace std;

// esta clase es equivalente a un nivel del juego
//se espera que herede de gamestate en un futuro
//tambien deberia convertirse en un template de modo de juego y mapa
class CreditsState : public GameState
{
private:
	double secondsPerFrame_ = 0;
	Texture* fondo_ = nullptr;
	Entity* continueText = nullptr;

	InputBinder* playerControl;
public:
	CreditsState() {};
	virtual ~CreditsState();

	virtual void init() override;
	virtual void update() override;
	virtual void render() override;
	virtual void handleInput() override;
	virtual void onLoaded();
};

