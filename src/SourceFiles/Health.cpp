#include "Health.h"
#include <iostream>
#include "Collider.h"
#include "Collision.h"
#include "Weapon.h"
#include "AttachesToObjects.h"
#include "CollisionHandler.h"
#include "ThrownByPlayer.h"

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

		b2Vec2 force = c->hitFixture->GetBody()->GetMass() * c->hitFixture->GetBody()->GetLinearVelocity();
		int impact = force.Length();
		Weapon* w = GETCMP_FROM_FIXTURE_(fix, Weapon);
		ThrownByPlayer* objThrown = nullptr;
		PlayerData* playerWhoHitMe = nullptr;
		//Si se impacta con un arma al umbral mï¿½s alto de fuerza, se recibe su daÃ±o de impacto
		if (w != nullptr) {
			impact = (impact >= CONST(double, "HIGH_DAMAGE")) ? w->getImpactDamage() : 0;
			objThrown = GETCMP_FROM_FIXTURE_(fix, ThrownByPlayer);
		}
		else {
			//Depending on the force of impact we apply damage to the player


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

			else if (impact >= CONST(double, "HIGH_DAMAGE")) impact = 3;

			// we get the Id of the player who hit me at high speed
			// (it may not exist, so we check later that it's not nullptr
			playerWhoHitMe = GETCMP_FROM_FIXTURE_(fix, PlayerData);
		}

		if (!subtractLife(impact)) {
			// player is killed by a weapon
			if (objThrown != nullptr) objThrown->addPointsToOwner();

			// player is killed by another player at high speed
			else if (playerWhoHitMe != nullptr) {
				GameMode* s = c->collisionHandler->getGamemode();
				s->playerKillsPlayer(playerWhoHitMe->getPlayerNumber());
			}

			playerDead(c);

		}
	}
