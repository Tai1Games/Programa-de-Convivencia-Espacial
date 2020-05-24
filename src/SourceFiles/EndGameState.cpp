#include "EndGameState.h"
#include "SDL_Game.h"
#include "InputHandler.h"
#include "MatchInfo.h"
#include "GameStateMachine.h"
#include "Texture.h"
#include "SDLTexturesManager.h"
#include "Resources.h"
#include "AnimatedViewer.h"
#include "Entity.h"
#include "UIViewer.h"
#include <algorithm>
#include <random>


bool comparePoints(MatchInfo::PlayerInfo* a, MatchInfo::PlayerInfo* b) { return a->totalPoints > b->totalPoints; }

void EndGameState::drawPlayer(int x, int y)
{
}

EndGameState::~EndGameState()
{
	delete entityManager_;		entityManager_ = nullptr;
}

void EndGameState::init()
{
	backgroundT_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::RocketRoom);
	vector<MatchInfo::PlayerInfo*>* playerInfo_ = SDL_Game::instance()->getStateMachine()->getMatchInfo()->getPlayersInfo();
	for (auto& player : *playerInfo_) {
		sortedPlayerInfo_.push_back(player);
	}
	sort(sortedPlayerInfo_.begin(), sortedPlayerInfo_.end(), comparePoints);
	int auxX = CONST(int, "LEADERBOARD_ANCHOR_X");
	int auxY = CONST(int, "LEADERBOARD_ANCHOR_Y");
	int iconOffset = CONST(int, "LEADERBOARD_ICON_OFFSET");
	int iconMargin = CONST(int, "LEADERBOARD_ICON_MARGIN");
	int zeroTex = Resources::NumZero;
	entityManager_ = new EntityManager();

	for (int i = 0; i < sortedPlayerInfo_.size(); i++) {
		Entity* auxEntity = entityManager_->addEntity();
		int y = auxY + (i * CONST(int, "LEADERBOARD_PLAYER_MARGIN"));
		int x = auxX;
		auxEntity->addComponent<UIViewer>(Resources::DeadBody, b2Vec2(auxX, y), 1);
		x += iconOffset;
		if (i < 3) {//si le toca medallita
			UIViewer* medalV = auxEntity->addComponent<UIViewer>(Resources::medals, b2Vec2(x, y), 1);
			medalV->setFrame(i);
		}
		//lista de chapitas
		vector<int> chapitas;
		for (int j = 0; j < sortedPlayerInfo_[i]->matchesWon.size(); j++) {
			for (int n = 0; n < sortedPlayerInfo_[i]->matchesWon[j]; n++) {
				chapitas.push_back(j);
			}
		}
		auto rng = std::default_random_engine{};
		std::shuffle(chapitas.begin(), chapitas.end(), rng);

		x += iconOffset;
		Resources::TextureId firstBadge = Resources::badgeCapitalism;
		for (auto& chapa : chapitas) {
			auxEntity->addComponent<UIViewer>((Resources::TextureId)firstBadge + chapa, b2Vec2(x, y), 1);
			x += iconOffset;
		}
	}
}
void EndGameState::render()
{
	backgroundT_->render(0, 0);
	GameState::render();
}

void EndGameState::update()
{
	if (anyButtonPush) {
		GameStateMachine* gsMachine = SDL_Game::instance()->getStateMachine();
		gsMachine->transitionToState(States::menu);
	}
}

void EndGameState::handleInput()
{
	GameState::handleInput();
	InputHandler* ih = SDL_Game::instance()->getInputHandler();

	if (ih->keyDownEvent() || ih->isButonDownEvent()) {
		anyButtonPush = true;
	}
	else {
		anyButtonPush = false;
	}
}

void EndGameState::onLoaded()
{
	SDL_Game::instance()->getStateMachine()->deleteState(States::midGame);
}