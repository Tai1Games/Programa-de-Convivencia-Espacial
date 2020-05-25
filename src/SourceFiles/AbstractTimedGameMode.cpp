#include "AbstractTimedGameMode.h"
#include "PlayState.h"

void AbstractTimedGameMode::init(PlayState* game)
{
	GameMode::init(game);
	sPerFrame_ = CONST(double, "SECONDS_PER_FRAME");
	suddenDeathRenderTime_ = CONST(double, "SUDDEN_DEATH_RENDER_TIME");

	winWidth_ = CONST(int, "WINDOW_WIDTH");
	winHeigth_ = CONST(int, "WINDOW_HEIGHT");

	halfWinWidth_ = winWidth_ * 0.5;
	halfWinHeight_ = winHeigth_ * 0.5;
	canvasTimerTexture_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::CanvasTimerBackground);
	canvasTimerRect_.x = halfWinWidth_ - CONST(int, "COUNTDOWN_UI_OFFSET_X");
	canvasTimerRect_.y = 0;
	canvasTimerRect_.w = CONST(int, "COUNTDOWN_UI_WIDTH");
	canvasTimerRect_.h = CONST(int, "COUNTDOWN_UI_HEIGTH");
}

void AbstractTimedGameMode::render()
{
	int minutes = 0, seconds = 0;

	if (timeToEnd_ < timeSinceStart_) {
		if (roundFinished_ && winnerId_ != -1) {
			Texture* ganador = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::winner1 + winnerId_);
			ganador->render(halfWinWidth_ - ganador->getWidth() * 0.5, halfWinHeight_);
		}
		else {
			suddenDeathRenderTimer_ += sPerFrame_;
			if (suddenDeathRenderTimer_ >= suddenDeathRenderTime_) {
				suddenDeathRendering_ = !suddenDeathRendering_;
				suddenDeathRenderTimer_ = 0;
			}
			if (suddenDeathRendering_) {
				SDL_Rect suddenDeathRect;
				suddenDeathRect.x = halfWinWidth_ - suddenDeathTexture_->getWidth() * 0.5;
				suddenDeathRect.y = halfWinHeight_ - suddenDeathTexture_->getHeight() * 0.5;
				suddenDeathRect.w = suddenDeathTexture_->getWidth();
				suddenDeathRect.h = suddenDeathTexture_->getHeight();
				suddenDeathTexture_->render(suddenDeathRect);
			}
		}
	}
	else {
		minutes = (timeToEnd_ - timeSinceStart_) * minutesFreq_;
		seconds = (int)(timeToEnd_ - timeSinceStart_) % 60;
	}
	renderTimer(seconds, minutes);

}

void AbstractTimedGameMode::renderTimer(int seconds, int minutes)
{
	canvasTimerTexture_->render(canvasTimerRect_);

	vector<Texture*> timeTextTextures;
	int l = (minutes > 0) ? log10(minutes) : log(1);

	for (int i = 0; i <= l; i++) { //sacamos los d�gitos y los metemos en un vector
		timeTextTextures.push_back(SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::NumZero + minutes / pow(10, l - i)));
		minutes %= 10;
	}
	timeTextTextures.push_back(SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::Colon));

	for (int i = 0; i <= 1; i++) { //sacamos los d�gitos y los metemos en un vector
		timeTextTextures.push_back(SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::NumZero + seconds / pow(10, 1 - i)));
		seconds %= 10;
	}

	for (int i = 0; i < timeTextTextures.size(); i++) {
		SDL_Rect timeTextRect;
		timeTextRect.x = halfWinWidth_ - timeTextTextures[i]->getWidth()/3 * timeTextTextures.size() + timeTextTextures[i]->getWidth()/1.5 * i;
		timeTextRect.y = 7;
		timeTextRect.w = timeTextTextures[i]->getWidth() * 0.7;
		timeTextRect.h = timeTextTextures[i]->getHeight() * 0.7;

		timeTextTextures[i]->render(timeTextRect);
	}
}

void AbstractTimedGameMode::update()
{
	GameMode::update();
}

void AbstractTimedGameMode::activateControl()
{
	setActiveTimer(true);
	GameMode::activateControl();
}

void AbstractTimedGameMode::updateTime(const vector<int>& playerPoints)
{
	if (activeTimer_) {
		timeSinceStart_ += sPerFrame_;
		if (timeSinceStart_ >= timeToEnd_ && !roundFinished_) {
			int maxPoints = 0;
			bool suddenDeath = false;
			for (int i = 0; i < playerPoints.size(); i++) {
				if (playerPoints[i] > maxPoints) {
					maxPoints = playerPoints[i];
					winnerId_ = i;
					suddenDeath = false;
				}
				else if (playerPoints[i] == maxPoints) {
					suddenDeath = true;
				}
			}
			if (!suddenDeath) {
				roundFinished_ = true;
				cout << "PLAYER: " << winnerId_ << " WON." << endl;
			}
		}
	}
}
