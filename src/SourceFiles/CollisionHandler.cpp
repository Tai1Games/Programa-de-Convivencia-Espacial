#include "CollisionHandler.h"

void CollisionHandler::BeginContact(b2Contact* contact)
{ 
	b2Fixture* fixA = contact->GetFixtureA();
	b2Fixture* fixB = contact->GetFixtureB();

	std::cout << "jajasi\n";

	TriggerCollision(fixA, fixB);
}

void CollisionHandler::EndContact(b2Contact* contact)
{ /* handle end event */
}

void CollisionHandler::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{ /* handle pre-solve event */
}

void CollisionHandler::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{ /* handle post-solve event */
}

bool CollisionHandler::TriggerCollision(b2Fixture* fixA, b2Fixture* fixB) {
	bool a = (fixA->IsSensor() || fixB->IsSensor());
	if(a) std::cout << "trigger\n";
	return a;
	
}