#include "Collider.h"

Collider::Collider(b2World* world, b2BodyType type, float x, float y, float width, float height,
	float density, float friction, float restitution, CollisionLayer c, bool sensor, bool canBeAttached) :
	world_(world),
	Component(ComponentType::Collider)
{   
	bodyDef_.type = type;
	bodyDef_.position.Set(x, y);
	body_ = world_->CreateBody(&bodyDef_);
	createFixture(width, height, density, friction, restitution, c, sensor);
	createFixture(width + HITBOX_ATTACH_TO_OBJECTS_OFFSET, height + HITBOX_ATTACH_TO_OBJECTS_OFFSET, 0, 0, 0, c, sensor);
}

void Collider::createFixture(float width, float height, float density,
	float friction, float restitution, CollisionLayer c, bool sensor) {
	widths_.push_back(width);
	heights_.push_back(height);
	b2PolygonShape shape;
	shape.SetAsBox(width, height);
	shapes_.push_back(shape);
	b2FixtureDef aux;
	aux.shape = &shapes_.back();
	aux.density = density;
	aux.friction = friction;
	aux.restitution = fmod(restitution, 1.0);
	switch (c) {
	case Normal:
		aux.filter.categoryBits = Normal; //what am I?
		aux.filter.maskBits = Normal | Player; //what do I collide with?
		break;
	case Player:
		aux.filter.categoryBits = Player;
		aux.filter.maskBits = Normal | Player | Trigger;
		break;
	case Trigger:
		aux.filter.categoryBits = Trigger;
		aux.filter.maskBits = Player;
		break;
	}
	aux.isSensor = sensor;
	fixtureDefs_.push_back(aux);
	fixtures_.push_back(body_->CreateFixture(&fixtureDefs_.back()));
}

void Collider::destroyFixture(int i) {
	body_->DestroyFixture(fixtures_[i]);
	/*fixtures_.erase(fixtures_.begin() + i);
	fixtureDef_.erase(fixtureDef_.begin() + i);
	shape_.erase(shape_.begin() + i);*/
}