#pragma once
#include <b2_world_callbacks.h>
#include <b2_contact.h>
#include "Pickable.h"

class PickObjectListener : public b2ContactListener
{
    virtual void BeginContact(b2Contact* contact) {

        Pickable* pickableObj = nullptr;
        b2Body* playerB = nullptr;
        if (contactPickableObjectAndPlayer(contact, pickableObj, playerB))
            pickableObj->SavePlayerInfo(int(playerB->GetUserData()),playerB);
    }

    virtual void EndContact(b2Contact* contact) {

        Pickable* pickableObj = nullptr;
        b2Body* playerB = nullptr;
        if (contactPickableObjectAndPlayer(contact, pickableObj, playerB))
            pickableObj->DeletePlayerInfo(int(playerB->GetUserData()));
    }
    bool contactPickableObjectAndPlayer(b2Contact* contact, Pickable*& pickableObj, b2Body*& playerB);
};

