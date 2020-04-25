#include <utility>
#include "InputHandler.h"

#pragma once
class b2Vec2;
enum ActionKey {Grab=0,Throw,Pick,Attack,Impulse};
class InputBinder
{
protected:
	int id_ = -1;
	InputHandler* ih = nullptr;
private:
public:
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
public:
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
		return ih->mouseButtonEvent() && ih->getMouseButtonState(InputHandler::MOUSEBUTTON::RIGHT);
	}
	virtual bool holdImpulse() {
		return ih->getMouseButtonState(InputHandler::MOUSEBUTTON::RIGHT);
	}
	virtual bool releaseImpulse() {
		return ih->mouseButtonEvent() && !ih->getMouseButtonState(InputHandler::MOUSEBUTTON::RIGHT);
	}
	virtual bool pressAttack() {
		return ih->mouseButtonEvent() && ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT);
	}
};

class ControllernputBinder : public InputBinder {
public:
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
};

