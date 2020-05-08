#pragma once
#include "GameMode.h"
#include "Resources.h"

class Countdown : public Component
{
private:
	int currentFrame_ = 0;
	int maxFrames_ = 180;
	int posX = CONST(int, "WINDOW_WIDTH") / 2;
	int posY = CONST(int, "WINDOW_HEIGHT") / 2;
	Texture* number = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::Three);
	GameMode* gMode_;
public:
	Countdown(GameMode* g): Component(ComponentType::Countdown), gMode_(g) {}
	~Countdown() {}
	virtual void update();
	virtual void draw();
};

