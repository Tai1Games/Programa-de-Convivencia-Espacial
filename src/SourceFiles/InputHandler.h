#pragma once

#include <SDL.h>
#include <array>
#include <vector>
#include "Vector2D.h"
#include <memory>
#include "../json/single_include/nlohmann/json.hpp"
#include <box2d.h>

using json = nlohmann::json;
using namespace std;

class InputHandler {
public:
	const int m_joystickDeadZone = 10000;
	const int m_triggerDeadZone = 10000; //trigger deadzone equals threshold

	InputHandler();
	enum MOUSEBUTTON : Uint8 {
		LEFT = 0, MIDDLE = 1, RIGHT = 2
	};
	enum GAMEPADSTICK : Uint8 {
		LEFTSTICK = 1, RIGHTSTICK=2
	};
	enum GAMEPADTRIGGER : Uint8 {
		LEFTTRIGGER = 1, RIGHTTRIGGER = 2
	};
	enum ButtonState :Uint8 {
		Up = 0, JustUp, Down, JustDown
	};

	InputHandler(InputHandler&) = delete;
	InputHandler& operator=(InputHandler&) = delete;

	virtual ~InputHandler();

	// update the state
	void update();

	// keyboard
	inline bool keyDownEvent();
	inline bool keyUpEvent() {
		return isKeyUpEvent_;
	}
	inline bool isKeyDown(SDL_Scancode key) {
		// return kbState_[key] == 1;
		return keyDownEvent() && kbState_[key] == 1;
	}
	inline bool isKeyDown(SDL_Keycode key) {
		return isKeyDown(SDL_GetScancodeFromKey(key));
	}
	inline bool isKeyUp(SDL_Scancode key) {
		// kbState_[key] == 0;
		return keyUpEvent() && kbState_[key] == 0;
	}
	inline bool isKeyUp(SDL_Keycode key) {
		return isKeyUp(SDL_GetScancodeFromKey(key));
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

	inline int getMouseButtonState(MOUSEBUTTON b) {
		return mbState_[b];
	}

	// Joystick
	//init
	void initialiseJoysticks();
	bool joysticksInitialised() {
		return m_bJoysticksInitialised;
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
	inline bool isButtonJustUp(int ctrl, SDL_GameControllerButton b) {
		return(isButtonUpEvent_ && m_buttonStates[ctrl][b] == JustUp);
	}
	inline bool isButtonJustDown(int ctrl, SDL_GameControllerButton b) {
		return(isButtonDownEvent_ && m_buttonStates[ctrl][b] == JustDown);
	}
	//isup/down for holding a button
	inline bool isButtonDown(int ctrl, SDL_GameControllerButton b) {
		return(m_buttonStates[ctrl][b] == Down);
	}
	inline bool isButtonUp(int ctrl, SDL_GameControllerButton b) {
		return(m_buttonStates[ctrl][b] == Up);
	}
	//get the direction or a value from a stick/trigger given a controller
	b2Vec2 getStickDir(int ctrl, GAMEPADSTICK stick);
	double getStickX(int ctrl, GAMEPADSTICK stick);
	double getStickY(int ctrl, GAMEPADSTICK stick);
	double getTrigger(int ctrl, GAMEPADTRIGGER trigger);


private:
	//
	//Methods
	//
	//controllers
	void clearState();
	void clearJoysticks();

	inline void onJoyAxisChange(SDL_Event& event);
	inline void onJoyButtonChange(SDL_Event& event, ButtonState just);
	inline bool mapJoystick(SDL_GameController* joy, json mapData);

	//keyboard
	inline void onKeyDown(SDL_Event& event) {
		isKeyDownEvent_ = true;
		// kbState_ = SDL_GetKeyboardState(0);
	}
	inline void onKeyUp(SDL_Event& event) {
		isKeyUpEvent_ = true;
		// kbState_ = SDL_GetKeyboardState(0);
	}
	
	//mouse
	inline void onMouseMotion(SDL_Event& event) {
		isMouseMotionEvent_ = true;
		mousePos_.Set(event.motion.x, event.motion.y);
	}
	inline void onMouseButtonChange(SDL_Event& event, bool isDown) {
		isMouseButtonEvent_ = true;
		if (event.button.button == SDL_BUTTON_LEFT) {
			mbState_[LEFT] = isDown;
		}
		else if (event.button.button == SDL_BUTTON_MIDDLE) {
			mbState_[MIDDLE] = isDown;
		}
		else if (event.button.button == SDL_BUTTON_RIGHT) {
			mbState_[RIGHT] = isDown;
		}
	}

	//
	//variables
	//
	//keyboard
	const Uint8* kbState_;
	bool isKeyUpEvent_;
	bool isKeyDownEvent_;
	//mouse
	bool isMouseMotionEvent_;
	bool isMouseButtonEvent_;
	b2Vec2 mousePos_;
	std::array<bool, 3> mbState_;




	std::vector<SDL_GameController*> m_gameControllers;
	std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
	std::vector<std::pair<double*,double*>> m_triggerValues;
	std::vector<std::vector<ButtonState>> m_buttonStates;

	bool m_bJoysticksInitialised;
	bool isButtonDownEvent_;
	bool isButtonUpEvent_;
	bool isAxisMovementEvent_;
};

