#include "InputHandler.h"
#include <fstream>
#include <box2d.h>
#include <iostream>
#include "SDL_Game.h"

using namespace std;
InputHandler::InputHandler() {
	clearState();
	//kbState_ = SDL_GetKeyboardState(0);
	numControllers_ = 0;
	for (int i = 0; i < 1000; i++) {
			kbState_[i] = ButtonState::Up;
	}
}

InputHandler::~InputHandler() {
	for (std::pair<Vector2D*, Vector2D*> e : m_joystickValues) {
		delete e.first;
		delete e.second;
	}
	for (std::pair<double*, double*> e : m_triggerValues) {
		delete e.first;
		delete e.second;
	}
}

void InputHandler::update() {
	//cout << "A" << endl;

	SDL_Event event;

	clearState();

	cout << (int)kbState_[6] << endl;
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
		case SDL_QUIT:
			SDL_Game::instance()->exitGame();
			break;
		}
	}

	//if (SDL_GameControllerGetButton(controllers_[0], SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A) == 1) {
	//	cout << "Voy a prenderme fuego ahora mismo" << endl;
	//}

}

void InputHandler::initialiseGamepads() {
	if (-1 == SDL_GameControllerAddMappingsFromFile("./config/gamecontrollerdb.txt"))
		cout << "Error al cargar la base de datos" << endl;
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}
	numControllers_ = SDL_NumJoysticks();
	if (SDL_NumJoysticks() > 0) {

		//json mapData;
		//ifstream inData = ifstream("../config/inputMapping.json");
		//if (inData.is_open()) {
		//	inData >> mapData;
		//	//cout << "loaded Mapping files" << endl;
		//}
		for (int i = 0; i < SDL_NumJoysticks(); i++) {
			SDL_GameController* gameCtrl = SDL_GameControllerOpen(i);
			if (gameCtrl)
			{
				cout << "--------------" << endl;
				cout << SDL_GameControllerName(gameCtrl) << endl;
				//if (mapJoystick(gameCtrl, mapData)) {
				//	cout << "Controller " << i <<" mapped accordingly" << endl;
				//}
				cout << SDL_GameControllerMapping(gameCtrl)<<endl;
				m_gameControllers.push_back(gameCtrl);
				m_joystickValues.push_back(std::make_pair(new
					Vector2D(0, 0), new Vector2D(0, 0))); // add our pair
				m_triggerValues.push_back(std::make_pair
				(new double(0.0), new double(0.0)));

				lastLStickValue_.push_back(b2Vec2(0, 0));

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
		switch (mbState_[i])
		{
		case JustUp:
			mbState_[i] = Up;
			break;
		case JustDown:
			mbState_[i] = Down;
			break;
		default:
			break;
		}
	}
	for (int i = 0; i < 1000; i++) {
		if (kbState_[i] == ButtonState::JustUp)
			kbState_[i] = ButtonState::Up;
		else if (kbState_[i] == ButtonState::JustDown)
			kbState_[i] = ButtonState::Down;
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
		if (stick == LEFTSTICK)

		{
			return m_joystickValues[joy].first->getX();
		}
		else if (stick == RIGHTSTICK)
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

	Uint8 i = 0;
	bool bindFound = false;
	int bindedAxis;
	//hay que buscar el botón al que se corresponde
	//porque SDL es una librería maravillosa y super intuitiva
	while (!bindFound && i < SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_MAX) {
		SDL_GameControllerButtonBind b = SDL_GameControllerGetBindForAxis(m_gameControllers[whichOne], (SDL_GameControllerAxis)i);
		if (b.value.axis == event.jaxis.axis) {
			bindedAxis = i;
			bindFound = true;
		}
		i++;
	}
	//left stick right or left
	if (bindedAxis == 0)
	{
		if (val > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setX(val*normalize);
			lastLStickValue_[whichOne].x = (float)m_joystickValues[whichOne].first->getX();
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setX(val * normalize);
			lastLStickValue_[whichOne].x = (float)m_joystickValues[whichOne].first->getX();
		}
		else
		{
			m_joystickValues[whichOne].first->setX(0);
		}
		
	}
	// left stick move up or down
	if (bindedAxis == 1)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setY(val * normalize);
			lastLStickValue_[whichOne].y = (float)m_joystickValues[whichOne].first->getY();
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setY(val * normalize);
			lastLStickValue_[whichOne].y = (float)m_joystickValues[whichOne].first->getY();

		}
		else
		{
			m_joystickValues[whichOne].first->setY(0);
		}
		
	}
	//left trigger move up or down
	if (bindedAxis == 4) {
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
	if (bindedAxis == 2)
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
	if (bindedAxis == 3)
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
	if (bindedAxis == 5) {
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

	float lastLx = m_joystickValues[whichOne].first->getX(), lastLy = m_joystickValues[whichOne].first->getY();

	if ((lastLx == 0 && lastLy >= 0.99) || (lastLx == 0 && lastLy <= -0.99) ||
		(lastLx >= 0.99 && lastLy == 0) || (lastLx <= -0.99 && lastLy == 0)) {
		lastLStickValue_[whichOne].x = lastLx;
		lastLStickValue_[whichOne].y = lastLy;
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

	Uint8 i = 0;
	bool bindFound=false;
	int bindedButton;
	//hay que buscar el botón al que se corresponde
	//porque SDL es una librería maravillosa y super intuitiva
	while (!bindFound &&i < SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_MAX){
		SDL_GameControllerButtonBind b = SDL_GameControllerGetBindForButton(m_gameControllers[whichOne], (SDL_GameControllerButton)i);
		if (b.value.button == event.cbutton.button) {
			bindedButton = i;
			bindFound = true;
		}
		i++;
	}
	m_buttonStates[whichOne][bindedButton] = just;
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
	if (stick == LEFTSTICK)
		return lastLStickValue_[ctrl];
	else
		return b2Vec2(0, 0);

	//return b2Vec2(aux.getX(), aux.getY());
}
