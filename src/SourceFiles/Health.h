#pragma once
#include "Component.h"
#include "checkML.h"
#include "Collider.h"
#include "Entity.h"

class CollisionHandler;
class AnimatedPlayer;

class Health: public Component
{
private:
	int lives_;
	int livesMax_;
	AnimatedPlayer* anim_ = nullptr;
	Collider* col_ = nullptr;

	int INV_FRAMES_HIT_;
	int INV_FRAMES_RESPAWN_;
	int invFrames_;		//frames de invulnerabilidad restantes
	int loopsInv_;
	int animSpeed_;

public:
	Health(int l);
	~Health();

	virtual void init() override;
	virtual void update() override;
	void resetHealth() { lives_ = livesMax_; }
	bool subtractLife(int damage); //return true si despues del daño sigue vivo
	void addLife(int sum); //suma sum a la vida siempre y cuando esta no supere la constanteGeneral
	int getHealthMax() { return livesMax_; }
	int getHealth() { return lives_; }
	void playerDead(CollisionHandler* c);

	virtual void onCollisionEnter(Collision* c);
};

