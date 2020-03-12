#include "CollisionHandler.h"

//Handles start of collisions
void CollisionHandler::BeginContact(b2Contact* contact)
{ 
	

	//Pickable weapon collisions
	Weapon* pickableObj = nullptr;
	Hands* playerHands = nullptr;
	b2Body* playerBody = nullptr;
	if (PlayerCanPickWeapon(contact, pickableObj, playerHands, playerBody)) {
		cout << "jaja si" << endl;
		pickableObj->SavePlayerInfo(playerHands->getPlayerId(), playerBody);
	}
	else {
		b2Fixture* fixA = contact->GetFixtureA();
		b2Fixture* fixB = contact->GetFixtureB();

		//player damage collision
		Health* player = nullptr;

		//check collision then do whatever, in this case twice because it might be two players colliding 
		if (ObjectCollidesWithPlayer(fixA, player)) {
			player->subtractLife(1);
			std::cout << "Health: " << player->getHealth() << endl;
		}
		if (ObjectCollidesWithPlayer(fixB, player)) {
			player->subtractLife(1);
			std::cout << "Health: " << player->getHealth() << endl;
		}
	}
	/*if (contactPickableObjectAndPlayer(contact, pickableObj, playerB))
		pickableObj->SavePlayerInfo(int(playerB->GetUserData()), playerB);*/
}

//Handles end of collisions
void CollisionHandler::EndContact(b2Contact* contact)
{ 
	//Pickable weapons
	/*Weapon* pickableObj = nullptr;
	Hands* player = nullptr;
	if (PlayerCanPickWeapon(contact, pickableObj, player))
		pickableObj->DeletePlayerInfo(player->getId());*/
}

//If you want to disable a collision after it's detected
void CollisionHandler::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
}

//Gather info about impulses
void CollisionHandler::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
}

//to add a new collision behaviour, make a method that checks if it's the specific collision you want
//you can distinguish bodies by their user data or make them collide with certain objects only with collision layers
//if you need to use a component you have to do collider->setUserData(this) in the component's init first
bool CollisionHandler::ObjectCollidesWithPlayer(b2Fixture* fixA, Health* &player)
{	
	Entity* fixAEnt = static_cast<Entity*>(fixA->GetBody()->GetUserData());
	if ((fixAEnt->hasComponent(ComponentType::Health)) &&
		(player = static_cast<Health*>(fixAEnt->getComponent<Health>(ComponentType::Health)))) return true;
	else return false;
}

bool CollisionHandler::PlayerCanPickWeapon(b2Contact* contact, Weapon* &pickableObj, Hands* &player, b2Body* &playerBody) {
	Entity* fixAentity = static_cast<Entity*>(contact->GetFixtureA()->GetBody()->GetUserData());
	Entity* fixBentity = static_cast<Entity*>(contact->GetFixtureB()->GetBody()->GetUserData());

	if ((fixAentity->hasComponent(ComponentType::Weapon)) && 
		(pickableObj = static_cast<Weapon*>(fixAentity->getComponent<Weapon>(ComponentType::Weapon)))) {
		player = static_cast<Hands*>(fixBentity->getComponent<Hands>(ComponentType::Hands));
		Collider* col = static_cast<Collider*>(fixBentity->getComponent<Collider>(ComponentType::Collider));
		playerBody = col->getBody();
		return true;
	}
	else if ((fixBentity->hasComponent(ComponentType::Weapon)) &&
		(pickableObj = static_cast<Weapon*>(fixBentity->getComponent<Weapon>(ComponentType::Weapon)))) {
		player = static_cast<Hands*>(fixAentity->getComponent<Hands>(ComponentType::Hands));
		Collider* col = static_cast<Collider*>(fixAentity->getComponent<Collider>(ComponentType::Collider));
		playerBody = col->getBody();
		return true;
	}
	return false;
}

//add pickable object method and grabbable object method here
/*bool CollisionHandler::contactPickableObjectAndPlayer(b2Contact* contact, Weapon*& pickableObj, b2Body*& playerB)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	//Asegurarse de que solo uno de los dos es sensor
	if (fixtureA->IsSensor() && !fixtureB->IsSensor()) {
		pickableObj = static_cast<Weapon*>(fixtureA->GetBody()->GetUserData());
		//Nos aseguramos de que es un jugador
		int id = int(fixtureB->GetBody()->GetUserData());
		//Suponiendo de 1 a 4 jugadores
		if (id >= 0 && id <= 3)
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

}*/