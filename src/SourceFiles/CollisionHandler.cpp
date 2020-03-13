#include "CollisionHandler.h"

//Handles start of collisions
void CollisionHandler::BeginContact(b2Contact* contact)
{ 
	/*b2Fixture* fixA = contact->GetFixtureA();
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
	}*/

	//Pickable weapon collisions
	Weapon* pickableObj = nullptr;
	Hands* playerHands = nullptr;
	if ((contact->GetFixtureA()->GetFilterData().categoryBits == Collider::CollisionLayer::Weapon ||
		contact->GetFixtureB()->GetFilterData().categoryBits == Collider::CollisionLayer::Weapon) &&
		PlayerCanPickWeapon(contact, pickableObj, playerHands)) {
		cout << "jaja si" << endl;
		pickableObj->SavePlayerInfo(playerHands->getPlayerId(), playerHands);
	}
}

//Handles end of collisions
void CollisionHandler::EndContact(b2Contact* contact)
{ 
	//Pickable weapons
	Weapon* pickableObj = nullptr;
	Hands* playerHands = nullptr;
	b2Body* playerB = nullptr;
	if ((contact->GetFixtureA()->GetFilterData().categoryBits == Collider::CollisionLayer::Weapon ||
		contact->GetFixtureB()->GetFilterData().categoryBits == Collider::CollisionLayer::Weapon) &&
		PlayerCanPickWeapon(contact, pickableObj, playerHands)) {
		pickableObj->DeletePlayerInfo(playerHands->getPlayerId());
		cout << "jaja no" << endl;
	}
		
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

bool CollisionHandler::PlayerCanPickWeapon(b2Contact* contact, Weapon* &pickableObj, Hands* &player) {
	Entity* fixAentity = static_cast<Entity*>(contact->GetFixtureA()->GetBody()->GetUserData());
	Entity* fixBentity = static_cast<Entity*>(contact->GetFixtureB()->GetBody()->GetUserData());

	if ((fixAentity->hasComponent(ComponentType::Weapon)) && 
		(pickableObj = static_cast<Weapon*>(fixAentity->getComponent<Weapon>(ComponentType::Weapon))) &&
		fixBentity->hasComponent(ComponentType::Hands)) {

		player = static_cast<Hands*>(fixBentity->getComponent<Hands>(ComponentType::Hands));
		return true;
	}
	else if ((fixBentity->hasComponent(ComponentType::Weapon)) &&
		(pickableObj = static_cast<Weapon*>(fixBentity->getComponent<Weapon>(ComponentType::Weapon))) &&
		fixAentity->hasComponent(ComponentType::Hands)){

		player = static_cast<Hands*>(fixAentity->getComponent<Hands>(ComponentType::Hands));
		return true;
	}
	return false;
}

//add  grabbable object method here