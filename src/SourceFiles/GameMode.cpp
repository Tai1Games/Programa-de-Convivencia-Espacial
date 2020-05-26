#include "GameMode.h"
#include "PlayState.h"
#include "HealthViewer.h"
#include "ImpulseViewer.h"
#include "PlayerData.h"

void GameMode::initProgressBars()
{
	b2Vec2 healthPos;
	healthPos = players_[0]->getComponent<HealthViewer>(ComponentType::HealthViewer)->getPos();
	healthViewerPos_.push_back(b2Vec2(healthPos.x - 12, healthPos.y + 60));
	if (players_.size() > 1) {
		healthPos = players_[1]->getComponent<HealthViewer>(ComponentType::HealthViewer)->getPos();
		healthViewerPos_.push_back(b2Vec2(healthPos.x - 80, healthPos.y + 60));
	}
	if (players_.size() > 2) {
		healthPos = players_[2]->getComponent<HealthViewer>(ComponentType::HealthViewer)->getPos();
		healthViewerPos_.push_back(b2Vec2(healthPos.x + 20, healthPos.y - 28));
	}
	if (players_.size() > 3) {
		healthPos = players_[3]->getComponent<HealthViewer>(ComponentType::HealthViewer)->getPos();
		healthViewerPos_.push_back(b2Vec2(healthPos.x - 102, healthPos.y - 28));
	}
}

void GameMode::renderProgressBars(const std::vector<double>& progressValues, const double& goalScore)
{
	for (int i = 0; i < players_.size(); i++) {
		SDL_Rect dest = {
			healthViewerPos_[i].x,
			healthViewerPos_[i].y,
			progressBar_->getFrameWidth() * barsScale,
			progressBar_->getFrameHeight() * barsScale
		};
		int value = min((progressValues[i] * progressBar_->getNumFramesX()) / goalScore, (double)progressBar_->getNumFramesX() - 1);
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		double angle = 0;
		if (i % 2 != 0) (i == 1) ? flip = SDL_FLIP_HORIZONTAL : angle = 180;		// gira cosas en los elementos de la derecha
		progressBar_->render(dest, angle, value, 0, flip);
	}
}

void GameMode::init(PlayState* game) {
	state_ = game;
	progressBar_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::TextureId::ProgressBar);
}

void GameMode::activateControl() {
	for (Entity* p : players_) {
		p->addComponent<Hands>(Resources::Hands);
		p->addComponent<AttachesToObjects>();
		p->addComponent<ParticleEmitter>(Vector2D(0, -1), Resources::Foam, CONST(float, "IMPULSE_PARTICLE_SPEED"),
			CONST(int, "IMPULSE_PARTICLE_NTEXTURES"), CONST(int, "IMPULSE_PARTICLE_GEN_ODDS"), CONST(int, "IMPULSE_PARTICLE_LIFETIME"),
			CONST(int, "IMPULSE_PARTICLE_SIZE"), CONST(int, "IMPULSE_PARTICLE_EMIT_TIME"), CONST(int, "IMPULSE_PARTICLE_SPEED_VAR"),
			CONST(int, "IMPULSE_PARTICLE_CONE_ANGLE"));
		p->addComponent<PlayerController>();
		p->addComponent<ImpulseViewer>(Resources::ImpulseArrow, Resources::ImpulseBackground);
	}
}

void GameMode::createPlayers(PlayState* game) {
	for (int i = 0; i < nPlayers_; i++) {
		players_.push_back(PlayerFactory::createPlayerWithHealth(game->getEntityManager(), game->getPhysicsWorld(), i,
			Resources::Body, tilemap_->getPlayerSpawnPoint(i).x, tilemap_->getPlayerSpawnPoint(i).y, (*matchInfo_->getPlayersInfo())[i]->inputBinder, 3, (*matchInfo_->getPlayersInfo())[i]->playerSkin));
	}
}

void GameMode::update() {
	if (roundFinished_) {
		matchInfo_->AddVictory(winnerId_, gamemodeId_);
		cout << "Player " << winnerId_ << " won" << endl;
		SDL_Game::instance()->getStateMachine()->transitionToState(States::midGame, winnerId_);
	}
	for (int i = 0; i < players_.size(); i++) {
		if (players_[i]->getComponent<PlayerData>(ComponentType::PlayerData)->getBinder()->secretWinButton()) {
			matchInfo_->AddVictory(players_[i]->getComponent<PlayerData>(ComponentType::PlayerData)->getPlayerNumber(), gamemodeId_);
			SDL_Game::instance()->getStateMachine()->transitionToState(States::midGame, players_[i]->getComponent<PlayerData>(ComponentType::PlayerData)->getPlayerNumber());
		}
	}
}