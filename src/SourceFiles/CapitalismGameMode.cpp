#include "CapitalismGameMode.h"
#include "FireBallGenerator.h"
#include "ObjectFactory.h"

void CapitalismGameMode::init(PlayState* game)
{
	AbstractTimedGameMode::init(game);
	coinPool_.init(game->getEntityManager(), game->getPhysicsWorld());
	//Load of constants
	timeToEnd_ = CONST(double, "CAPITALISM_TIME_TO_END");
	suddenDeathTexture_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::SuddenDeathCapitalismModeText);

	spawnTime_ = CONST(double, "TIME_TO_SPAWN_COIN");
	minimumSpawnTime_ = CONST(double, "MINIMUM_SPAWN_COIN_TIME");
	maxCoins_ = CONST(int, "TOTAL_COIN_NUMBER");
	coinUIRadius_ = CONST(int, "COIN_UI_RADIUS");
	coinUIMarginX_ = CONST(int, "COIN_UI_MARGIN_X");
	coinUIMarginY_ = CONST(int, "COIN_UI_MARGIN_Y");
	coinUISpriteScale_ = CONST(double, "COIN_UI_SPRITE_SCALE");
	fontCharacterWidth_ = CONST(double, "NES_WIDTH_PER_CHARACTER");

	currentSpawnTime_ = spawnTime_;
	coinSpawnersPositions_ = tilemap_->getCoinsSpawnPoints();

	for (b2Vec2 pos : coinSpawnersPositions_) {
		roombaColliders_.push_back(ObjectFactory::makeRoomba(game->getEntityManager(),
			game->getPhysicsWorld(), pos)->getComponent<Collider>(ComponentType::Collider));
	}

	createPlayers(game);


	//UI Elements.
	coinTextureUI_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::CoinUI);
}

void CapitalismGameMode::render() {

	AbstractTimedGameMode::render();

	renderCoinsMarker();
}

void CapitalismGameMode::createPlayers(PlayState* game) {
	for (int k = 0; k < nPlayers_; k++) {
		players_.push_back(PlayerFactory::createPlayerWithWallet(game->getEntityManager(), game->getPhysicsWorld(), k,
			Resources::Body, tilemap_->getPlayerSpawnPoint(k).x, tilemap_->getPlayerSpawnPoint(k).y, (*matchInfo_->getPlayersInfo())[k]->inputBinder, this, (*matchInfo_->getPlayersInfo())[k]->playerSkin));
		playerWallets_.push_back(players_[k]->getComponent<Wallet>(ComponentType::Wallet));
		playerCoins_.push_back(playerWallets_[k]->getCoins());
	}
}

void CapitalismGameMode::update() {

	for (int i = 0; i < playerCoins_.size(); i++) { playerCoins_[i] = playerWallets_[i]->getCoins(); }
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
	AbstractTimedGameMode::update();
}

void CapitalismGameMode::renderCoinsMarker()
{
	for (int k = 0; k < playerWallets_.size(); k++) {

		string coinNumb = to_string(playerCoins_[k]);
		vector<Texture*> coinNumbTextures;

		for (int i = 0; i < coinNumb.length(); i++) { //sacamos los dígitos y los metemos en un vector
			coinNumbTextures.push_back(SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::Zero + coinNumb[i] - '0'));
		}

		SDL_Rect coinImageRect;
		coinImageRect.x = (k % 2 == 0) ? coinUIMarginX_ : winWidth_ - coinUIMarginX_ - coinUIRadius_;
		coinImageRect.y = (k < 2) ? coinUIMarginY_ : winHeigth_ - coinUIMarginY_ - coinUIRadius_;
		coinImageRect.w = coinUIRadius_;
		coinImageRect.h = coinUIRadius_;

		coinTextureUI_->render(coinImageRect);

		for (int i = 0; i < coinNumbTextures.size(); i++) {
			SDL_Rect coinTextRect;
			coinTextRect.w = coinNumbTextures[i]->getWidth() * coinUISpriteScale_;
			coinTextRect.h = coinNumbTextures[i]->getHeight() * coinUISpriteScale_;
			coinTextRect.x = (k % 2 == 0) ? (coinImageRect.x + coinImageRect.w / 3 + i * coinTextRect.w) + coinUIRadius_ :
				(coinImageRect.x + coinImageRect.w / 3 + i * coinTextRect.w) - coinUIRadius_ * coinNumbTextures.size()/1.5;
			coinTextRect.y = coinImageRect.y + coinUIRadius_ * 0.3;

			coinNumbTextures[i]->render(coinTextRect);
		}
	}
}

void CapitalismGameMode::createCoin(b2Vec2 spawnPos, int player, int val) {
	coinPool_.addCoin(spawnPos, player, val);
}