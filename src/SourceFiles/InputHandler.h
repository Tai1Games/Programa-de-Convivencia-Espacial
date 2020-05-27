#pragma once

#include <SDL.h>
#include <array>
#include <vector>
#include "Vector2D.h"
#include <memory>
#include "../json/single_include/nlohmann/json.hpp"
#include <box2d.h>
#include "checkML.h"
#include <iterator>
#include <queue>

using json = nlohmann::json;
using namespace std;

class InputHandler {
public:
	enum MOUSEBUTTON : Uint8 {
		LEFT = 0, MIDDLE = 1, RIGHT = 2
	};
	enum GAMEPADSTICK : Uint8 {
		LEFTSTICK = 1, RIGHTSTICK = 2
	};
	enum GAMEPADTRIGGER : Uint8 {
		LEFTTRIGGER = 1, RIGHTTRIGGER = 2
	};
	enum ButtonState :Uint8 {
		Up = 0, JustUp, Down, JustDown
	};

private:
	//
	//variables
	//
	//keyboard
	bool isKeyUpEvent_;
	bool isKeyDownEvent_;

	//---------------------------------------------
	//mouse
	bool isMouseMotionEvent_;
	bool isMouseButtonEvent_;
	b2Vec2 mousePos_;
	std::array<ButtonState, 3> mbState_;
	//---------------------------------------------
	//mandos
	int numControllers_;
	std::vector<SDL_GameController*> m_gameControllers; //punteros a los controllers de sdl
	std::queue<int> disconnectedGameControllers_;//cola de los mandos desconectados
		//almacenamiento del estado de los mandos
	std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
	std::vector<std::pair<double*, double*>> m_triggerValues;
	std::vector<std::vector<ButtonState>> m_buttonStates;
	std::vector<b2Vec2> lastLStickValue_;

	//teclado y raton
	//almacenamiento del estado de teclado y raton
	ButtonState m_mouseButtonStates[3];
	std::vector<SDL_Scancode> m_keysJustDown; //vector de teclas recien pulsadas
	std::vector<SDL_Scancode> m_keysJustUp; //vector de teclas recien soltadas
	const int kbSize = 300;
	std::vector<ButtonState> kbState_;
	std::queue<int> justUpKeys;
	std::queue<int> justDownKeys;

	//estructuras auxiliares para la reconexion y desconexion de mandos
	int gameToSystemCtrlId[4] = { -1,-1,-1,-1 }; //guarda las ids con las que sdl reconoce cada mando del que se pide input
	std::map<int, int> systemToGameCtrlId; //guarda los ids que el juego asocia a cada input fisico

	bool debugFlag_ReconectedController = false;

	bool m_bJoysticksInitialised;
	bool isButtonDownEvent_;
	bool isButtonUpEvent_;
	bool isAxisMovementEvent_;

	//
	//Methods
	//
	//controllers
	void clearState();
	void clearJoysticks();

	inline void onJoyAxisChange(SDL_Event& event);
	inline void onJoyButtonChange(SDL_Event& event, ButtonState just);
	inline bool mapJoystick(SDL_GameController* joy, json mapData);
	inline void onControllerAddedEvent(const SDL_Event& event);
	inline void onControllerRemovedEvent(const SDL_Event& event);
	inline void initialiseNewController(int i);
	//---------------------------------------------
	//keyboard
	inline void onKeyDown(SDL_Event& event) {
		isKeyDownEvent_ = true;
		if (kbState_[event.key.keysym.scancode] == ButtonState::Up) {
			kbState_[event.key.keysym.scancode] = ButtonState::JustDown;
			justDownKeys.push(event.key.keysym.scancode);
		}
	}
	inline void onKeyUp(SDL_Event& event) {
		isKeyUpEvent_ = true;
		if (kbState_[event.key.keysym.scancode] == ButtonState::Down) {
			kbState_[event.key.keysym.scancode] = ButtonState::JustUp;
			justUpKeys.push(event.key.keysym.scancode);
		}
	}
	//---------------------------------------------
	//mouse
	inline void onMouseMotion(SDL_Event& event) {
		isMouseMotionEvent_ = true;
		mousePos_.Set(event.motion.x, event.motion.y);
	}
	inline void onMouseButtonChange(SDL_Event& event, bool isDown) {
		isMouseButtonEvent_ = true;
		if (event.button.button == SDL_BUTTON_LEFT) {
			mbState_[LEFT] = (isDown) ? JustDown : JustUp;
		}
		else if (event.button.button == SDL_BUTTON_MIDDLE) {
			mbState_[MIDDLE] = (isDown) ? JustDown : JustUp;
		}
		else if (event.button.button == SDL_BUTTON_RIGHT) {
			mbState_[RIGHT] = (isDown) ? JustDown : JustUp;
		}
	}
	//---------------------------------------------

public:
	const int m_joystickDeadZone = 10000;
	const int m_triggerDeadZone = 10000; //trigger deadzone equals threshold

	InputHandler();

	InputHandler(InputHandler&) = delete;
	InputHandler& operator=(InputHandler&) = delete;

	virtual ~InputHandler();

	// update the state
	void update();

	// keyboard
	inline bool keyDownEvent() {
		return isKeyDownEvent_;
	}
	inline bool keyUpEvent() {
		return isKeyUpEvent_;
	}
	inline bool isKeyDown(SDL_Scancode key) {
		// return kbState_[key] == 1;
		return kbState_[key] == ButtonState::Down;
	}
	inline bool isKeyDown(SDL_Keycode key) {
		return isKeyDown(SDL_GetScancodeFromKey(key));
	}
	inline bool isKeyUp(SDL_Scancode key) {
		// kbState_[key] == 0;
		return kbState_[key] == ButtonState::Up;
	}
	inline bool isKeyUp(SDL_Keycode key) {
		return isKeyUp(SDL_GetScancodeFromKey(key));
	}
	inline bool isKeyJustDown(SDL_Keycode key) {
		return kbState_[SDL_GetScancodeFromKey(key)] == ButtonState::JustDown;
	}
	inline bool isKeyJustUp(SDL_Keycode key) {
		return kbState_[SDL_GetScancodeFromKey(key)] == ButtonState::JustUp;
	}
	// mouse
	inline bool mouseMotionEvent() {
		return isMouseMotionEvent_;
	}

	inline bool mouseButtonEvent() {
		return isMouseButtonEvent_;
	}

	b2Vec2 getMousePos() {
		return mousePos_;
	}

	inline bool isMouseButtonUp(MOUSEBUTTON mb) {
		return mbState_[mb] == Up || mbState_[mb] == JustUp;
	}
	inline bool isMouseButtonDown(MOUSEBUTTON mb) {
		return mbState_[mb] == Down || mbState_[mb] == JustDown;
	}
	inline bool isMouseButtonJustDown(MOUSEBUTTON mb) {
		return mbState_[mb] == JustDown;
	}
	inline bool isMouseButtonJustUp(MOUSEBUTTON mb) {
		return mbState_[mb] == JustUp;
	}


	// Joystick
	//init
	void initialiseGamepads();
	bool joysticksInitialised() {
		return m_bJoysticksInitialised;
	}
	int getNumControllers() {
		return numControllers_;
	}

	//Ask for this variables when asking for input
	//type of events
	inline bool isButonDownEvent() {
		return isButtonDownEvent_;
	}
	inline bool isButtonUpEvent() {
		return isButtonUpEvent_;
	}
	inline bool isAxisMovementEvent() {
		return isAxisMovementEvent_;
	}
	//justup/down for the exact press or release
	bool isButtonJustUp(int gameCtrl, SDL_GameControllerButton b);
	bool isButtonJustDown(int gameCtrl, SDL_GameControllerButton b);
	//isup/down for holding a button
	bool isButtonDown(int gameCtrl, SDL_GameControllerButton b);
	bool isButtonUp(int gameCtrl, SDL_GameControllerButton b);


	//get the direction or a value from a stick/trigger given a controller
	b2Vec2 getStickDir(int ctrl, GAMEPADSTICK stick);
	b2Vec2 getLastStickDir(int ctrl, GAMEPADSTICK stick);
	double getStickX(int ctrl, GAMEPADSTICK stick);
	double getStickY(int ctrl, GAMEPADSTICK stick);
	double getTrigger(int ctrl, GAMEPADTRIGGER trigger);
};
