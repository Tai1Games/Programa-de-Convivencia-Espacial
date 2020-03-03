#include "InputHandler.h"


InputHandler::InputHandler() {
	clearState();
	kbState_ = SDL_GetKeyboardState(0);
}

InputHandler::~InputHandler() {
}

void InputHandler::update() {
	//cout << "A" << endl;

	SDL_Event event;

	clearState();

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			onKeyDown(event);
			break;
		case SDL_KEYUP:
			onKeyUp(event);
			break;
		case SDL_MOUSEMOTION:
			onMouseMotion(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonChange(event, true);
			break;
		case SDL_MOUSEBUTTONUP:
			onMouseButtonChange(event, false);
			break;
		case SDL_JOYAXISMOTION:
			onJoyAxisChange(event);
			break;
		}

	}

}

void InputHandler::initialiseJoysticks() {
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}
	if (SDL_NumJoysticks() > 0) {
		for (int i = 0; i < SDL_NumJoysticks(); i++) {
			SDL_Joystick* joy = SDL_JoystickOpen(i);
			if (joy)
			{
				m_joysticks.push_back(joy);
				m_joystickValues.push_back(std::make_pair(new
					Vector2D(0, 0), new Vector2D(0, 0))); // add our pair
				m_triggerValues.push_back(std::make_pair
				(new int(0), new int(0)));
			}
			else
			{
				std::cout << SDL_GetError();
			}
			SDL_JoystickEventState(SDL_ENABLE);
			m_bJoysticksInitialised = true;
			std::cout << "Initialised " << m_joysticks.size() << " joystick(s)";
		}
	}
	else
	{
		m_bJoysticksInitialised = false;
	}
}

void InputHandler::clearJoysticks()
{
	if (m_bJoysticksInitialised)
	{
		for (unsigned int i = 0; i < SDL_NumJoysticks();
			i++)
		{
			SDL_JoystickClose(m_joysticks[i]);
		}
	}
}

void InputHandler::clearState() {
	isKeyDownEvent_ = false;
	isKeyUpEvent_ = false;
	isMouseButtonEvent_ = false;
	isMouseMotionEvent_ = false;
	isJoyAxisMovement_ = false;

	for (int i = 0; i < 3; i++) {
		mbState_[i] = false;
	}
}

int InputHandler::getAxisX(int joy, GAMEPADSTICK stick)
{
	if (m_joystickValues.size() > 0)
	{
		if (stick == LEFT)

		{
			return m_joystickValues[joy].first->getX();
		}
		else if (stick == RIGHT)
		{
			return m_joystickValues[joy].second->getX();
		}
	}
	return 0;
}

int InputHandler::getAxisY(int joy, GAMEPADSTICK stick)
{
	if (m_joystickValues.size() > joy)
	{
		if (stick == LEFTSTICK)
		{
			return m_joystickValues[joy].first->getY();
		}
		else if (stick == RIGHTSTICK)
		{
			return m_joystickValues[joy].second->getY();
		}
	}
	return 0;
}

int InputHandler::getTrigger(int joy, GAMEPADTRIGGER trigger) {
	if (m_joystickValues.size() > joy)
	{
		if (trigger == LEFTTRIGGER)
		{
			return *m_triggerValues[joy].first;
		}
		else if (trigger == RIGHTTRIGGER)
		{
			return *m_triggerValues[joy].second;
		}
	}
	return 0;
}

void InputHandler::onJoyAxisChange(SDL_Event& event) {
	isJoyAxisMovement_ = true;
	int whichOne = event.jaxis.which;
	// left stick move left or right
	if (event.jaxis.axis == 0)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setX(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setX(-1);
		}
		else
		{
			m_joystickValues[whichOne].first->setX(0);
		}
	}
	// left stick move up or down
	if (event.jaxis.axis == 1)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setY(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setY(-1);
		}
		else
		{
			m_joystickValues[whichOne].first->setY(0);
		}
	}
	//left trigger move up or down
	if (event.jaxis.axis == 2) {
		if (event.jaxis.value > m_triggerDeadZone)
		{
			*m_triggerValues[whichOne].first=1;
		}
		//else if (event.jaxis.value < -m_joystickDeadZone)
		//{
		//	m_joystickValues[whichOne].first->setY(-1);
		//}
		else
		{
			*m_triggerValues[whichOne].first = 0;
		}
	}
	// right stick move left or right
	if (event.jaxis.axis == 3)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->setX(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->setX(-1);
		}
		else
		{
			m_joystickValues[whichOne].second->setX(0);
		}
	}
	// right stick move up or down
	if (event.jaxis.axis == 4)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->setY(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->setY(-1);
		}
		else
		{
			m_joystickValues[whichOne].second->setY(0);
		}
		
	}
	//right trigger move up or down
	if (event.jaxis.axis == 5) {
		if (event.jaxis.value > m_triggerDeadZone)
		{
			*m_triggerValues[whichOne].second = 1;
		}
		//else if (event.jaxis.value < -m_joystickDeadZone)
		//{
		//	m_joystickValues[whichOne].first->setY(-1);
		//}
		else
		{
			*m_triggerValues[whichOne].second = 0;
		}
	}


	//cout << "Controller 0:" << endl;
	//cout << "Triggers " << getTrigger(0, LEFTTRIGGER) << " " << getTrigger(0, RIGHTTRIGGER) << endl;

	//cout << whichOne << endl;
	//cout<<"Left: " <<
	//m_joystickValues[whichOne].first->getX() << " " << m_joystickValues[whichOne].first->getY() << endl;
	//cout << "Right: " <<
	//	m_joystickValues[whichOne].second->getX() << " " << m_joystickValues[whichOne].second->getY() << endl;
}

