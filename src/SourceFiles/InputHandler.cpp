#include "InputHandler.h"
#include <fstream>
#include <box2d.h>
#include <iostream>


using namespace std;
InputHandler::InputHandler() {
	clearState();
	kbState_ = SDL_GetKeyboardState(0);
	numControllers_ = 0;
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
		case SDL_JOYBUTTONDOWN:
			onJoyButtonChange(event, JustDown);
			break;
		case SDL_JOYBUTTONUP:
			onJoyButtonChange(event, JustUp);
			break;
		}

	}

}

void InputHandler::initialiseJoysticks() {
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}
	numControllers_ = SDL_NumJoysticks();
	if (SDL_NumJoysticks() > 0) {

		json mapData;
		ifstream inData = ifstream("../config/inputMapping.json");
		if (inData.is_open()) {
			inData >> mapData;
			//cout << "loaded Mapping files" << endl;
		}
		for (int i = 0; i < SDL_NumJoysticks(); i++) {
			SDL_GameController* gameCtrl = SDL_GameControllerOpen(i);
			if (gameCtrl)
			{
				cout << "--------------" << endl;
				cout << SDL_GameControllerName(gameCtrl) << endl;
				if (mapJoystick(gameCtrl, mapData)) {
					cout << "Controller " << i <<" mapped accordingly" << endl;
				}
				m_gameControllers.push_back(gameCtrl);
				m_joystickValues.push_back(std::make_pair(new
					Vector2D(0, 0), new Vector2D(0, 0))); // add our pair
				m_triggerValues.push_back(std::make_pair
				(new double(0.0), new double(0.0)));

				lastLStickValue_.push_back(Vector2D(0, 0));

				std::vector<ButtonState> tempButtons;
				for (int j = 0; j < SDL_CONTROLLER_BUTTON_MAX; j++)
				{
					tempButtons.push_back(Up);
				}
				m_buttonStates.push_back(tempButtons);
			}
			else
			{
				std::cout << SDL_GetError();
			}
			SDL_JoystickEventState(SDL_ENABLE);
			m_bJoysticksInitialised = true;
			std::cout << "Initialised " << m_gameControllers.size() << " joystick(s)";
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
			SDL_GameControllerClose(m_gameControllers[i]);
		}
	}
}

void InputHandler::clearState() {
	isKeyDownEvent_ = false;
	isKeyUpEvent_ = false;
	isMouseButtonEvent_ = false;
	isMouseMotionEvent_ = false;
	isAxisMovementEvent_ = false;
	isButtonDownEvent_ = false;
	isButtonUpEvent_ = false;

	for (int i = 0; i < 3; i++) {
		mbState_[i] = false;
	}

	for (int controller = 0; controller < m_gameControllers.size();controller++) {
		for (int j = 0; j < SDL_CONTROLLER_BUTTON_MAX; j++) {
			switch (m_buttonStates[controller][j])
			{
			case(JustDown):
				m_buttonStates[controller][j] = Down;
				break;
			case(JustUp):
				m_buttonStates[controller][j] = Up;
				break;
			default:
				break;
			}
		}
	}
}

double InputHandler::getStickX(int joy, GAMEPADSTICK stick)
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

double InputHandler::getStickY(int joy, GAMEPADSTICK stick)
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

double InputHandler::getTrigger(int joy, GAMEPADTRIGGER trigger) {
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
	isAxisMovementEvent_ = true;
	int whichOne = event.jaxis.which;
	//cout << event.jaxis.value<<endl;
	const double normalize= 1.0/32768.0;
	double val = event.jaxis.value;
	// left stick move left or right
	if (event.jaxis.axis == 0)
	{
		if (val > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setX(val*normalize);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setX(val * normalize);
		}
		else
		{
			m_joystickValues[whichOne].first->setX(0);
		}
		lastLStickValue_[whichOne].setX(m_joystickValues[whichOne].first->getX());
	}
	// left stick move up or down
	if (event.jaxis.axis == 1)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setY(val * normalize);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setY(val * normalize);
		}
		else
		{
			m_joystickValues[whichOne].first->setY(0);
		}
		lastLStickValue_[whichOne].setY(m_joystickValues[whichOne].first->getY());
	}
	//left trigger move up or down
	if (event.jaxis.axis == 2) {
		if (event.jaxis.value > m_triggerDeadZone)
		{
			*m_triggerValues[whichOne].first=abs(event.jaxis.value);
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
			m_joystickValues[whichOne].second->setX(val * normalize);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->setX(val * normalize);
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
			m_joystickValues[whichOne].second->setY(val * normalize);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->setY(val * normalize);
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
			*m_triggerValues[whichOne].second = abs(event.jaxis.value);
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


	//if (m_joystickValues[whichOne].first->magnitude() != 0 || m_joystickValues[whichOne].second->magnitude()!=0)
	//{
	//	cout << whichOne << endl;
	//	cout << "Left: " <<
	//		m_joystickValues[whichOne].first->getX() << " " << m_joystickValues[whichOne].first->getY() << endl;
	//	cout << "Right: " <<
	//		m_joystickValues[whichOne].second->getX() << " " << m_joystickValues[whichOne].second->getY() << endl;
	//}
}

void InputHandler::onJoyButtonChange(SDL_Event& event,ButtonState just) {
	if (just == JustDown)
		isButtonDownEvent_ = true;
	else
		isButtonUpEvent_ = true;
	
	int whichOne = event.jaxis.which;
	//if (event.cbutton.button != event.jbutton.button)
	//	cout << "Puto sdl" << endl;
	//if(SDL_GameControllerGetButton(m_gameControllers[whichOne],SDL_CONTROLLER_BUTTON_B)) {
	//	cout << "BBBBBBBBB" << endl;
	//}

	//m_buttonStates[whichOne][event.jbutton.button] = just;
	//m_buttonStates[whichOne]
	//	[SDL_GameControllerGetBindForButton
	//	(m_gameControllers[whichOne],(SDL_GameControllerButton)event.jbutton.button).value] = just;
	m_buttonStates[whichOne][(int)SDL_GameControllerGetBindForButton
	(m_gameControllers[whichOne], (SDL_GameControllerButton)event.cbutton.button).value.button] = just;


	/*if (just = JustDown)
		cout << SDL_GameControllerGetBindForButton
		(m_gameControllers[whichOne], (SDL_GameControllerButton)event.cbutton.button).value.button << endl;*/
}

bool InputHandler::mapJoystick(SDL_GameController* ctrl,json mapData) {
	const int bytes = 33;
	const int bits = bytes * 8;
	char guid[bits] = {};
	SDL_Joystick* joy = SDL_GameControllerGetJoystick(ctrl);
	SDL_JoystickGetGUIDString(SDL_JoystickGetGUID(joy), guid, bits);

	cout << "looking for " << guid << " mapString" << endl;
	if (!(mapData[guid]).is_null()) {
		cout << "found " << guid << " mapString" << endl;
		string mapString = mapData[guid];
		cout << SDL_GameControllerMappingForGUID(SDL_JoystickGetGUID(joy)) << endl;
		int res = SDL_GameControllerAddMapping(mapString.c_str());
		cout << "-----------------------------" << endl;
		cout << SDL_GameControllerMappingForGUID(SDL_JoystickGetGUID(joy)) << endl;

		return res== 1;
		
	}
	else {
		return false;
	}
	return false;
}

b2Vec2 InputHandler::getStickDir(int ctrl, GAMEPADSTICK stick) {
	Vector2D aux;
	if (stick == LEFTSTICK)
		aux = *m_joystickValues[ctrl].first;
	else
		aux = *m_joystickValues[ctrl].second;

	aux = aux.normalize(); //vaya, menos mal que tenemos una clase Vector2D 
	//porque si de b2Vec dependiera...
	return b2Vec2(aux.getX(), aux.getY());
}

b2Vec2 InputHandler::getLastStickDir(int ctrl, GAMEPADSTICK stick) {
	Vector2D aux;
	if (stick == LEFTSTICK)
		aux = lastLStickValue_[ctrl];
	else
		return b2Vec2(0, 0);

	aux = aux.normalize();
	return b2Vec2(aux.getX(), aux.getY());
}