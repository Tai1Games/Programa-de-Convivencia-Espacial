#include "CollisionHandler.h"
//This method calculates the damage recieved by the impact of an object (or another player) with the player
void CollisionHandler::damageOnImpact(b2Fixture* fix, Health* playerHealth) {
	//Measure de impact of an object with the player 
	b2Vec2 force = fix->GetBody()->GetMass() * fix->GetBody()->GetLinearVelocity();

	int impact = force.Length();

	//Depending on the force of impact we apply damage to the player
	if (impact >= lowDamage && impact < mediumDamage) {playerHealth->subtractLife(1);}

	if (impact >= mediumDamage && impact < hightDamage) {playerHealth->subtractLife(2);}

	if (impact >= hightDamage) {playerHealth->subtractLife(3);}
}

//Handles start of collisions
void CollisionHandler::BeginContact(b2Contact* contact)
{
	b2Fixture* fixA = contact->GetFixtureA();
	b2Fixture* fixB = contact->GetFixtureB();

	//player damage collision
	Health* player = nullptr;

	//check collision then do whatever, in this case twice because it might be two players colliding 
	if (ObjectCollidesWithPlayer(fixA, player)) {
		damageOnImpact(fixB, player);	//Check the stats of the other object
	}

	player = nullptr;	//Lo reseteamos para evitar problemas

	if (ObjectCollidesWithPlayer(fixB, player)) {
		damageOnImpact(fixA, player);	//Check the stats of the other object
	//Pickable weapon collisions
	Weapon* pickableObj = nullptr;
	Hands* playerHands = nullptr;
	if ((contact->GetFixtureA()->GetFilterData().categoryBits == Collider::CollisionLayer::Weapon ||
		contact->GetFixtureB()->GetFilterData().categoryBits == Collider::CollisionLayer::Weapon) &&
		PlayerCanPickWeapon(contact, pickableObj, playerHands)) {
		cout << "jaja si" << endl;
		pickableObj->SavePlayerInfo(playerHands->getPlayerId(), playerHands);
	}
	else {
		//player damage collision
		Health* playerHealth = nullptr;

		//check collision then do whatever, in this case twice because it might be two players colliding
		if (ObjectCollidesWithPlayer(fixA, playerHealth)) {
			playerHealth->subtractLife(1);
			std::cout << "Health: " << playerHealth->getHealth() << endl;
		}
		if (ObjectCollidesWithPlayer(fixB, playerHealth)) {
			playerHealth->subtractLife(1);
			std::cout << "Health: " << playerHealth->getHealth() << endl;
		}
	}	
}

//Handles end of collisions
void CollisionHandler::EndContact(b2Contact* contact)
{
	//Pickable weapons
	Weapon* pickableObj = nullptr;
	Hands* playerHands = nullptr;
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
bool CollisionHandler::ObjectCollidesWithPlayer(b2Fixture* fixA, Health*& player)
{	
	//Obtenemos los datos guardados en el Collider
	Entity* aux = static_cast<Entity*>(fixA->GetBody()->GetUserData());

	if(aux != nullptr){		//Cuidado de que no sea null

	//Cogemos el health si es que lo tiene
	player = aux->getComponent<Health>(ComponentType::Health);
	}

	if (player != nullptr) {	//Si lo tiene es que es un player
		return true;
	}
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
