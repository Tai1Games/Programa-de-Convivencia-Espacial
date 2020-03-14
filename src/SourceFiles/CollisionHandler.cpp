#include "CollisionHandler.h"

//Handles start of collisions
void CollisionHandler::BeginContact(b2Contact* contact)
{ 
	b2Fixture* fixA = contact->GetFixtureA();
	b2Fixture* fixB = contact->GetFixtureB();
	//player damage collision
	//Health* player_Health = nullptr;
	AttachesToObjects* player_AttachesToObjects = nullptr;
	
	//check collision then do whatever, in this case twice because it might be two players colliding 
	/*if (ObjectCollidesWithPlayer(fixA, player_Health)) {
		player_Health->subtractLife(1);
		std::cout << "Health: " << player_Health->getHealth() << endl;
	}
	if (ObjectCollidesWithPlayer(fixB, player_Health)) {
		player_Health->subtractLife(1);
		std::cout << "Health: " << player_Health->getHealth() << endl;
	}*/
	if (AttachableObjectCollidesWithPlayer(fixA, player_AttachesToObjects)) {
		b2WorldManifold manifold;
		contact->GetWorldManifold(&manifold);
		if (player_AttachesToObjects->isPressingInput()) player_AttachesToObjects->registerCollision(fixB->GetBody(), b2Vec2(manifold.points[0].x , manifold.points[0].y));
		//if (player_AttachesToObjects->isPressingInput()) player_AttachesToObjects->registerCollision(fixB->GetBody(), b2Vec2((manifold.points[0].x + manifold.points[1].x) / 2, (manifold.points[0].y + manifold.points[1].y) / 2));
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

bool CollisionHandler::AttachableObjectCollidesWithPlayer(b2Fixture* fixA, AttachesToObjects*& player) {
	if (player = static_cast<AttachesToObjects*>(fixA->GetBody()->GetUserData())) return true;
	else return false;
}

//add pickable object method and grabbable object method here