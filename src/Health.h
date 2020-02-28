#pragma once
#include "Component.h"

class Health: public Component
{
public:
	Health(int l);
	~Health();

	void resetHealth() { lifes_ = lifesMax_; }
	bool subtractLife(int damage); //return true si despues del daño sigue vivo
	void addLife(int sum); //suma sum a la vida siempre y cuando esta no supere la constanteGeneral
	int getHealthMax() { return lifesMax_; }
private:
	int lifes_;
	int lifesMax_;
};

