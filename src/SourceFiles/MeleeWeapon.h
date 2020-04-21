#pragma once
#include "ActionableWeapon.h"

class MeleeWeapon :
	public ActionableWeapon
{
protected:
	std::vector<EnemyData>playersInsideRange_;
	int index = 2;

	int damage_ = 0;
public:
	MeleeWeapon(WeaponID wId, int dmg, int impactDmg, int cooldownFrames);
	MeleeWeapon(ComponentType::CmpId compType, WeaponID wId, int dmg, int impactDmg, int cooldownFrames);
	virtual ~MeleeWeapon() {};

	virtual void init() override;
	virtual void action() override;
	//Alterar el viewer

	virtual void PickObjectBy(Hands* playerHands) override;
	virtual void UnPickObject() override;

	virtual void detectPlayer(Entity* playerDetected, int id) override;
	virtual void loseContactPlayer(Entity* playerDetected, int id) override;
};

