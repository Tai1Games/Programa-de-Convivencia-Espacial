#include "GameState.h"
#include "Constants.h"
#include "SDL.h"
#include "SDL_Game.h"
#include "InputHandler.h"

GameState::GameState() :
	entityManager_(nullptr){
}

GameState::~GameState() {
	delete entityManager_;
	entityManager_ = nullptr;
}

void GameState::update() {
	entityManager_->update();
	//tambi�n deber�a actualizar la l�gica de modo de juego
	//spawners de monedas, carga de objetivos...
}

void GameState::render() {

	entityManager_->render();

}

void GameState::handleInput() {
	SDL_Game::instance()->getInputHandler()->update();
	DebugInput();
	if(entityManager_!=nullptr)
		entityManager_->handleInput();
}

void GameState::DebugInput() {
	InputHandler* ih = SDL_Game::instance()->getInputHandler();
	for (int i = 0; i < ih->getNumControllers(); i++)
	{
		/*cout << "----------------" << endl;
		cout << "Mando " << i << endl;
		cout << "----------------" << endl;*/

		if (ih->isButtonJustDown(i, SDL_CONTROLLER_BUTTON_A)) {
			cout << "just pressed A" << endl;
		}
		if (ih->isButtonJustDown(i, SDL_CONTROLLER_BUTTON_B)) {
			cout << "just pressed B" << endl;
		}
		if (ih->isButtonJustUp(i, SDL_CONTROLLER_BUTTON_A)) {
			cout << "just released A" << endl;
		}
		if (ih->isButtonJustUp(i, SDL_CONTROLLER_BUTTON_B)) {
			cout << "just released B" << endl;
		}
		if (ih->isButtonDown(0, SDL_CONTROLLER_BUTTON_A)) {
			cout << "AAAAAAAAA" << endl;
		}
		if (ih->isButtonDown(0, SDL_CONTROLLER_BUTTON_B)) {
			cout << "BBBBBBB" << endl;
		}
		b2Vec2 vI = ih->getStickDir(i, InputHandler::GAMEPADSTICK::LEFTSTICK);
		b2Vec2 vD = ih->getStickDir(i, InputHandler::GAMEPADSTICK::RIGHTSTICK);
		if (vI.Length() != 0 || vD.Length() != 0) {
			cout << "STICKS" << "--------" << endl;
			b2Vec2 vI = ih->getStickDir(i, InputHandler::LEFTSTICK);
			b2Vec2 vD = ih->getStickDir(i, InputHandler::RIGHTSTICK);
			cout << "Izq: " << vI.x << " " << vI.y << endl;
			cout << "Der: " << vD.x << " " << vD.y << endl;
			cout << endl;
		}
		double tD = ih->getTrigger(i, InputHandler::GAMEPADTRIGGER::RIGHTTRIGGER);
		double tI = ih->getTrigger(i, InputHandler::GAMEPADTRIGGER::LEFTTRIGGER);
		if (tD != 0 || tI != 0) {
			cout << "TRIGGERS" << endl << "--------" << endl;
			cout << "Izq: " << tI << endl;
			cout << "Der: " << tD << endl;
			cout << endl;
		}
	}
}