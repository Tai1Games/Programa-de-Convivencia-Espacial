#include "GameMode.h"
#include "PlayState.h"

void GameMode::initProgressBars()
{
	//Posiciones de las barras respecto a los HealthViewer
	b2Vec2 healthPos = players_[0]->getComponent<HealthViewer>(ComponentType::HealthViewer)->getPos();
	emptyProgressBars_.push_back(new Viewer(Resources::EmptyProgressBar, b2Vec2(healthPos.x - 12, healthPos.y + 60), 0.07, 0));
	progressBars_.push_back(new Viewer(Resources::ProgressBar, b2Vec2(healthPos.x - 12, healthPos.y + 60), 0.07, 0));
	healthPos = players_[1]->getComponent<HealthViewer>(ComponentType::HealthViewer)->getPos();
	emptyProgressBars_.push_back(new Viewer(Resources::EmptyProgressBar2, b2Vec2(healthPos.x - 60, healthPos.y + 60), 0.07, 180, SDL_FLIP_HORIZONTAL));
	progressBars_.push_back(new Viewer(Resources::ProgressBar2, b2Vec2(healthPos.x - 60, healthPos.y + 60), 0.07, 180, SDL_FLIP_HORIZONTAL));
	healthPos = players_[2]->getComponent<HealthViewer>(ComponentType::HealthViewer)->getPos();
	emptyProgressBars_.push_back(new Viewer(Resources::EmptyProgressBar, b2Vec2(healthPos.x + 20, healthPos.y - 28), 0.07, 0));
	progressBars_.push_back(new Viewer(Resources::ProgressBar, b2Vec2(healthPos.x + 20, healthPos.y - 28), 0.07, 0));
	healthPos = players_[3]->getComponent<HealthViewer>(ComponentType::HealthViewer)->getPos();
	emptyProgressBars_.push_back(new Viewer(Resources::EmptyProgressBar2, b2Vec2(healthPos.x - 92, healthPos.y - 28), 0.07, 0, SDL_FLIP_HORIZONTAL));
	progressBars_.push_back(new Viewer(Resources::ProgressBar2, b2Vec2(healthPos.x - 92, healthPos.y - 28), 0.07, 180, SDL_FLIP_HORIZONTAL));

	for (auto ePB : emptyProgressBars_) ePB->init();
}

void GameMode::updateProgressBar(Viewer& progressBar, const float& progressValue, int player)
{
	float value = (player % 2 == 0) ? progressValue : 1 - progressValue;
	progressBar.init();
	progressBar.setClipUIElement(SDL_Rect{ 0, 0, int(progressBar.getWHUIElement().x * value), int(progressBar.getWHUIElement().y) });
	progressBar.setWHUIElement(b2Vec2(progressBar.getWHUIElement().x * value, progressBar.getWHUIElement().y));
	progressBar.draw();
}

void GameMode::renderProgressBars(const std::vector<double>& progressValues, const double& goalScore)
{
	for (auto ePB : emptyProgressBars_) ePB->draw();

	for (int i = 0; i < players_.size(); i++) {
		updateProgressBar(*progressBars_[i], progressValues[i] / goalScore, i);
	}
}

void GameMode::init(PlayState* state) {
	state_ = state;
	players_ = state->getPlayers();
}