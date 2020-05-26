#include "TimeGameMode.h"
#include "PlayState.h"
#include "ThrownByPlayer.h"
#include "TomatoPool.h"

TimeGameMode::TimeGameMode(MatchInfo* mInfo) :
	AbstractTimedGameMode(mInfo, GamemodeID::Timed) {
}

TimeGameMode::~TimeGameMode() {
}

void TimeGameMode::init(PlayState* game)
{
	AbstractTimedGameMode::init(game);

	timeToEnd_ = CONST(double, "TIMEMODE_TIME_TO_END");
	suddenDeathTexture_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::SuddenDeathTimeModeText);

	killsMarkerWidth_ = CONST(int, "KILLS_WIDTH");
	killsMarkerHeight_ = CONST(int, "KILLS_HEIGHT");

	GameMode::createPlayers(game);
	for (int i = 0; i < nPlayers_; i++) {
		playerKills_.push_back(0); //Initializes kills vector with 0 for all players.
	}

	for (int i = 0; i < players_.size(); i++) {
		Entity* e = players_[i];
		playersHealth_.push_back(e->getComponent<Health>(ComponentType::Health)); //Initializes playersHealth vector catching a reference to Health on entity e.
		HealthViewer* hV = (e->getComponent<HealthViewer>(ComponentType::HealthViewer)); //Obtains a reference to the HealthViewer component of entity e. This is used to calculate where the kills will be drawn
		b2Vec2 p = hV->getPos();
		int hVW = hV->getWidth();

		if (i % 2 != 0) {
			p.x = p.x - hVW + killsMarkerWidth_;
		}

		// draws P1 and P2 kill marker below health viewer, P3 and P4 kill marker above health viewer
		if (i < 2)
			p.y += (CONST(int, "KILLS_VERTICAL_OFFSET") + CONST(int, "LIFE_HEIGTH"));
		else
			p.y -= (CONST(int, "LIFE_HEIGTH") - CONST(int, "KILLS_VERTICAL_OFFSET"));

		playersPointsPos_.push_back(p);
	}

	//UI Elements.
	skullUISize_ = CONST(int, "SKULL_UI_SIZE");
	skullUIMarginX_ = CONST(int, "SKULL_UI_OFFSET_X");
	skullTextureUI_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::SkullUI);
}

void TimeGameMode::render()
{
	AbstractTimedGameMode::render();

	renderKillMarker();
}

void TimeGameMode::update()
{
	updateTime(playerKills_);
	AbstractTimedGameMode::update();
}

void TimeGameMode::addPoints(int playerID)
{
	playerKills_[playerID]++;
}

void TimeGameMode::playerKillsPlayer(int killerId, int deadId)
{
	addPoints(killerId);
}


void TimeGameMode::renderKillMarker() {
	for (int k = 0; k < playerKills_.size(); k++) {
		string killsNumb = to_string(playerKills_[k]);
		vector<Texture*> killsNumbTextures;

		for (int i = 0; i < killsNumb.length(); i++) { //sacamos los dígitos y los metemos en un vector
			killsNumbTextures.push_back(SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::Zero + killsNumb[i] - '0'));
		}

		SDL_Rect killsTextTexture;
		for (int i = 0; i < killsNumbTextures.size(); i++) {
			killsTextTexture.x = (int)playersPointsPos_[k].x + killsNumbTextures[i]->getWidth() / 1.35 * (i + 1);
			killsTextTexture.y = (int)playersPointsPos_[k].y;
			killsTextTexture.w = killsMarkerWidth_;
			killsTextTexture.h = killsMarkerHeight_;

			killsNumbTextures[i]->render(killsTextTexture, 0, 0);
		}

		SDL_Rect skullImageRect;
		skullImageRect.x = killsTextTexture.x + killsTextTexture.w + skullUIMarginX_;
		skullImageRect.y = killsTextTexture.y - killsTextTexture.h * 0.5;
		skullImageRect.w = skullUISize_;
		skullImageRect.h = skullUISize_;

		skullTextureUI_->render(skullImageRect, 0, 0);
	}
}