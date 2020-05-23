#pragma once
#include "GameState.h"

class InputHandler;
class Texture;
class EndGameState :
	public GameState
{
private:
	InputHandler* ih;
	Texture* backgroundT_;
	bool anyButtonPush = false;
public:
	virtual void init();
	virtual void render();
	virtual void update();
	virtual void handleInput();
	virtual void onLoaded();
};
