#include "Weapon.h"
#include <iostream>
#include "InputHandler.h"
#include "Hands.h"

void Weapon::init()
{
	ih_ = SDL_Game::instance()->getInputHandler();
	mainCollider_ = GETCMP1_(Collider);
	vw_ = GETCMP1_(Viewer);
	//Fixture Sensor a�adido por el componente
	mainCollider_->createFixture(mainCollider_->getW(0)*4, mainCollider_->getH(0), 1, 0.1, 0, Collider::CollisionLayer::Weapon, true);
	//Pone la informacion de esta clase en el body, para poder usarla en el Listener
	//Tama�o del vector segun el numero de jugadores
	playerInfo_.resize(ih_->getNumControllers());
}

void Weapon::update()
{

	for (int i = 0; i<playerInfo_.size(); i++) {

		if (ih_->isButtonDown(i, SDL_CONTROLLER_BUTTON_Y) && playerInfo_[i].isNear && !IsPicked()) {
			cout << "inRange";
			PickObjectBy(playerInfo_[i].playerHands);
		}
	}
}

void Weapon::PickObjectBy(Hands* playerH)
{
	picked_ = true;
	playerH->setWeapon(weaponType_);
	mainCollider_->getBody()->SetEnabled(false);
	vw_->setDrawable(false);
}

void Weapon::UnPickObject()
{
	if (joint_ != nullptr) {
		mainCollider_->getWorld()->DestroyJoint(joint_);
		picked_ = false;
	}
}

void Weapon::SavePlayerInfo(int index, Hands* playerH)
{
	playerInfo_[index].isNear = true;
	playerInfo_[index].playerHands = playerH;
}

void Weapon::DeletePlayerInfo(int index)
{
	//cout << index << endl;
	playerInfo_[index].isNear = false;
	playerInfo_[index].playerHands = nullptr;
}
