#pragma once
#include "Component.h"

class AnimatedViewer;
class Collider;
class Fireball :
	public Component
{
private:
	int damage_ = 0; //daño que hace al impactar con el jugador
	int coinDamage_ = 0;
	AnimatedViewer* viewer_ = nullptr;
	Collider* col_ = nullptr;
public:
	Fireball() : Component(ComponentType::Fireball) {}
	~Fireball() {};
	virtual void init() override;
	void setActive(bool to, b2Vec2 pos, double angle = 0);

	virtual void onCollisionEnter(Collision* c);
};
