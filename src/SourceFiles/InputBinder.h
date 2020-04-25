#include <utility>
#include "InputHandler.h"
#include "SDL_Game.h"
#include "Collider.h"
#include "box2d.h"

#pragma once
class b2Vec2;
enum ActionKey {Grab=0,Throw,Pick,Attack,Impulse};
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

class KBMInputBinder : public InputBinder {
protected:
	Collider* playerCol_ = nullptr;
public:
	KBMInputBinder(Collider* c) : InputBinder(), playerCol_(c) {}
	virtual bool holdGrab() {
		return ih->isKeyDown(SDLK_SPACE);
	}
	virtual bool releaseGrab() {
		return ih->keyUpEvent() && ih->isKeyUp(SDLK_SPACE);
	}
	virtual bool pressPick() {
		return ih->keyDownEvent() && ih->isKeyDown(SDLK_e);
	}
	virtual bool pressThrow() {
		return ih->keyDownEvent() && ih->isKeyDown(SDLK_e);
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
	virtual b2Vec2 getAimDir() {
		//devolvemos un vector unitario que apunte del jugador al raton
		SDL_Rect playerDrawPos = playerCol_->getRectRender();
		b2Vec2 playerPos = b2Vec2(playerDrawPos.x + playerDrawPos.w / 2, playerDrawPos.y + playerDrawPos.h / 2);
		b2Vec2 dir = ih->getMousePos() - playerPos;
		dir.Normalize();
		return dir;
	}
};

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

