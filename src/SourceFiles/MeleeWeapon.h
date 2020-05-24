#pragma once
#include "ActionableWeapon.h"

class MeleeWeapon :
	public ActionableWeapon
{
protected:

	int damage_ = 0;
	int nHitboxActiveFrames_ = CONST(int, "WEAPON_MELEE_HIT_FRAMES");
	int nAnimActiveFrames_ = CONST(int, "WEAPON_MELEE_HIT_VISIBLE_FRAMES");
public:
	MeleeWeapon(WeaponID wId, int dmg, int impactDmg, int cooldownFrames, int impctForce);
	MeleeWeapon(ComponentType::CmpId compType, WeaponID wId, int dmg, int impactDmg, int cooldownFrames, int impctForce);
	virtual ~MeleeWeapon() {};

	//virtual void init() override;
	virtual void action() override;
	virtual void update() override;
	//Alterar el viewer

	virtual void PickObjectBy(int index) override;
	virtual void onCollisionEnter(Collision* c) override;
	virtual void UnPickObject() override;

	//virtual void detectPlayer(Entity* playerDetected, int id) override;
	//virtual void loseContactPlayer(Entity* playerDetected, int id) override;
};

