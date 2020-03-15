#pragma once
#include <box2d.h>
#include <iostream>
#include "Health.h"
#include "AttachesToObjects.h"

class CollisionHandler :
	public b2ContactListener
{
private:
	struct weldData {
		AttachesToObjects* player = nullptr;
		b2Body* bodyToBeAttached = nullptr;
		b2Vec2 collPoint;
	};
	vector<weldData> vecWeld;
public:

    CollisionHandler() {};
    ~CollisionHandler() {};

    void BeginContact(b2Contact* contact);

    void EndContact(b2Contact* contact);

    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

	void SolveInteractions();

    bool ObjectCollidesWithPlayer(b2Fixture* fixA, Health*& player);

	bool AttachableObjectCollidesWithPlayer(b2Fixture* fixA, AttachesToObjects*& player);
};

