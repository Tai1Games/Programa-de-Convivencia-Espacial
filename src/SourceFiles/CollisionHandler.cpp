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
	}
}

//Handles end of collisions
void CollisionHandler::EndContact(b2Contact* contact)
{ 
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

//add pickable object method and grabbable object method here