#include "PickObjectListener.h"

bool PickObjectListener::contactPickableObjectAndPlayer(b2Contact* contact, Pickable*& pickableObj, b2Body*& playerB)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	//Asegurarse de que solo uno de los dos es sensor
	if (fixtureA->IsSensor() && !fixtureB->IsSensor()) {
		pickableObj = static_cast<Pickable*>(fixtureA->GetBody()->GetUserData());
		//Nos aseguramos de que es un jugador
		int id = int(fixtureB->GetBody()->GetUserData());
		//Suponiendo de 1 a 4 jugadores
		if(id>=0 && id<=3)
		playerB = fixtureB->GetBody();
		return (pickableObj != nullptr && playerB != nullptr);
	}
	else if (!fixtureA->IsSensor() && fixtureB->IsSensor()) {
		pickableObj = static_cast<Pickable*>(fixtureB->GetBody()->GetUserData());
		//Nos aseguramos de que es un jugador
		int id = int(fixtureA->GetBody()->GetUserData());
		//Suponiendo de 1 a 4 jugadores
		if (id >= 0 && id <= 3)
		playerB = fixtureA->GetBody();
		return (pickableObj != nullptr && playerB != nullptr);
	}
	else return false;

}
