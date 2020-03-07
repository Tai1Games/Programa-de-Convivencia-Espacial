#include "Pickable.h"
#include <iostream>
#include "InputHandler.h"

void Pickable::init()
{
	ih_ = SDL_Game::instance()->getInputHandler();
	mainCollider_ = GETCMP1_(Collider);
	//Fixture Sensor añadido por el componente
	mainCollider_->createFixture(100, 100, 10, 0, 0, 0, true);
	//Pone la informacion de esta clase en el body, para poder usarla en el Listener
	mainCollider_->setUserData(this);
	//Tamaño del vector segun el numero de jugadores
	playerInfo.resize(ih_->getNumControllers());
}

void Pickable::update()
{

	for (int i = 0; i<playerInfo.size(); i++) {

		if (ih_->isButtonDown(i, SDL_CONTROLLER_BUTTON_Y) && playerInfo[i].isNear) {
			cout << "inRange";
			PickObjectBy(playerInfo[i].body);
		}
	}
}

void Pickable::PickObjectBy(b2Body* playerBody)
{
	if (joint_ == nullptr) {
		b2WeldJointDef jointDef;
		jointDef.bodyA = playerBody;
		jointDef.bodyB = mainCollider_->getBody();
		jointDef.collideConnected = false;
		/*mainCollider_->setTransform(b2Vec2(playerBody->GetPosition().x, playerBody->GetPosition().y),0);*/
		jointDef.localAnchorA = b2Vec2(-100, 50 / 2);
		joint_ = (b2WeldJoint*)mainCollider_->getWorld()->CreateJoint(&jointDef);
		picked_ = true;
	}
}

void Pickable::UnPickObject()
{
	if (joint_ != nullptr) {
		mainCollider_->getWorld()->DestroyJoint(joint_);
		picked_ = false;
	}
}

void Pickable::SavePlayerInfo(int index, b2Body* playerB)
{
	cout << "si";
	cout << index << endl;
	cout << playerB->GetUserData() << endl;
	playerInfo[index].isNear = true;
	playerInfo[index].body = playerB;
}

void Pickable::DeletePlayerInfo(int index)
{
	cout << "no";
	cout << index << endl;
	playerInfo[index].isNear = false;
	playerInfo[index].body = nullptr;
}
