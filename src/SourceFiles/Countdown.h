#pragma once
#include "GameMode.h"
#include "Resources.h"
#include "Texture.h"
#include "FireBallGenerator.h"
#include "Viewer.h"

class Countdown : public Component
{
private:
	int currentFrame_ = 0;
	int maxFrames_ = CONST(int, "MAX_COUNTDOWN_FRAMES");
	int framesPerNum_ = maxFrames_ / 4;

	int numAct_ = 0;

	int minSize_ = CONST(int, "MIN_COUNTDOWN_SIZE");
	int maxSize_ = CONST(int, "MAX_COUNTDOWN_SIZE");
	int currentSize_ = 0;
	int sizeChangeRate_ = (maxSize_ - minSize_) / framesPerNum_; //ratio de crecimiento teniendo en cuenta que hay 4 texturas

	int posX_ = CONST(int, "WINDOW_WIDTH") / 2;
	int posY_ = CONST(int, "WINDOW_HEIGHT") / 2;

	// Texture* textures_[4] = { //3 2 1 go
	// 	SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::Three),
	// 	SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::Two),
	// 	SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::One),
	// 	SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::Go)
	// };

	Resources::TextureId texturesId_[4] = {
		Resources::Three,
		Resources::Two,
		Resources::One,
		Resources::Go
	};

	Texture* currentNumTexture_ = nullptr;

	GameMode* gMode_;
	FireBallGenerator* fGen_;

	Viewer* viewer = nullptr;

public:
	Countdown(GameMode* g) : Component(ComponentType::Countdown), gMode_(g) {}
	virtual ~Countdown() {}
	void init() override;
	virtual void update();
	void assignBoiler(FireBallGenerator* fGen) { fGen_ = fGen; }
};
