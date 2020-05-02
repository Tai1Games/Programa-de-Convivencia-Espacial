#include <utility>
#include "InputHandler.h"
#include "SDL_Game.h"
#include "Collider.h"
#include "box2d.h"

#pragma once
class b2Vec2;
enum ActionKey {Grab=0,Throw,Pick,Attack,Impulse};
struct KeyCursor {
	SDL_Keycode Up = SDLK_w;
	SDL_Keycode Left = SDLK_a;
	SDL_Keycode Down = SDLK_s;
	SDL_Keycode Right = SDLK_d;
	KeyCursor() {}
	KeyCursor(int player) {
		switch (player)
		{
		case 1: {
			Up = SDLK_w;
			Left = SDLK_a;
			Down = SDLK_s;
			Right = SDLK_d;
		}
		break;
		case 2: {
			Up = SDLK_i;
			Left = SDLK_j;
			Down = SDLK_k;
			Right = SDLK_l;
		}
		break;
		default:
			break;
		}
	}
	KeyCursor(SDL_Keycode u, SDL_Keycode l, SDL_Keycode d, SDL_Keycode r) {
		Up = u; Left = l, Down = d; Right = r;
	}
};
struct KeyboardMapping {
	KeyCursor cursor; //Teclas de movimiento para PureKeyboardBinder
	//Varias teclas
	SDL_Keycode grab,
		pickWeapon,
		pickWeapon_secondary,
		throwWeapon,
		throwWeapon_secondary,
		attack, 
		attack_secondary,
		impulse,
		impulse_secondary,
		pause;

	KeyboardMapping(int player = 1) {
		switch (player)
		{
		case 1: {
			cursor = KeyCursor(1);
				grab = SDLK_z,
				pickWeapon = SDLK_q,
				pickWeapon_secondary = SDLK_r,
				throwWeapon = SDLK_q,
				throwWeapon_secondary = SDLK_r,
				attack = SDLK_TAB,
				attack_secondary = SDLK_e,
				impulse = SDLK_LSHIFT,
				impulse_secondary = SDLK_f,
				pause = SDLK_ESCAPE;
		}
		break;
		case 2: {
			cursor = KeyCursor(2);
			grab = SDLK_RALT,
			pickWeapon = SDLK_o,
			throwWeapon = SDLK_o,
			attack = SDLK_u,
			impulse = SDLK_PERIOD,
			pause = SDLK_7;
		}
		break;
		default:
			break;
		}
	}
};

//Abstracta pura
class InputBinder
{
protected:
	InputHandler* ih = nullptr;
	b2Vec2 lastDir = b2Vec2(0, 0);
private:
public:
	InputBinder() { ih = SDL_Game::instance()->getInputHandler(); }
	virtual ~InputBinder() {}
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
	KeyboardMapping map_;
public:
	KeyboardBinder(KeyboardMapping m) : InputBinder(), map_(m) {}
	KeyboardBinder(int defaultMap) : InputBinder(), map_(defaultMap) {}
	bool grabbed = false;
	virtual bool holdGrab() {
		return (!grabbed && ih->isKeyDown(map_.grab));
	}
	virtual bool releaseGrab() {
		return(!grabbed && ih->isKeyJustDown(map_.grab));
	}
	virtual bool pressPick() {
		return (ih->isKeyJustDown(map_.pickWeapon) || ih->isKeyJustDown(map_.pickWeapon_secondary));
	}
	virtual bool pressThrow() {
		return (ih->isKeyJustDown(map_.throwWeapon) || ih->isKeyJustDown(map_.throwWeapon_secondary));
	}
	//como sigamos con la pelea juro que me como a alguien
	virtual b2Vec2 getAimDir() = 0;
};

//de llorar todos
class PureKeyboardBinder : public KeyboardBinder {
	//Team MMur, PJ, posiblemente Satan
public:
	PureKeyboardBinder(KeyboardMapping m) : KeyboardBinder(m) {}
	PureKeyboardBinder(int defaultMap) : KeyboardBinder(defaultMap) {}
	virtual b2Vec2 getAimDir() {
		b2Vec2 dir = b2Vec2(0, 0);
		if (ih->isKeyDown(map_.cursor.Left))
			dir.x = -1;
		else if (ih->isKeyDown(map_.cursor.Right))
			dir.x = 1;
		if (ih->isKeyDown(map_.cursor.Up))
			dir.y = -1;
		if (ih->isKeyDown(map_.cursor.Down))
			dir.y = 1;
		dir.Normalize();
		if (dir.y != 0 || dir.x != 0)
			lastDir = dir;
		return lastDir;
	}
	virtual bool pressImpulse() {
		return (ih->isKeyJustDown(map_.impulse) || ih->isKeyJustDown(map_.impulse_secondary));
	}
	virtual bool holdImpulse() {
		return (ih->isKeyDown(map_.impulse) || ih->isKeyDown(map_.impulse_secondary));
	}
	virtual bool releaseImpulse() {
		return (ih->isKeyJustUp(map_.impulse) || ih->isKeyJustUp(map_.impulse_secondary));
	}
	virtual bool pressAttack() {
		return (ih->isKeyJustDown(map_.attack) || ih->isKeyJustDown(map_.attack_secondary));
	}
};

//de una puta vez
class MouseKeyboardBinder : public KeyboardBinder {
	//Team Adri, Esteban, Andres, Jorge
	Collider* playerCol_ = nullptr;
public:
	MouseKeyboardBinder(Collider* c, KeyboardMapping m) : KeyboardBinder(m), playerCol_(c) {}
	MouseKeyboardBinder(Collider* c, int defaultMap) : KeyboardBinder(defaultMap), playerCol_(c) {}
	virtual b2Vec2 getAimDir() {
		//devolvemos un vector unitario que apunte del jugador al raton
		SDL_Rect playerDrawPos = playerCol_->getRectRender();
		b2Vec2 playerPos = b2Vec2(playerDrawPos.x + playerDrawPos.w / 2, playerDrawPos.y + playerDrawPos.h / 2);
		b2Vec2 dir = ih->getMousePos() - playerPos;
		dir.Normalize();
		if (dir.y != 0 || dir.x != 0)
			lastDir = dir;
		return lastDir;
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
class ControllerBinder : public InputBinder {
protected:
	int id_ = -1;
public:
	ControllerBinder(int id) : InputBinder(),id_(id) {}
	virtual ~ControllerBinder() { ih->returnGamePad(id_); }
	virtual bool holdGrab() {
		return ih->getTrigger(id_, InputHandler::GAMEPADTRIGGER::LEFTTRIGGER);
	}
	virtual bool releaseGrab() {
		return !ih->getTrigger(id_, InputHandler::GAMEPADTRIGGER::LEFTTRIGGER);
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