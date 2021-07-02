#include "GameMode.h"
#include "PlayState.h"
#include "HealthViewer.h"
#include "ImpulseViewer.h"
#include "PlayerData.h"

void GameMode::initProgressBars()
{
	int posicionesX [4] = {-12, -80, 20, -102};
	int posicionesY [4] = { 60, 60, -28, -28};

	for(int i = 0; i < players_.size(); i++)
	{
		b2Vec2 healthPos;
		healthPos = players_[i]->getComponent<HealthViewer>(ComponentType::HealthViewer)->getPos();
		healthViewerPos_.push_back(b2Vec2(healthPos.x + posicionesX[i], healthPos.y + posicionesY[i]));

		SDL_Rect r = {0,0,progressBar_->getFrameWidth(), progressBar_->getFrameHeight()};

		Entity* e = state_->getEntityManager()->addEntity();
		e->addComponent<Transform>(r, nullptr);
		e->addComponent<Viewer>(Resources::Tinky);
		progressBars_.push_back(e);
	}
}

void GameMode::renderProgressBars(const std::vector<double>& progressValues, const double& goalScore)
{
	for (int i = 0; i < players_.size(); i++)
	{
		SDL_Rect dest = {
			(int)healthViewerPos_[i].x,
			(int)healthViewerPos_[i].y,
			progressBar_->getFrameWidth() * (int)barsScale,
			progressBar_->getFrameHeight() * (int)barsScale
		};
		int value = min((progressValues[i] * progressBar_->getNumFramesX()) / goalScore, (double)progressBar_->getNumFramesX() - 1);
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		double angle = 0;
		if (i % 2 != 0) (i == 1) ? flip = SDL_FLIP_HORIZONTAL : angle = 180;		// gira cosas en los elementos de la derecha
		
		Viewer* v = GETCMP2(progressBars_[i], Viewer);
		v->setRenderRectangle(dest);
		v->setFrame(value, v->getFrameY());
		v->setAngle(angle);
		v->setFlip(flip);
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