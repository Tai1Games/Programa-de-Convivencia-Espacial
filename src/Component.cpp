#include "Component.h"

Component::Component(ComponentType::CmpId id) : entity_(nullptr), game_(nullptr), id_(id) //
{
}

Component::~Component() {
}

