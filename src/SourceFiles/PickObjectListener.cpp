#include "PickObjectListener.h"

void PickObjectListener::BeginContact(b2Contact* contact)
{
	Weapon* pickableObj = nullptr;
	b2Body* playerB = nullptr;
	if (contactPickableObjectAndPlayer(contact, pickableObj, playerB))
		pickableObj->SavePlayerInfo(int(playerB->GetUserData()), playerB);
}

void PickObjectListener::EndContact(b2Contact* contact)
{
	Weapon* pickableObj = nullptr;
	b2Body* playerB = nullptr;
	if (contactPickableObjectAndPlayer(contact, pickableObj, playerB))
		pickableObj->DeletePlayerInfo(int(playerB->GetUserData()));
}

bool PickObjectListener::contactPickableObjectAndPlayer(b2Contact* contact, Weapon*& pickableObj, b2Body*& playerB)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	//Asegurarse de que solo uno de los dos es sensor
	if (fixtureA->IsSensor() && !fixtureB->IsSensor()) {
		pickableObj = static_cast<Weapon*>(fixtureA->GetBody()->GetUserData());
		//Nos aseguramos de que es un jugador
		int id = int(fixtureB->GetBody()->GetUserData());
		//Suponiendo de 1 a 4 jugadores
		if(id>=0 && id<=3)
		playerB = fixtureB->GetBody();
		return (pickableObj != nullptr && playerB != nullptr);
	}
	else if (!fixtureA->IsSensor() && fixtureB->IsSensor()) {
		pickableObj = static_cast<Weapon*>(fixtureB->GetBody()->GetUserData());
		//Nos aseguramos de que es un jugador
		int id = int(fixtureA->GetBody()->GetUserData());
		//Suponiendo de 1 a 4 jugadores
		if (id >= 0 && id <= 3)
		playerB = fixtureA->GetBody();
		return (pickableObj != nullptr && playerB != nullptr);
	}
	else return false;

}
