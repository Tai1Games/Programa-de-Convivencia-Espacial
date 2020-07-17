#pragma once

#include "GameState.h"
#include "checkML.h"
#include "Texture.h"
#include "InputHandler.h"

class IntroState : public GameState {
private:
protected:
	InputHandler* ih_ = nullptr;
public:
	IntroState() {};
	~IntroState() {};
	void init() override;
	void handleInput() override;
	void update() override {};
	void render() override {};
};
