#include "ControllerGameMode.h"
#include <map>

void ControllerGameMode::init(PlayState* game)  {
	GameMode::init(game);
	for (Entity* player : players_) controllerTimes_.push_back(0);
}

void ControllerGameMode::update() {
	if (!roundFinished_) {
		for (Entity* player : players_) {
			Hands* playerHand = player->getComponent<Hands>(ComponentType::Hands);
			PlayerData* pData = player->getComponent<PlayerData>(ComponentType::PlayerData);
			if (playerHand != nullptr && playerHand->getWeapon() == WeaponID::Mando) controllerTimes_[pData->getPlayerNumber()] += MS_PER_FRAME / 1000;
			if (controllerTimes_[pData->getPlayerNumber()] >= TIME_TO_WIN) {
				roundFinished_ = true;
				winner = player;
			}
		}
	}
}

void ControllerGameMode::render() {
	if (players_[0] != nullptr) {
		Texture score(SDL_Game::instance()->getRenderer(),
			to_string(controllerTimes_[0]).substr(0, 4 + log10(controllerTimes_[0])),
			SDL_Game::instance()->getFontMngr()->getFont(Resources::NES_Chimera),
			{ COLOR(0xffffffff) });
		score.render(10, 75);
	}
	if (players_[1] != nullptr) {
		Texture score(SDL_Game::instance()->getRenderer(),
			to_string(controllerTimes_[1]).substr(0, 4 + log10(controllerTimes_[1])),
			SDL_Game::instance()->getFontMngr()->getFont(Resources::NES_Chimera),
			{ COLOR(0xffffffff) });
		score.render(WINDOW_WIDTH - score.getWidth(), 75);
	}
	if (players_[2] != nullptr) {
		Texture score(SDL_Game::instance()->getRenderer(),
			to_string(controllerTimes_[2]).substr(0, 4 + log10(controllerTimes_[2])),
			SDL_Game::instance()->getFontMngr()->getFont(Resources::NES_Chimera),
			{ COLOR(0xffffffff) });
		score.render(10, WINDOW_HEIGHT - score.getHeight() - 75);
	}
	if (players_[3] != nullptr) {
		Texture score(SDL_Game::instance()->getRenderer(),
			to_string(controllerTimes_[3]).substr(0, 4 + log10(controllerTimes_[3])),
			SDL_Game::instance()->getFontMngr()->getFont(Resources::NES_Chimera),
			{ COLOR(0xffffffff) });
		score.render(WINDOW_WIDTH - score.getWidth(), WINDOW_HEIGHT - score.getHeight() - 75);
	}
	if (roundFinished_) {
		string winMsg = "Gana el jugador " + to_string(winner->getComponent<PlayerData>(ComponentType::PlayerData)->getPlayerNumber());
		Texture ganador(SDL_Game::instance()->getRenderer(), winMsg,
			SDL_Game::instance()->getFontMngr()->getFont(Resources::NES_Chimera), { COLOR(0xffffffff) });
		ganador.render(WINDOW_WIDTH / 2 - ganador.getWidth() / 2, WINDOW_HEIGHT / 2);
	}
}
