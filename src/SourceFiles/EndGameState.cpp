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
	int zeroTex = Resources::NumZero;
	entityManager_ = new EntityManager();

	for (int i = 0; i < sortedPlayerInfo_.size(); i++) {
		Entity* auxEntity = entityManager_->addEntity();
		int y = auxY + i * CONST(int, "LEADERBOARD_PLAYER_MARGIN");
		auxEntity->addComponent<UIViewer>(Resources::Token, b2Vec2(auxX, y), 0);
		auxEntity->addComponent<UIViewer>((Resources::TextureId)zeroTex + i, b2Vec2(auxX + CONST(int, "LEADERBOARD_ICON_OFFSET"), y), 0);
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