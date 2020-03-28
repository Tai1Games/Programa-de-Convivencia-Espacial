#include "Collider.h"

Collider::Collider(b2World* world, b2BodyType type, float x, float y, float width, float height,

	float density, float friction, float restitution, float linearDrag, float angDrag, CollisionLayer c, bool sensor) :

	world_(world),
	Component(ComponentType::Collider)
{
	bodyDef_.type = type;
	bodyDef_.position.Set(x, y);
	bodyDef_.linearDamping = linearDrag;
	bodyDef_.angularDamping = angDrag;
	body_ = world_->CreateBody(&bodyDef_);

	createRectangularFixture(width, height, density, friction, restitution, c, sensor);
}

void Collider::createRectangularFixture(float width, float height, float density,
	float friction, float restitution, CollisionLayer c, bool sensor) {
	widths_.push_back(width);
	heights_.push_back(height);
	b2PolygonShape shape;
	shape.SetAsBox(width, height);
	//shapes_.push_back(shape);

	b2FixtureDef aux;
	aux.shape = &shape;
	aux.density = density;
	aux.filter = setCollisionLayer(c);
	aux.friction = friction;
	aux.restitution = fmod(restitution, 1.0);
	aux.isSensor = sensor;
	fixtureDefs_.push_back(aux);
	fixtures_.push_back(body_->CreateFixture(&fixtureDefs_.back()));
}

void Collider::createCircularFixture(float radius, float density, float friction, float restitution, CollisionLayer c, bool sensor) {
	widths_.push_back(radius);
	heights_.push_back(radius);
	b2CircleShape shape;
	shape.m_radius = radius;
	//shapes_.push_back(shape);

	b2FixtureDef aux;
	aux.shape = &shape;
	aux.density = density;
	aux.filter = setCollisionLayer(c);
	aux.friction = friction;
	aux.restitution = fmod(restitution, 1.0);
	aux.isSensor = sensor;
	fixtureDefs_.push_back(aux);
	fixtures_.push_back(body_->CreateFixture(&fixtureDefs_.back()));
}

b2Filter Collider::setCollisionLayer(CollisionLayer c) {
	b2Filter filter;
	switch (c) {
	case NormalObject:
		filter.categoryBits = NormalObject;
		filter.maskBits = NormalObject | NormalAttachableObject | Player | Wall; //what do I collide with?
		break;
	case NormalAttachableObject:
		filter.categoryBits = NormalAttachableObject;
		filter.maskBits = NormalObject | NormalAttachableObject | Player | Wall; //what do I collide with?
		break;
	case Player:
		filter.categoryBits = Player;
		filter.maskBits = NormalObject | NormalAttachableObject | Player | Weapon | Wall;
		break;
	case Trigger:
		filter.categoryBits = Trigger;
		filter.maskBits = Player;
		break;
	case Weapon:
		filter.categoryBits = Weapon;
		filter.maskBits = Player | Wall;
		break;
	case UnInteractableObject:
		filter.categoryBits = UnInteractableObject;
		filter.maskBits = Wall;
		break;
	case Wall:
		filter.categoryBits = Wall;
		filter.maskBits = UnInteractableObject | Wall;
		break;
	}
	return filter;
}

void Collider::destroyFixture(int i) {
	body_->DestroyFixture(fixtures_[i]);
	/*fixtures_.erase(fixtures_.begin() + i);
	fixtureDef_.erase(fixtureDef_.begin() + i);
	shape_.erase(shape_.begin() + i);*/

}
