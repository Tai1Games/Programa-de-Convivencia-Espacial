#pragma once
#include "GameMode.h"
#include "Resources.h"
#include "Texture.h"

class Countdown : public Component
{
private:
	int currentFrame_ = 0;
	int maxFrames_ = CONST(int, "MAX_COUNTDOWN_FRAMES");

	int minSize_ = CONST(int, "MIN_COUNTDOWN_SIZE");
	int maxSize_ = CONST(int, "MAX_COUNTDOWN_SIZE");
	int currentSize_ = 0;
	int sizeChangeRate_ = (maxSize_ - minSize_) / (maxFrames_ / 4); //ratio de crecimiento teniendo en cuenta que hay 4 texturas

	int posX_ = CONST(int, "WINDOW_WIDTH") / 2;
	int posY_ = CONST(int, "WINDOW_HEIGHT") / 2;
	
	Texture* textures_[4] = { //3 2 1 go
	SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::Three),
	SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::Two),
	SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::One),
	SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::Go) };
	GameMode* gMode_;
public:
	Countdown(GameMode* g) : Component(ComponentType::Countdown), gMode_(g) {}
	~Countdown() {}
	virtual void update();
	virtual void draw() const;
};

