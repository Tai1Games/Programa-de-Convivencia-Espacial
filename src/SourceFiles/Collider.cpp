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

Collider::Collider(b2World* world, b2BodyType type, float x, float y, float radius,
	float density, float friction, float restitution, float linearDrag, float angDrag, CollisionLayer c, bool sensor):
	world_(world),
	Component(ComponentType::Collider) {

	bodyDef_.type = type;
	bodyDef_.position.Set(x, y);
	bodyDef_.linearDamping = linearDrag;
	bodyDef_.angularDamping = angDrag;
	body_ = world_->CreateBody(&bodyDef_);

	createCircularFixture(radius, density, friction, restitution, c, sensor);
}

void Collider::init() {
	PIXELS_PER_METER = CONST(double, "PIXELS_PER_METER");
	WINDOW_HEIGHT = CONST(int, "WINDOW_HEIGHT");
	setUserData(entity_);
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
	aux.filter = getFilterFromLayer(c);
	aux.friction = friction;
	aux.restitution = restitution;
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
	aux.filter = getFilterFromLayer(c);
	aux.friction = friction;
	aux.restitution = restitution;
	aux.isSensor = sensor;
	fixtureDefs_.push_back(aux);
	fixtures_.push_back(body_->CreateFixture(&fixtureDefs_.back()));
}

b2Filter Collider::getFilterFromLayer(CollisionLayer c) {
	b2Filter filter;
	filter.categoryBits = c;
	return setFilterLayerBits(filter);
}

b2Filter Collider::setFilterLayerBits(b2Filter filter) {
	switch (filter.categoryBits) {
	case NormalObject:
		// = 0000 0111 1100 1011
		filter.maskBits = NormalObject | NormalAttachableObject | Player | Wall | NonGrababbleWall; //what do I collide with?
		break;
	case NormalAttachableObject:
		// = 0000 0111 1100 1011
		filter.maskBits = NormalObject | NormalAttachableObject | Player | Wall | NonGrababbleWall; //what do I collide with?
		break;
	case Player1:
	case Player2:
	case Player3:
	case Player4:
	case Player:
		// = 0000 0111 1111 1011
		filter.maskBits = InteractsWithPlayer;
		break;
	case Trigger:
		// = 0000 0111 1001 0000
		filter.maskBits = Player | Trigger;
		break;
	case PickableObject:
		// = 0000 0111 1100 0000
		filter.maskBits = Player | Wall | NonGrababbleWall;
		break;
	case UnInteractableObject:
		// = 0000 0000 0100 1000
		filter.maskBits = Wall | NonGrababbleWall;
		break;
	case Wall:
		// = 0000 0111 1010 0111
		filter.maskBits = UnInteractableObject | Player | NormalAttachableObject | NormalObject | PickableObject;
		break;
	case NonGrababbleWall:
		// = 0000 0111 1010 0111
		filter.maskBits = UnInteractableObject | Player | NormalAttachableObject | NormalObject | PickableObject;
		break;
	default:
		filter.maskBits = filter.categoryBits;
		break;
	}
	return filter;
}

void Collider::disableFixtureCollisions(int fixtureIndex) {
	b2Filter filter;
	filter.maskBits = 0;
	filter.categoryBits = 0;
	getFixture(fixtureIndex)->SetFilterData(filter);
}

void Collider::destroyFixture(int i) {
	body_->DestroyFixture(fixtures_[i]);
	fixtures_.erase(fixtures_.begin() + i);
	fixtureDefs_.erase(fixtureDefs_.begin() + i);
	//shape_.erase(shape_.begin() + i);

}