#include "Health.h"
#include <iostream>
#include "Collider.h"
#include "Collision.h"
#include "Weapon.h"
#include "AttachesToObjects.h"
#include "CollisionHandler.h"
#include "ThrownByPlayer.h"
#include "PlayerController.h"

Health::Health(int l) : Component(ComponentType::Health)
{
	lives_ = livesMax_ = l;
}

void Health::init() {
	//col_ = GETCMP1_(Collider);
	//col_->setUserData(this);
	INV_FRAMES_HIT_ = CONST(int, "INVULNERABILITY_FRAMES_HIT");
	INV_FRAMES_RESPAWN_ = CONST(int, "INVULNERABILITY_FRAMES_RESPAWN");
	invFrames_ = 0;
}

void Health::update()
{
	if (invFrames_ > 0) {
		invFrames_--;
	}
}

Health::~Health()
{
}

bool Health::subtractLife(int damage)
{
	if (invFrames_ <= 0 && damage> 0) {
		if (lives_ > 0) {
			lives_ -= damage;
			invFrames_ = INV_FRAMES_HIT_;
			if (lives_ <= 0) {
				lives_ = 0;
				return false;
			}	//Evitar vidas negativas
			return true;
		}
		else return false;
	}
	else return true;
}

void Health::addLife(int sum)
{
	if (lives_ + sum > livesMax_) lives_ = livesMax_;
	else lives_ += sum;
}

void Health::playerDead(CollisionHandler* c)
{
	//reset player

	//soltar objetos agarrados
	AttachesToObjects* a = GETCMP1_(AttachesToObjects);
	if (a != nullptr && a->isAttached())
		c->breakAttachment(a);
	//soltar arma
	Hands* h = GETCMP1_(Hands);
	Weapon* w = nullptr;
	if (h != nullptr) w = h->getWeapon();
	if (w != nullptr) c->dropWeapon(w);
	//reset impulso
	PlayerController* pc = GETCMP1_(PlayerController);
	pc->resetImpulseForce();
	//respawn
	GameMode* s = c->getGamemode();
	PlayerData* p = GETCMP1_(PlayerData);
	CollisionHandler::moveData mov;
	mov.body = GETCMP1_(Collider)->getFixture(0)->GetBody();
	mov.pos = c->getPlayerRespawnPoint(p->getPlayerNumber());
	if (s->onPlayerDead(p->getPlayerNumber())) {	//avisa al jugador si puede respawnear
		resetHealth();
		invFrames_ = INV_FRAMES_RESPAWN_;
	}
	else {	//si no le quedan vidas le mandamos lejos provisionalmente
		mov.pos = b2Vec2((1 + p->getPlayerNumber()) * 50, 0);
	}
	c->addMove(mov);

	//cuerpo muerto
	CollisionHandler::bodyData body;
	b2Fixture* fix = GETCMP1_(Collider)->getFixture(0);
	body.pos = fix->GetBody()->GetPosition();
	body.angle = fix->GetBody()->GetAngle();
	c->addCorpse(body);
}

void Health::onCollisionEnter(Collision* c)
{
	if (invFrames_ <= 0) {

		b2Fixture* fix = c->hitFixture;
		if (!fix->IsSensor())
		{
			b2Vec2 force = c->hitFixture->GetBody()->GetMass() * c->hitFixture->GetBody()->GetLinearVelocity();
			int impact = force.Length();
			Weapon* w = GETCMP_FROM_FIXTURE_(fix, Weapon);
			ThrownByPlayer* objThrown = nullptr;
			PlayerData* playerWhoHitMe = nullptr;
			//Si se impacta con un arma al umbral m�s alto de fuerza, se recibe su daño de impacto
			if (w != nullptr) {
				impact = (impact >= CONST(double, "HIGH_DAMAGE")) ? w->getImpactDamage() : 0;
				objThrown = GETCMP_FROM_FIXTURE_(fix, ThrownByPlayer);
			}
			else {
				//Depending on the force of impact we apply damage to the player

				if (impact < CONST(int, "LOW_DAMAGE")) impact = 0;

				else if (impact >= CONST(int, "LOW_DAMAGE") && impact < CONST(double, "MEDIUM_DAMAGE")) impact = 1;

				else if (impact >= CONST(double, "MEDIUM_DAMAGE") && impact < CONST(double, "HIGH_DAMAGE")) impact = 2;

				else if (impact >= CONST(double, "HIGH_DAMAGE")) impact = 3;

				// we get the Id of the player who hit me at high speed
				// (it may not exist, so we check later that it's not nullptr
				playerWhoHitMe = GETCMP_FROM_FIXTURE_(fix, PlayerData);
			}

		if (!subtractLife(impact)) {
			// player is killed by a weapon
			if (objThrown != nullptr) {
				if(objThrown->getOwnerId() != GETCMP1_(PlayerData)->getPlayerNumber())
					objThrown->addPointsToOwner();
			}

			// player is killed by another player at high speed
			else if (playerWhoHitMe != nullptr) {
				if (playerWhoHitMe->getPlayerNumber() != GETCMP1_(PlayerData)->getPlayerNumber()) {
					GameMode* s = c->collisionHandler->getGamemode();
					s->playerKillsPlayer(playerWhoHitMe->getPlayerNumber());
				}
			}

				playerDead(c->collisionHandler);
			}
		}
	}
}
