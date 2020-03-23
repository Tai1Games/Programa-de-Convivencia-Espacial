#include "Weapon.h"
#include <iostream>
#include "InputHandler.h"
#include "Hands.h"
#include "Health.h"

void Weapon::init()
{
	ih_ = SDL_Game::instance()->getInputHandler();
	mainCollider_ = GETCMP1_(Collider);
	vw_ = GETCMP1_(Viewer);
	//Fixture Sensor a�adido por el componente
	mainCollider_->createFixture(mainCollider_->getW(0)*4, mainCollider_->getH(0)*4, 1, 0.1, 0, Collider::CollisionLayer::Weapon, true);
	//Pone la informacion de esta clase en el body, para poder usarla en el Listener
	//Tama�o del vector segun el numero de jugadores
	playerInfo_.resize(ih_->getNumControllers());
}

void Weapon::update()
{
	
	
}

void Weapon::handleInput()
{
	if (currentHand_ == nullptr) {
		for (int i = 0; i < playerInfo_.size(); i++) {

			if (!IsPicked() && playerInfo_[i].isNear && ih_->isButtonJustDown(i, SDL_CONTROLLER_BUTTON_Y)) {
				cout << "inRange";
				PickObjectBy(playerInfo_[i].playerHands);
			}
		}
	}
	else if (IsPicked() && ih_->isButtonJustDown(currentHand_->getPlayerId(), SDL_CONTROLLER_BUTTON_Y))
	{
		UnPickObject();
	}

	else if (IsPicked() && ih_->isButtonDown(currentHand_->getPlayerId(), SDL_CONTROLLER_BUTTON_X))
	{
		Action();
	}
}

void Weapon::PickObjectBy(Hands* playerH)
{
	if (playerH->getWeapon() == NoWeapon) {
		currentHand_ = playerH;
		picked_ = true;
		currentHand_->setWeapon(weaponType_);
		mainCollider_->getBody()->SetEnabled(false);
		vw_->setDrawable(false);
	}
}

void Weapon::UnPickObject()
{
	currentHand_->setWeapon(NoWeapon);
	picked_ = false;
	mainCollider_->getBody()->SetEnabled(true);
	vw_->setDrawable(true);
	mainCollider_->setLinearVelocity(b2Vec2(0, 0));
	mainCollider_->setTransform(b2Vec2(currentHand_->getPos().x, currentHand_->getPos().y), currentHand_->getAngle());
	mainCollider_->applyLinearImpulse(b2Vec2(currentHand_->getDir().x * WEAPON_THROW_SPEED, -currentHand_->getDir().y * WEAPON_THROW_SPEED), mainCollider_->getBody()->GetLocalCenter());
	mainCollider_->getBody()->SetAngularVelocity(WEAPON_SPIN_SPEED);
	currentHand_ = nullptr;
}

void Weapon::SavePlayerInfo(int index, Hands* playerH)
{
	playerInfo_[index].isNear = true;
	playerInfo_[index].playerHands = playerH;
}

void Weapon::DeletePlayerInfo(int index)
{
	playerInfo_[index].isNear = false;
	playerInfo_[index].playerHands = nullptr;
}


void Weapon::Action() {
	cout << "Zasca ";
	/*Entity* aux = entity_;

	Health* he = aux->getComponent<Health>(ComponentType::Health);
	//Calculo del daño de la chancla
	int damage = he->getHealthMax() - he->getHealth() + 1;

	cout << "Fuiste golpeado con " << damage << " al contrincante" << endl;
	*/
}