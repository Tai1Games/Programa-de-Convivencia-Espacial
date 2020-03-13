#include "Weapon.h"
#include <iostream>
#include "InputHandler.h"

void Weapon::init()
{
	ih_ = SDL_Game::instance()->getInputHandler();
	mainCollider_ = GETCMP1_(Collider);
	vw_ = GETCMP1_(Viewer);
	//Fixture Sensor añadido por el componente
	mainCollider_->createFixture(mainCollider_->getW(0)*4, mainCollider_->getH(0), 1, 0.1, 0, Collider::CollisionLayer::Trigger, true);
	//Pone la informacion de esta clase en el body, para poder usarla en el Listener
	//Tamaño del vector segun el numero de jugadores
	playerInfo_.resize(ih_->getNumControllers());
}

void Weapon::update()
{

	for (int i = 0; i<playerInfo_.size(); i++) {

		if (ih_->isButtonDown(i, SDL_CONTROLLER_BUTTON_Y) && playerInfo_[i].isNear && !IsPicked()) {
			cout << "inRange";
			PickObjectBy(playerInfo_[i].body);
		}
	}
}

void Weapon::PickObjectBy(b2Body* playerBody)
{
	if (joint_ == nullptr) {
		//b2WeldJointDef jointDef;
		//jointDef.bodyA = playerBody;
		//jointDef.bodyB = mainCollider_->getBody();
		//jointDef.collideConnected = false;
		//mainCollider_->getBody()->SetEnabled(false);
		//mainCollider_->setTransform(b2Vec2(playerBody->GetPosition().x-mainCollider_->getW(0), playerBody->GetPosition().y + 25),0);
		//jointDef.localAnchorA = b2Vec2(0, 50 / 2);
		//jointDef.localAnchorB = b2Vec2(mainCollider_->getW(0), 10);
		//joint_ = (b2WeldJoint*)mainCollider_->getWorld()->CreateJoint(&jointDef);
		picked_ = true;
		mainCollider_->getBody()->SetEnabled(false);
		vw_->setDrawable(false);
		//mainCollider_->getBody()->SetEnabled(true);
	}
}

void Weapon::UnPickObject()
{
	if (joint_ != nullptr) {
		mainCollider_->getWorld()->DestroyJoint(joint_);
		picked_ = false;
	}
}

void Weapon::SavePlayerInfo(int index, b2Body* playerB)
{
	//cout << "si";
	//cout << index << endl;
	//cout << playerB->GetUserData() << endl;
	playerInfo_[index].isNear = true;
	playerInfo_[index].body = playerB;
}

void Weapon::DeletePlayerInfo(int index)
{
	cout << "sijaja SALIDO" << endl;
	//cout << index << endl;
	playerInfo_[index].isNear = false;
	playerInfo_[index].body = nullptr;
}
