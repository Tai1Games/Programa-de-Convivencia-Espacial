#include "GameMode.h"
#include "PlayState.h"

void GameMode::initProgressBars()
{
	for (int i = 0; i < players_.size(); i++) {
		if (i % 2 == 0) {
			emptyProgressBars_.push_back(new Texture(*SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::EmptyProgressBar)));
			progressBars_.push_back(new Texture(*SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::ProgressBar)));
		}
		else {
			emptyProgressBars_.push_back(new Texture(*SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::EmptyProgressBar2)));
			progressBars_.push_back(new Texture(*SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::ProgressBar2)));
		}
	}
	b2Vec2 healthPos = players_[0]->getComponent<HealthViewer>(ComponentType::HealthViewer)->getPos();
	healthViewerPos_.push_back(b2Vec2(healthPos.x - 12, healthPos.y + 60));
	healthPos = players_[1]->getComponent<HealthViewer>(ComponentType::HealthViewer)->getPos();
	healthViewerPos_.push_back(b2Vec2(healthPos.x - 60, healthPos.y + 60));
	healthPos = players_[2]->getComponent<HealthViewer>(ComponentType::HealthViewer)->getPos();
	healthViewerPos_.push_back(b2Vec2(healthPos.x + 20, healthPos.y - 28));
	healthPos = players_[3]->getComponent<HealthViewer>(ComponentType::HealthViewer)->getPos();
	healthViewerPos_.push_back(b2Vec2(healthPos.x - 92, healthPos.y - 28));
}

void GameMode::renderProgressBars(const std::vector<double>& progressValues, const double& goalScore)
{
	float barsScale = 0.07;
	for (int i = 0; i < players_.size(); i++) {
		float angle = (i % 2 == 0) ? 0 : 180;
		SDL_RendererFlip flip = (i % 2 == 0) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

		//Barra de progreso vacía
		SDL_Rect dest = { healthViewerPos_[i].x, healthViewerPos_[i].y ,
		emptyProgressBars_[i]->getWidth() * barsScale, emptyProgressBars_[i]->getHeight() * barsScale};
		emptyProgressBars_[i]->render(dest,angle,flip);

		//Barra de progreso rellena
		float progresV = progressValues[i] / goalScore;
		float value = (i % 2 == 0) ? progresV : 1 - progresV;
		dest = { int(healthViewerPos_[i].x), int(healthViewerPos_[i].y), 
		int(progressBars_[i]->getWidth() * barsScale * value), int(progressBars_[i]->getHeight() * barsScale)};
		SDL_Rect clip = { 0, 0, int(progressBars_[i]->getWidth() * value), int(progressBars_[i]->getHeight()) };
		progressBars_[i]->render(dest, angle, clip, flip);
	}
}

void GameMode::init(PlayState* state) {
	state_ = state;
	players_ = state->getPlayers();
}