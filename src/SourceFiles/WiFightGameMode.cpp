#include "WiFightGameMode.h"
#include "Resources.h"
#include "ParticleEmitter.h"
#include "RouterLogic.h"

void WiFightGameMode::init(PlayState* game)
{
	GameMode::init(game);
	playerProgress_.reserve(nPlayers_);
	for (int k = 0; k < nPlayers_; k++) {
		players_.push_back(PlayerFactory::createPlayerWithHealth(game->getEntityManager(), game->getPhysicsWorld(), k,
			Resources::Body, tilemap_->getPlayerSpawnPoint(k).x, tilemap_->getPlayerSpawnPoint(k).y, 3));
		playerProgress_.push_back(0);
	}

	router = state_->getEntityManager()->addEntity();
																								  //				x,								y,						width, height, density,	friction, restitution, linearDrag, angularDrag,	 Laye,  sensor,  canBeAttached
	Collider* collRouter = router->addComponent<Collider>(state_->getPhysicsWorld(), b2_dynamicBody, tilemap_->getObjSpecialSpawnPos().x, tilemap_->getObjSpecialSpawnPos().y, 1, 0.7, 1, 0, 1, 0, 0, Collider::CollisionLayer::UnInteractableObject, false);
	collRouter->createCircularFixture(5, 1, 0, 0, Collider::CollisionLayer::Trigger, true);
	router->addComponent<Viewer>(Resources::Router);
	router->addComponent<RouterLogic>(this);
	//(Vector2D direction, int textureId, float speed, int numTextures = 1, int particleGenerationOdds = 5, Uint16 particleLifetime = 1000, Uint16 size = 20, Uint16 emittingTime = 1000, int speedVariation = 0, int emissionConeAngle = 10.0);
	//router->addComponent<ParticleEmitter>(Vector2D(), Resources::TextureId::WiFiWave, Vector2D(), 1, );

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
