#include "CapitalismGameMode.h"
#include "FireBallGenerator.h"


void CapitalismGameMode::init(PlayState* game)
{
	AbstractTimedGameMode::init(game);
	coinPool_.init(game->getEntityManager(), game->getPhysicsWorld());
	//NEED TO DELETE ---
	tomatoPool_.init(game->getEntityManager(), game->getPhysicsWorld());
	//------------------
	//Load of constants
	/*sPerFrame_ = CONST(double, "SECONDS_PER_FRAME");*/
	timeToEnd_ = CONST(double, "CAPITALISM_TIME_TO_END");
	suddenDeathTexture_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::SuddenDeathCapitalismModeText);
	
	spawnTime_ = CONST(double, "TIME_TO_SPAWN_COIN");
	minimumSpawnTime_ = CONST(double, "MINIMUM_SPAWN_COIN_TIME");
	maxCoins_ = CONST(int, "TOTAL_COIN_NUMBER");
	//winWidth_ = CONST(int, "WINDOW_WIDTH");
	//winHeigth_ = CONST(int, "WINDOW_HEIGHT");
	coinUIRadius_ = CONST(int, "COIN_UI_RADIUS");
	coinUIMarginX_ = CONST(int, "COIN_UI_MARGIN_X");
	coinUIMarginY_ = CONST(int, "COIN_UI_MARGIN_Y");
	coinUISpriteScale_ = CONST(double, "COIN_UI_SPRITE_SCALE");
	fontCharacterWidth_ = CONST(double, "NES_WIDTH_PER_CHARACTER");
	//suddenDeathRenderTime = CONST(double, "SUDDEN_DEATH_RENDER_TIME");

	currentSpawnTime_ = spawnTime_;
	coinSpawnersPositions_ = tilemap_->getCoinsSpawnPoints();

	for (b2Vec2 pos : coinSpawnersPositions_) {
		roombaColliders_.push_back(ObjectFactory::makeRoomba(game->getEntityManager(),
			game->getPhysicsWorld(), pos)->getComponent<Collider>(ComponentType::Collider));
	}

	for (int k = 0; k < nPlayers_; k++) {
		players_.push_back(PlayerFactory::createPlayerWithWallet(game->getEntityManager(), game->getPhysicsWorld(), k,
			Resources::Body, tilemap_->getPlayerSpawnPoint(k).x, tilemap_->getPlayerSpawnPoint(k).y, this));
		playerWallets_.push_back(players_[k]->getComponent<Wallet>(ComponentType::Wallet));
		playerCoins_.push_back(playerWallets_[k]->getCoins());
	}

	//UI Elements.
	coinTextureUI_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::CoinUI);
	//canvasTimerTexture_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::CanvasTimerBackground);
	//canvasTimerRect_.x = winWidth_ / 2 - CONST(int, "COUNTDOWN_UI_OFFSET_X");
	//canvasTimerRect_.y = 0;
	//canvasTimerRect_.w = CONST(int, "COUNTDOWN_UI_WIDTH");
	//canvasTimerRect_.h = CONST(int, "COUNTDOWN_UI_HEIGTH");

	//NEED TO DELETE
	tomatoPool_.addTomato({ 40, 20 });
	//--
}

void CapitalismGameMode::render() {

	AbstractTimedGameMode::render();

	//canvasTimerTexture_->render(canvasTimerRect_);
	//string timeText;
	//if (seconds < 10) timeText = to_string(minutes) + ":0" + to_string(seconds);
	//else timeText = to_string(minutes) + ":" + to_string(seconds);
	//Texture timeTextTexture(SDL_Game::instance()->getRenderer(), timeText,
	//	SDL_Game::instance()->getFontMngr()->getFont(Resources::NES_Chimera), { COLOR(0xffffffff) });

	//SDL_Rect timeTextRect;
	//timeTextRect.x = winWidth_ / 2 - timeTextTexture.getWidth() * 0.7 / 2;
	//timeTextRect.y = 7;
	//timeTextRect.w = timeTextTexture.getWidth() * 0.7;
	//timeTextRect.h = timeTextTexture.getHeight() * 0.7;

	//timeTextTexture.render(timeTextRect);

	for (int k = 0; k < playerWallets_.size(); k++) {

		string coinNumb = to_string(playerWallets_[k]->getCoins());
		Texture coinNumbTexture(SDL_Game::instance()->getRenderer(), coinNumb,
			SDL_Game::instance()->getFontMngr()->getFont(Resources::NES_Chimera), { COLOR(0xffffffff) });

		SDL_Rect coinImageRect;
		coinImageRect.x = (k % 2 == 0) ? coinUIMarginX_ : winWidth_ - coinUIMarginX_ - coinUIRadius_;
		coinImageRect.y = (k < 2) ? coinUIMarginY_ : winHeigth_ - coinUIMarginY_ - coinUIRadius_;
		coinImageRect.w = coinUIRadius_;
		coinImageRect.h = coinUIRadius_;

		SDL_Rect coinTextRect;
		coinTextRect.x = coinImageRect.x + coinUIRadius_ * 0.3 - (fontCharacterWidth_ * (coinNumb.size() - 1));
		coinTextRect.y = coinImageRect.y + coinUIRadius_ * 0.3;
		coinTextRect.w = coinNumbTexture.getWidth() * coinUISpriteScale_;
		coinTextRect.h = coinNumbTexture.getHeight() * coinUISpriteScale_;

		coinTextureUI_->render(coinImageRect);
		coinNumbTexture.render(coinTextRect);
	}
}

void CapitalismGameMode::update() {

	updateTime(playerCoins_);

	if (coinsSpawned_ < maxCoins_) {
		timeSinceSpawn_ += sPerFrame_;
		if (timeSinceSpawn_ >= currentSpawnTime_) {
			timeSinceSpawn_ = 0;
			if (timeToEnd_ < timeSinceStart_) currentSpawnTime_ = minimumSpawnTime_;
			else currentSpawnTime_ = spawnTime_ - ((timeSinceStart_ / timeToEnd_) * spawnTime_);
			b2Vec2 position = roombaColliders_[rand() % roombaColliders_.size()]->getPos();
			createCoin(position);
			coinsSpawned_++;
		}
	}
}

void CapitalismGameMode::createCoin(b2Vec2 spawnPos, int player,int val) {
	coinPool_.addCoin(spawnPos, player, val);
}