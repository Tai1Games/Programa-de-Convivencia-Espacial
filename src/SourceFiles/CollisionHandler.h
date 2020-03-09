#pragma once
#include <box2d.h>
#include <iostream>

class CollisionHandler :
	public b2ContactListener
{
public:

    CollisionHandler() {};
    ~CollisionHandler() {};

    void BeginContact(b2Contact* contact);

    void EndContact(b2Contact* contact);

    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

    bool TriggerCollision(b2Fixture* fixA, b2Fixture* fixB);
};

