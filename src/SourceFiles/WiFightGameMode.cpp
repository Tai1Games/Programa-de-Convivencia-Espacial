#include "WiFightGameMode.h"
#include "Resources.h"
#include "ParticleEmitter.h"
#include "RouterLogic.h"
#include "ColliderViewer.h"

void WiFightGameMode::init(PlayState* game)
{
	GameMode::init(game);

	GameMode::createPlayers(game);
	playerProgress_.reserve(nPlayers_);
	for (int k = 0; k < nPlayers_; k++) {
		playerProgress_.push_back(0);
	}

	Entity* router = ObjectFactory::makeRouter(state_->getEntityManager(), state_->getPhysicsWorld(), tilemap_->getObjSpecialSpawnPos(), this, &wifiWavesPool_);

	wifiWavesPool_.init(state_->getEntityManager(), state_->getPhysicsWorld(), router->getComponent<Collider>(ComponentType::Collider));

	GameMode::initProgressBars();

}

void WiFightGameMode::render()
{
	GameMode::renderProgressBars(playerProgress_, CONST(double, "POINTS_TO_WIN"));

	if (roundFinished_) {
		string winMsg = "Gana el jugador " + (winnerId_ + 1);
		Texture ganador(SDL_Game::instance()->getRenderer(), winMsg,
			SDL_Game::instance()->getFontMngr()->getFont(Resources::NES_Chimera), { COLOR(0xffffffff) });
		ganador.render(CONST(int, "WINDOW_WIDTH") / 2 - ganador.getWidth() / 2, CONST(int, "WINDOW_HEIGHT") / 2);
	}
}

void WiFightGameMode::addPoints(int player, double sumPoints)
{
	if (!roundFinished_) {
		playerProgress_[player] += sumPoints;
		//cout << "Player " << player << " progress: " << playerProgress_[player] << endl;
		if (playerProgress_[player] >= CONST(int, "POINTS_TO_WIN")) {
			cout << "Player " << player << " won!" << endl;
			winnerId_ = player;
			roundFinished_ = true;
		}
	}
}
