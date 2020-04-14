#pragma once
#include "Component.h"
#include "checkML.h"
#include "Collider.h"
#include "Entity.h"

class Health: public Component
{
private:
	int lives_;
	int livesMax_;
	Collider* col_ = nullptr;
public:
	Health(int l);
	~Health();

	virtual void init() override;
	virtual void update() override {}
	void resetHealth() { lives_ = livesMax_; }
	bool subtractLife(int damage); //return true si despues del da�o sigue vivo
	void addLife(int sum); //suma sum a la vida siempre y cuando esta no supere la constanteGeneral
	int getHealthMax() { return livesMax_; }
	int getHealth() { return lives_; }

	virtual void onCollisionEnter(Collision* c);
};

