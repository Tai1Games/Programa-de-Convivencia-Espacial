#include "WiFightGameMode.h"
#include "Resources.h"

void WiFightGameMode::init(PlayState* game)
{
	GameMode::init(game);
	playerProgress_.reserve(players_.size());
	for (int k = 0; k < players_.size(); k++) {
		playerProgress_.push_back(0);
	}

	router = state_->getEntityManager()->addEntity();
																								  //				x,								y,						width, height, density,	friction, restitution, linearDrag, angularDrag,	 Laye,  sensor,  canBeAttached
	Collider* collRouter = router->addComponent<Collider>(state_->getPhysicsWorld(), b2_dynamicBody, tilemap_->getObjSpecialSpawnPos().x, tilemap_->getObjSpecialSpawnPos().y, 1, 0.7, 1, 0, 1, 0, 0, Collider::CollisionLayer::UnInteractableObject, false);
	collRouter->createCircularFixture(5, 1, 0, 0, Collider::CollisionLayer::Trigger, true);
	collRouter->setUserData(router);
	router->addComponent<Viewer>(Resources::Router);
	router->addComponent<RouterLogic>(this);

	collRouter->applyLinearImpulse(b2Vec2(100,100), b2Vec2(0, 0));

	GameMode::initProgressBars();
}

void WiFightGameMode::render()
{
	GameMode::renderProgressBars(playerProgress_, CONST(double, "POINTS_TO_WIN"));

	if (roundFinished_) {
		string winMsg = "Gana el jugador " + to_string(winner_->getComponent<PlayerData>(ComponentType::PlayerData)->getPlayerNumber()+1);
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
			winner_ = players_[player];
			roundFinished_ = true;
		}
	}
}
