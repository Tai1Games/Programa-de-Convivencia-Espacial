#include "CollisionHandler.h"

//Handles start of collisions
void CollisionHandler::BeginContact(b2Contact* contact)
{ 
	b2Fixture* fixA = contact->GetFixtureA();
	b2Fixture* fixB = contact->GetFixtureB();

	//player damage collision
	Health* player = nullptr;

	//check collision then do whatever, in this case twice because it might be two players colliding 
	if (ObjectCollidesWithPlayer(fixA, player)) {

		//Measure de impact of an object with the player 
		b2Vec2 force = fixB->GetBody()->GetMass() * fixB->GetBody()->GetLinearVelocity();
		int impact= force.Length();

		
		//Depending on the force of impact we apply damage to the player
		if (impact >= 35 && impact < 50) {
			player->subtractLife(1);
			std::cout << "Health: " << player->getHealth() << endl;
			cout << impact << endl;
		}

		if (impact >= 50 && impact < 65) {
			player->subtractLife(2);
			std::cout << "Health: " << player->getHealth() << endl;
			cout << impact << endl;
		}

		if (impact >= 65) {
			player->subtractLife(3);
			std::cout << "Health: " << player->getHealth() << endl;
			cout << impact << endl;
		}
	}

	if (ObjectCollidesWithPlayer(fixB, player)) {
		player->subtractLife(1);
		std::cout << "Health: " << player->getHealth() << endl;
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
	if (player = static_cast<Health*>(fixA->GetBody()->GetUserData())) return true;
	else return false;
}

//add pickable object method and grabbable object method here