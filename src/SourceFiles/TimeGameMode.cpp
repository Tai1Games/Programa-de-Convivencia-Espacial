#include "TimeGameMode.h"
#include "PlayState.h"
#include "ThrownByPlayer.h"
#include "TomatoPool.h"

TimeGameMode::TimeGameMode(int nPlayers) :
	GameMode(nPlayers) {
}

TimeGameMode::~TimeGameMode() {
}

void TimeGameMode::init(PlayState* game)
{
	GameMode::init(game);
	tomatoPool_.init(game->getEntityManager(), game->getPhysicsWorld());

	sPerFrame_ = CONST(double, "SECONDS_PER_FRAME");
	timeToEnd_ = CONST(double, "TIMEMODE_TIME_TO_END");
	winWidth_ = CONST(int, "WINDOW_WIDTH");
	winHeigth_ = CONST(int, "WINDOW_HEIGHT");
	killsMarkerWidth_ = CONST(int, "KILLS_WIDTH");
	killsMarkerHeight_ = CONST(int, "KILLS_HEIGHT");
	suddenDeathRenderTime = CONST(double, "SUDDEN_DEATH_RENDER_TIME");

	for (int i = 0; i < nPlayers_; i++) {
		players_.push_back(PlayerFactory::createPlayerWithHealth(game->getEntityManager(), game->getPhysicsWorld(), i,
			Resources::Body, tilemap_->getPlayerSpawnPoint(i).x, tilemap_->getPlayerSpawnPoint(i).y, 3));
		playerKills_.push_back(0); //Initializes kills vector with 0 for all players.
	}

	for (Entity* e : *(state_->getEntityManager()->getWeaponVector())) {
		if(e != nullptr)
			e->addComponent<ThrownByPlayer>(this);
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
	canvasTimerTexture_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::CanvasTimerBackground);
	canvasTimerRect_.x = winWidth_ / 2 - CONST(int, "COUNTDOWN_UI_OFFSET_X");
	canvasTimerRect_.y = 0;
	canvasTimerRect_.w = CONST(int, "COUNTDOWN_UI_WIDTH");
	canvasTimerRect_.h = CONST(int, "COUNTDOWN_UI_HEIGTH");

	tomatoPool_.addTomato({ 40, 20 });
}

void TimeGameMode::render()
{
	int minutes = 0, seconds = 0;

	if (timeToEnd_ < timeSinceStart_) {
		if (roundFinished_ && winner_ != nullptr) {
			string winMsg = "Gana el jugador " + to_string(winner_->getComponent<PlayerData>(ComponentType::PlayerData)->getPlayerNumber() + 1);
			Texture ganador(SDL_Game::instance()->getRenderer(), winMsg,
				SDL_Game::instance()->getFontMngr()->getFont(Resources::NES_Chimera), { COLOR(0xffffffff) });
			ganador.render(winWidth_ / 2 - ganador.getWidth() / 2, winHeigth_ / 2);
		}
		else {
			suddenDeathRenderTimer += sPerFrame_;
			if (suddenDeathRenderTimer >= suddenDeathRenderTime) {
				suddenDeathRendering = !suddenDeathRendering;
				suddenDeathRenderTimer = 0;
			}
			if (suddenDeathRendering) {
				Texture* suddenDeathTexture = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::SuddenDeathTimeModeText);
				SDL_Rect suddenDeathRect;
				suddenDeathRect.x = winWidth_ / 2 - suddenDeathTexture->getWidth() / 2;
				suddenDeathRect.y = winHeigth_ / 2 - suddenDeathTexture->getHeight() / 2;
				suddenDeathRect.w = suddenDeathTexture->getWidth();
				suddenDeathRect.h = suddenDeathTexture->getHeight();
				suddenDeathTexture->render(suddenDeathRect);
			}

		}
	}
	else {
		minutes = (timeToEnd_ - timeSinceStart_) / 60;
		seconds = (int)(timeToEnd_ - timeSinceStart_) % 60;
	}
	renderTimer(seconds, minutes);
	renderKillMarker();
}

void TimeGameMode::update()
{

	timeSinceStart_ += sPerFrame_;
	if (timeSinceStart_ >= timeToEnd_ && !roundFinished_) {
		int maxPoints = 0;
		bool suddenDeath = false;
		for (int i = 0; i < playerKills_.size();i++) {
			if (playerKills_[i] > maxPoints) {
				maxPoints = playerKills_[i];
				winner_ = players_[i];
				suddenDeath = false;
			}
			else if (playerKills_[i]==maxPoints) {
				suddenDeath = true;
			}
		}
		if (!suddenDeath) {
			roundFinished_ = true;
			cout << "PLAYER: " << winner_->getComponent<PlayerData>(ComponentType::PlayerData)->getPlayerNumber() << " WON." << endl;
		}

	}
}

void TimeGameMode::addPoints(int playerID)
{
	playerKills_[playerID]++;
}

void TimeGameMode::playerKillsPlayer(int killerId, int deadId)
{
	addPoints(killerId);
}

void TimeGameMode::renderTimer(int seconds, int minutes) {
	canvasTimerTexture_->render(canvasTimerRect_);
	string timeText;
	if (seconds < 10) timeText = to_string(minutes) + ":0" + to_string(seconds);
	else timeText = to_string(minutes) + ":" + to_string(seconds);
	Texture timeTextTexture(SDL_Game::instance()->getRenderer(), timeText,
		SDL_Game::instance()->getFontMngr()->getFont(Resources::NES_Chimera), { COLOR(0xffffffff) });

	SDL_Rect timeTextRect;
	timeTextRect.x = winWidth_ / 2 - timeTextTexture.getWidth() * 0.7 / 2;
	timeTextRect.y = 7;
	timeTextRect.w = timeTextTexture.getWidth() * 0.7;
	timeTextRect.h = timeTextTexture.getHeight() * 0.7;

	timeTextTexture.render(timeTextRect);

}

void TimeGameMode::renderKillMarker() {

	for (int k = 0; k < playerKills_.size(); k++) {

		string killsNumb = "x" + to_string(playerKills_[k]);
		Texture killsNumbTexture(SDL_Game::instance()->getRenderer(), killsNumb,
			SDL_Game::instance()->getFontMngr()->getFont(Resources::NES_Chimera), { COLOR(0xffffffff) });
		
		SDL_Rect killsTextTexture;
		killsTextTexture.x = (int)playersPointsPos_[k].x;
		killsTextTexture.y = (int)playersPointsPos_[k].y;
		killsTextTexture.w = killsMarkerWidth_ * (calculateDigits(playerKills_[k] / 10) + 2);
		killsTextTexture.h = killsMarkerHeight_;

		killsNumbTexture.render(killsTextTexture);

		SDL_Rect coinImageRect;
		coinImageRect.x = killsTextTexture.x + killsTextTexture.w + skullUIMarginX_;
		coinImageRect.y = killsTextTexture.y - killsTextTexture.h/2;
		coinImageRect.w = skullUISize_;
		coinImageRect.h = skullUISize_;

		skullTextureUI_->render(coinImageRect);
	}
}

int TimeGameMode::calculateDigits(int points) {
	if (points > 0) return calculateDigits(points / 10) + 1;
	else return 0;
}