#pragma once
#include <b2_world_callbacks.h>
#include <b2_contact.h>
#include "Pickable.h"

class PickObjectListener : public b2ContactListener
{
private:
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
    bool contactPickableObjectAndPlayer(b2Contact* contact, Pickable*& pickableObj, b2Body*& playerB);
};

