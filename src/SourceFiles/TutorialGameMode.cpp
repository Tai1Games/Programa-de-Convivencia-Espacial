#include "TutorialGameMode.h"
#include "Constants.h"
#include "PlayState.h"
#include "ActionableWeapon.h"


TutorialGameMode::TutorialGameMode(int nPlayers, int stocks) : GameMode(nPlayers)
{
	maxStocks_ = stocks;
}

TutorialGameMode::~TutorialGameMode()
{
}

void TutorialGameMode::init(PlayState* game) {
	GameMode::init(game);

	//------------------
	for (int i = 0; i < nPlayers_; i++) {
		players_.push_back(PlayerFactory::createPlayerWithHealth(game->getEntityManager(), game->getPhysicsWorld(), i,
			Resources::Body, tilemap_->getPlayerSpawnPoint(i).x, tilemap_->getPlayerSpawnPoint(i).y, 3));
		playerStocks_.push_back(maxStocks_); //Initializes maxStocks vector with 3 on all positions.
		//tutorial weapons
		weapons_.push_back(ObjectFactory::makeExtinguisher(game->getEntityManager(), game->getPhysicsWorld(),
			b2Vec2(10 + i, 10 + i), b2Vec2(1.25, 1.25)));
		weapons_.back()->getComponent<Collider>(ComponentType::Collider)->changeLayerCollision(0, -Collider::CollisionLayer::Player);
		weapons_.back()->setActive(false);
	}
	for (int i = 0; i < players_.size(); i++) {
		Entity* e = players_[i];
		playersHealth_.push_back(e->getComponent<Health>(ComponentType::Health)); //Initializes playersHealth vector catching a reference to Health on entity e.
		HealthViewer* hV = (e->getComponent<HealthViewer>(ComponentType::HealthViewer)); //Obtains a reference to the HealthViewer component of entity e. This is used to calculate where the stocks will be drawn
		inputBinders_.push_back(e->getComponent<PlayerData>(ComponentType::PlayerData)->getBinder());
		b2Vec2 p = hV->getPos();
		if (i % 2 == 0) { //Players 1 & 3 will be drawn on the left side of the screen. Players 2 & 4 will be drawn on the right.
			p.x += hV->getWidth() + CONST(int, "STOCK_INITIAL_OFFSET");
		}
		else {
			p.x -= ((hV->getWidth() - CONST(int, "LIFE_WIDTH")) + CONST(int, "STOCK_INITIAL_OFFSET") + CONST(int, "STOCK_WIDTH"));
		}
		playersStocksPos_.push_back(p);
		for (int j = 0; j < Resources::TutorialEnd - Resources::MoveTutorial; j++) tutorials_[j].push_back(false);
	}
	//tutorial texts
	for (int i = Resources::MoveTutorial; i < Resources::TutorialEnd + 1; i++) {
		tutorialTexts_.push_back(game->getEntityManager()->addEntity());
		tutorialTexts_.back()->addComponent<Viewer>(i, b2Vec2(xOffset_, yOffset_), scale_, 0);
		tutorialTexts_.back()->setActive(false);
	}
	tutorialTexts_[0]->setActive(true);
	//progress texts
	//completed + /
	completed_ = game->getEntityManager()->addEntity();
	completed_->addComponent<Viewer>(Resources::Completed, b2Vec2(xOffsetProgressText_, yOffsetProgress_), scale_, 0);
	slash_ = game->getEntityManager()->addEntity();
	slash_->addComponent<Viewer>(Resources::Slash, b2Vec2(xOffsetProgressSlash_, yOffsetProgress_), scale_, 0);
	//zero to number of players
	for (int i = Resources::Zero; i < Resources::One + players_.size(); i++) {
		numberTexts_.push_back(game->getEntityManager()->addEntity());
		numberTexts_.back()->addComponent<Viewer>(i, b2Vec2(xOffsetProgressCount_, yOffsetProgress_), scale_, 0);
		numberTexts_.back()->setActive(false);
	}
	numberTexts_[0]->setActive(true);
	//number of players
	numPlayers_ = game->getEntityManager()->addEntity();
	numPlayers_->addComponent<Viewer>(Resources::Zero + players_.size(), b2Vec2(xOffsetProgressMax_, yOffsetProgress_), scale_, 0);
}

void TutorialGameMode::update() {
	if (tutorialPointer_ < Resources::TutorialEnd - Resources::MoveTutorial) {
		InputHandler* ih = SDL_Game::instance()->getInputHandler();
		//check if current tutorial is complete and if so, advance to next
		int progress = 0;
		bool complete = true;
		for (int i = 0; i < players_.size(); i++) {
			if (tutorials_[tutorialPointer_][i]) progress++;
			else complete = false;
		}
		if (complete) {
			tutorialTexts_[tutorialPointer_]->setActive(false); //hide old text
			tutorialPointer_++;									//advance tutorial
			tutorialTexts_[tutorialPointer_]->setActive(true); // show new text
			numberTexts_[previousProgress_]->setActive(false);
			numberTexts_[0]->setActive(true);					//reset progress
			if (tutorialPointer_ == 2) for (Entity* e : weapons_) {
				e->setActive(true); //activate weapons
				e->getComponent<Collider>(ComponentType::Collider)->changeLayerCollision(0, Collider::CollisionLayer::Player);
			}
		}
		else if (progress != previousProgress_) {	//update progress if changed
			numberTexts_[previousProgress_]->setActive(false);
			numberTexts_[progress]->setActive(true);
			previousProgress_ = progress;
		}
		//handle current tutorial
		switch (tutorialPointer_) {
		case 0: //move tutorial
			for (int i = 0; i < players_.size(); i++) if (inputBinders_[i]->releaseImpulse()) tutorials_[tutorialPointer_][i] = true;
			break;
		case 1: //hold tutorial
			for (int i = 0; i < players_.size(); i++) tutorials_[tutorialPointer_][i] = players_[i]->getComponent<AttachesToObjects>(ComponentType::AttachesToObjects)->isAttached();
			break;
		case 2: //grab tutorial
			for (int i = 0; i < players_.size(); i++) tutorials_[tutorialPointer_][i] = (players_[i]->getComponent<Hands>(ComponentType::Hands)->getWeaponID() != NoWeapon);
			break;
		case 3: //action tutorial
			for (int i = 0; i < players_.size(); i++) if (inputBinders_[i]->pressAttack()) tutorials_[tutorialPointer_][i] = true;
			break;
		case 4: //throw tutorial
			for (int i = 0; i < players_.size(); i++) if (inputBinders_[i]->pressThrow()) tutorials_[tutorialPointer_][i] = true;
			break;
		case 5: //death tutorial
			for (int i = 0; i < players_.size(); i++) tutorials_[tutorialPointer_][i] = (playerStocks_[i] < maxStocks_);
			break;
		default:
			break;
		}
	}
	else {
		completed_->setActive(false);
		slash_->setActive(false);
		numPlayers_->setActive(false);
		numberTexts_[0]->setActive(false);
	}
}

void TutorialGameMode::render() {
	SDL_Rect drawPos; //Position where the stocks will be drawn
	drawPos.w = CONST(int, "STOCK_WIDTH");
	drawPos.h = CONST(int, "STOCK_HEIGTH");
	for (int i = 0; i < playerStocks_.size(); ++i) { //i = player number, j = individual stock to be drawn
		drawPos.y = playersStocksPos_[i].y; //Stocks and Health are drawn on the same Y coordinate.
		for (int j = 0; j < playerStocks_[i]; j++) {
			if (i % 2 == 0) //X coordinate depends on whether the stocks are drawn on the left or the right. 
				drawPos.x = playersStocksPos_[i].x + j * (CONST(int, "STOCK_WIDTH") + CONST(int, "STOCK_OFFSET"));
			else
				drawPos.x = playersStocksPos_[i].x - j * (CONST(int, "STOCK_WIDTH") + CONST(int, "STOCK_OFFSET"));
			SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::Tinky)->render(drawPos);
		}
	}
}

bool TutorialGameMode::onPlayerDead(int id) { //Returns false when player runs out of stocks
	if (id < playerStocks_.size()) {
		playerStocks_[id]--;
		if (playerStocks_[id] <= 0) {
			roundResults_.push_back(players_[id]);
			if (roundResults_.size() == playerStocks_.size() - 1) {
				//int k = 0;
				//while (playerStocks_[k] == 0) { k++; }
				//roundResults_.push_back(players_[k]);
				//winner_ = players_[k];
				//roundFinished_ = true; //Round finishes when only 1 player remains
			}
			return false;
		}
		else return true;
	}
	else return true;
}