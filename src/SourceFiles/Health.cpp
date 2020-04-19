#include "Health.h"
#include <iostream>
#include "Collider.h"
#include "Collision.h"
#include "Weapon.h"
#include "AttachesToObjects.h"
#include "CollisionHandler.h"

Health::Health(int l) : Component(ComponentType::Health)
{
	lives_ = livesMax_ = l;
	INV_FRAMES_HIT = CONST(int, "INVULNERABILITY_FRAMES_HIT");;
	INV_FRAMES_RESPAWN = CONST(int, "INVULNERABILITY_FRAMES_RESPAWN");
	invFrames_ = -1;
}

void Health::init() {
	//col_ = GETCMP1_(Collider);
	//col_->setUserData(this);
}

void Health::update()
{
	if (invFrames_ >= 0) {
		invFrames_--;
		cout << invFrames_ << "\n";
	}
}

	Health::~Health()
	{
	}

	bool Health::subtractLife(int damage)
	{
		if (invFrames_ < 0) {
			if (lives_ > 0) {

				if (damage != 0)invFrames_ = INV_FRAMES_HIT;
				lives_ -= damage;
				if (lives_ <= 0) {
					lives_ = 0;
					return false;
				}	//Evitar vidas negativas
				return true;
			}
			else return false;
		}else return true;
	}

	void Health::addLife(int sum)
	{
		if (lives_ + sum > livesMax_) lives_ = livesMax_;
		else lives_ += sum;
	}

	void Health::playerDead(Collision * c)
	{
			//reset player

			//soltar objetos agarrados
			AttachesToObjects* a = GETCMP1_(AttachesToObjects);
			if (a != nullptr && a->isAttached())
				c->collisionHandler->breakAttachment(a);
			//soltar arma
			Hands* h = GETCMP1_(Hands);
			Weapon* w = nullptr;
			if (h != nullptr) w = h->getWeapon();
			if (w != nullptr) c->collisionHandler->dropWeapon(w);
			//respawn
			GameMode* s = c->collisionHandler->getGamemode();
			PlayerData* p = GETCMP1_(PlayerData);
			CollisionHandler::moveData mov;
			mov.body = GETCMP1_(Collider)->getFixture(0)->GetBody();
			mov.pos = c->collisionHandler->getPlayerRespawnPoint(p->getPlayerNumber());
			if (s->onPlayerDead(p->getPlayerNumber())) {	//avisa al jugador si puede respawnear
				resetHealth();
				invFrames_ = INV_FRAMES_RESPAWN;
			}
			else {	//si no le quedan vidas le mandamos lejos provisionalmente
				mov.pos = b2Vec2((1 + p->getPlayerNumber()) * 50, 0);
			}
			c->collisionHandler->addMove(mov);

			//cuerpo muerto
			CollisionHandler::bodyData body;
			b2Fixture* fix = GETCMP1_(Collider)->getFixture(0);
			body.pos = fix->GetBody()->GetPosition();
			body.angle = fix->GetBody()->GetAngle();
			c->collisionHandler->addCorpse(body);
		
	}

	void Health::onCollisionEnter(Collision * c)
	{
		if (invFrames_ < 0) {	//si no es invulnerable

			b2Fixture* fix = c->hitFixture;
			if (!fix->IsSensor())
			{
				b2Vec2 force = c->hitFixture->GetBody()->GetMass() * c->hitFixture->GetBody()->GetLinearVelocity();
				int impact = force.Length();
				Weapon* w = GETCMP_FROM_FIXTURE_(fix, Weapon);
				//Si se impacta con un arma al umbral más alto de fuerza, se recibe su daño de impacto
				if (w != nullptr) {
					impact = (impact >= CONST(double, "HIGH_DAMAGE")) ? w->getImpactDamage() : 0;
				}
				else {
					//Depending on the force of impact we apply damage to the player

					if (impact < CONST(int, "LOW_DAMAGE")) impact = 0;

					else if (impact >= CONST(int, "LOW_DAMAGE") && impact < CONST(double, "MEDIUM_DAMAGE")) impact = 1;

					else if (impact >= CONST(double, "MEDIUM_DAMAGE") && impact < CONST(double, "HIGH_DAMAGE")) impact = 2;

					else if (impact >= CONST(double, "HIGH_DAMAGE")) /*&& impact < CONST(double, "HIGH_DAMAGE"))*/ impact = 3;
				}

				if (!subtractLife(impact))
					playerDead(c);

			}
		}
	}
