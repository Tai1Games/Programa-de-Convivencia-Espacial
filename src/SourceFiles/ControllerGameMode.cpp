#include "ControllerGameMode.h"
#include <map>

ControllerGameMode::~ControllerGameMode()
{
	for (auto ePB : emptyProgressBars_) delete ePB;
	for (auto pB : progressBars_) delete pB;
}

void ControllerGameMode::init(PlayState* game)  {
	GameMode::init(game);
	//Instancia necesaria para poder coger el puntero al mando (si usáramos una función void no haría falta)
	WeaponFactory wF;
	controller_ = wF.makeController(state_->getEntityManager(), state_->getPhysicsWorld(), b2Vec2(18, 5), b2Vec2(0.5, 0.5));
	for (Entity* player : players_) controllerTimes_.push_back(0);

	//Posiciones de las barras respecto a los HealthViewer
	b2Vec2 healthPos = players_[0]->getComponent<HealthViewer>(ComponentType::HealthViewer)->getPos();
	emptyProgressBars_.push_back(new Viewer(Resources::EmptyProgressBar, b2Vec2(healthPos.x-15, healthPos.y+60), 0.08, 0));
	progressBars_.push_back(new Viewer(Resources::ProgressBar, b2Vec2(healthPos.x - 15, healthPos.y + 60), 0.08, 0));
	healthPos = players_[1]->getComponent<HealthViewer>(ComponentType::HealthViewer)->getPos();
	emptyProgressBars_.push_back(new Viewer(Resources::EmptyProgressBar, b2Vec2(healthPos.x - 115, healthPos.y + 60), 0.08, 0));
	progressBars_.push_back(new Viewer(Resources::ProgressBar, b2Vec2(healthPos.x - 115, healthPos.y + 60), 0.08, 0));
	healthPos = players_[2]->getComponent<HealthViewer>(ComponentType::HealthViewer)->getPos();
	emptyProgressBars_.push_back(new Viewer(Resources::EmptyProgressBar, b2Vec2(healthPos.x + 13, healthPos.y - 40), 0.08, 0));
	progressBars_.push_back(new Viewer(Resources::ProgressBar, b2Vec2(healthPos.x + 13, healthPos.y - 40), 0.08, 0));
	healthPos = players_[3]->getComponent<HealthViewer>(ComponentType::HealthViewer)->getPos();
	emptyProgressBars_.push_back(new Viewer(Resources::EmptyProgressBar, b2Vec2(healthPos.x - 90, healthPos.y - 40), 0.08, 0));
	progressBars_.push_back(new Viewer(Resources::ProgressBar, b2Vec2(healthPos.x - 90, healthPos.y - 40), 0.08, 0));

	for (auto ePB : emptyProgressBars_) ePB->init();
}

void ControllerGameMode::update() {
	if (!roundFinished_) {
		if (controller_->isPicked()) {
			controllerTimes_[controller_->getPlayerId()] += (CONST(double, "MS_PER_FRAME") / 1000);
			if (controllerTimes_[controller_->getPlayerId()] >= CONST(double, "TIME_TO_WIN")) {
				roundFinished_ = true;
				winner_ = players_[controller_->getPlayerId()];
			}
		}
	}
}

void ControllerGameMode::updateProgressBar(Viewer& progressBar,const float& progressValue)
{
	progressBar.init();
	progressBar.setClipUIElement(SDL_Rect{ 0, 0, int(progressBar.getWHUIElement().x * progressValue), int(progressBar.getWHUIElement().y) });
	progressBar.setWHUIElement(b2Vec2(progressBar.getWHUIElement().x * progressValue, progressBar.getWHUIElement().y));
	progressBar.draw();
}

void ControllerGameMode::render() {
	for (auto ePB : emptyProgressBars_) ePB->draw();

	if (players_[0] != nullptr) {
		updateProgressBar(*progressBars_[0], controllerTimes_[0] / CONST(double, "TIME_TO_WIN"));
	}
	if (players_[1] != nullptr) {
		updateProgressBar(*progressBars_[1], controllerTimes_[1] / CONST(double, "TIME_TO_WIN"));
	}
	if (players_[2] != nullptr) {
		updateProgressBar(*progressBars_[2], controllerTimes_[2] / CONST(double, "TIME_TO_WIN"));
	}
	if (players_[3] != nullptr) {
		updateProgressBar(*progressBars_[3], controllerTimes_[3] / CONST(double, "TIME_TO_WIN"));
	}
	if (roundFinished_) {
		string winMsg = "Gana el jugador " + to_string(winner_->getComponent<PlayerData>(ComponentType::PlayerData)->getPlayerNumber());
		Texture ganador(SDL_Game::instance()->getRenderer(), winMsg,
			SDL_Game::instance()->getFontMngr()->getFont(Resources::NES_Chimera), { COLOR(0xffffffff) });
		ganador.render(CONST(int, "WINDOW_WIDTH") / 2 - ganador.getWidth() / 2, CONST(int, "WINDOW_HEIGHT") / 2);
	}
}
