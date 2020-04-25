#pragma once
#include "Component.h"

class Viewer;
class Collider;
class Fireball :
	public Component
{
private:
	const static int damage_ = 1000; //daño que hace al impactar con el jugador
	Viewer* vw_ = nullptr;
	Collider* col_ = nullptr;
	int coinDMG;
public:
	Fireball() :Component(ComponentType::Fireball),coinDMG(CONST(int,"FIREBALL_COIN_DMG")) {}
	~Fireball() {};
	virtual void init() override;
	void setActive(bool to, b2Vec2 pos);

	virtual void onCollisionEnter(Collision* c);
};

