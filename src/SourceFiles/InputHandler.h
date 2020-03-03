#pragma once

#include <SDL.h>
#include <array>
#include <vector>
#include "Vector2D.h"
#include <memory>

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

	inline const Vector2D& getMousePos() {
		return mousePos_;
	}

	inline int getMouseButtonState(MOUSEBUTTON b) {
		return mbState_[b];
	}

	// Joystick
	void initialiseJoysticks();
	bool joysticksInitialised() {
		return m_bJoysticksInitialised;
	}
	// see:
	//   Chapter 4 of 'SDL Game Development' book
	//   Available online via https://biblioteca.ucm.es/
	//

private:
	void clearState();
	void clearJoysticks();

	inline void onKeyDown(SDL_Event& event) {
		isKeyDownEvent_ = true;
		// kbState_ = SDL_GetKeyboardState(0);
	}
	inline void onKeyUp(SDL_Event& event) {
		isKeyUpEvent_ = true;
		// kbState_ = SDL_GetKeyboardState(0);
	}
	inline void onMouseMotion(SDL_Event& event) {
		isMouseMotionEvent_ = true;
		mousePos_.set(event.motion.x, event.motion.y);
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

	inline void onJoyAxisChange(SDL_Event& event);
	const Uint8* kbState_;
	bool isKeyUpEvent_;
	bool isKeyDownEvent_;
	bool isMouseMotionEvent_;
	bool isMouseButtonEvent_;

	Vector2D mousePos_;
	std::array<bool, 3> mbState_;

	int getAxisX(int joy, GAMEPADSTICK stick);
	int getAxisY(int joy, GAMEPADSTICK stick);
	int getTrigger(int joy, GAMEPADTRIGGER trigger);

	//Pruebas de Gamepad para proyecto
	std::vector<SDL_Joystick*> m_joysticks;
	std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
	std::vector<std::pair<int*,int*>> m_triggerValues;
	bool m_bJoysticksInitialised;
	bool isButtonDownEvent_;
	bool isButtonUpEvent_;
	bool isJoyAxisMovement_;
};

