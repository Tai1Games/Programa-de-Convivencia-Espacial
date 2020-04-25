#include <utility>
#include "InputHandler.h"
#include "SDL_Game.h"
#include "Collider.h"
#include "box2d.h"

#pragma once
class b2Vec2;
enum ActionKey {Grab=0,Throw,Pick,Attack,Impulse};

//Abstracta pura
class InputBinder
{
protected:
	InputHandler* ih = nullptr;
private:
public:
	InputBinder() { ih = SDL_Game::instance()->getInputHandler(); }
	virtual bool holdGrab() = 0;
	virtual bool pressThrow() = 0;
	virtual bool pressPick() = 0;
	virtual bool releaseGrab() = 0;
	virtual b2Vec2 getAimDir() = 0;
	virtual bool pressImpulse() = 0;
	virtual bool holdImpulse() = 0;
	virtual bool releaseImpulse() = 0;
	virtual bool pressAttack() = 0;
};

//Abstracta pura para modos con teclado 
//para que dejeis
class KeyboardBinder : public InputBinder {
protected:
public:
	KeyboardBinder() : InputBinder() {}
	virtual bool holdGrab() {
		return ih->isKeyDown(SDLK_SPACE);
	}
	virtual bool releaseGrab() {
		return ih->isKeyJustUp(SDLK_SPACE);
	}
	virtual bool pressPick() {
		return ih->keyDownEvent() && ih->isKeyDown(SDLK_e);
	}
	virtual bool pressThrow() {
		return ih->keyDownEvent() && ih->isKeyDown(SDLK_e);
	}
	//como sigamos con la pelea juro que me como a alguien
	virtual b2Vec2 getAimDir() = 0;
};

//de llorar todos
class PureKeyboardBinder : public KeyboardBinder {
	//Team MMur, PJ, posiblemente Satan
public:
	PureKeyboardBinder() : KeyboardBinder() {}
	virtual b2Vec2 getAimDir() {
		b2Vec2 dir = b2Vec2(0, 0);
		if (ih->isKeyDown(SDLK_a))
			dir.x = -1;
		else if (ih->isKeyDown(SDLK_d))
			dir.x = 1;
		if (ih->isKeyDown(SDLK_w))
			dir.y = -1;
		if (ih->isKeyDown(SDLK_s))
			dir.y = 1;
		dir.Normalize();
		return dir;
	}
	virtual bool pressImpulse() {
		return ih->isKeyJustDown(SDLK_c);
	}
	virtual bool holdImpulse() {
		return ih->isKeyDown(SDLK_c);
	}
	virtual bool releaseImpulse() {
		return ih->isKeyJustUp(SDLK_c);
	}
	virtual bool pressAttack() {
		return ih->isKeyJustDown(SDLK_v);
	}
};

//de una puta vez
class MouseKeyboardBinder : public KeyboardBinder {
	//Team Adri, Esteban, Andres, Jorge
	Collider* playerCol_ = nullptr;
public:
	MouseKeyboardBinder(Collider* c) : KeyboardBinder(), playerCol_(c) {}
	virtual b2Vec2 getAimDir() {
		//devolvemos un vector unitario que apunte del jugador al raton
		SDL_Rect playerDrawPos = playerCol_->getRectRender();
		b2Vec2 playerPos = b2Vec2(playerDrawPos.x + playerDrawPos.w / 2, playerDrawPos.y + playerDrawPos.h / 2);
		b2Vec2 dir = ih->getMousePos() - playerPos;
		dir.Normalize();
		return dir;
	}
	virtual bool pressImpulse() {
		return ih->isMouseButtonJustDown(InputHandler::MOUSEBUTTON::RIGHT);
	}
	virtual bool holdImpulse() {
		return ih->isMouseButtonDown(InputHandler::MOUSEBUTTON::RIGHT);
	}
	virtual bool releaseImpulse() {
		return ih->isMouseButtonJustUp(InputHandler::MOUSEBUTTON::RIGHT);
	}
	virtual bool pressAttack() {
		return ih->isMouseButtonJustDown(InputHandler::MOUSEBUTTON::LEFT);
	}
};

//La unica opcion correcta
class ControllerInputBinder : public InputBinder {
protected:
	int id_ = -1;
public:
	ControllerInputBinder(int id):InputBinder(),id_(id) {}
	virtual bool holdGrab() {
		return ih->getTrigger(id_, InputHandler::GAMEPADTRIGGER::RIGHTTRIGGER);
	}
	virtual bool releaseGrab() {
		return !ih->getTrigger(id_, InputHandler::GAMEPADTRIGGER::RIGHTTRIGGER);
	}
	virtual bool pressPick() {
		return ih->isButtonJustDown(id_,SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_Y);
	}
	virtual bool pressThrow() {
		return ih->isButtonJustDown(id_, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_Y);
	}
	virtual bool pressImpulse() {
		return ih->isButtonJustDown(id_, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A);
	}
	virtual bool holdImpulse() {
		return ih->isButtonDown(id_, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A);
	}
	virtual bool releaseImpulse() {
		return ih->isButtonJustUp(id_, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A);
	}
	virtual bool pressAttack() {
		return ih->isButtonJustDown(id_, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_X);
	}
	virtual b2Vec2 getAimDir() {
		return ih->getLastStickDir(id_, InputHandler::GAMEPADSTICK::LEFTSTICK);
	}
};





















//pero seguid con los meme xfa