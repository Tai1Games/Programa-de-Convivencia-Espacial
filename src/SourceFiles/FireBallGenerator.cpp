#include "FireBallGenerator.h"
#include "Collider.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Viewer.h"
#include "Resources.h"
#include "ParticleEmitter.h"
#include <math.h>

void FireBallGenerator::init() {
	col_ = GETCMP1_(Collider);
	particleEmitter_ = GETCMP1_(ParticleEmitter);
	boilerViewer_ = GETCMP1_(Viewer);
	pos_ = col_->getPos();
	radius = sqrt(pow(col_->getH(0), 2) + pow(col_->getW(0), 2))/*+0.5*/; //JAJA he hecho una hipotenusa despues del instiuto
	//cout << "radius " << radius << endl;

	//initialize constants
	minCd_ = CONST(int, "FBGEN_MIN_COOLDOWN");
	maxCd_ = CONST(int, "FBGEN_MAX_COOLDOWN");
	minFireballs_ = CONST(int, "FBGEN_MIN_FIREBALLS");
	maxFireballs_ = CONST(int, "FBGEN_MIN_FIREBALLS");
	particleGenOddsModifier_ = CONST(int, "FBGEN_PARTICLE_GEN_ODDS_MODIFIER");
	fireballSpeed_ = CONST(int, "FIREBALL_SPEED");
	limitMinCd_ = CONST(int, "FBGEN_LIMIT_MIN_COOLDOWN");
	limitMaxCd_ = CONST(int, "FBGEN_LIMIT_MAX_COODLOWN");
	cdTimeChange_ = CONST(int, "FBGEN_CHANGE_CD_ON_BUTTON_ACTION");
	cdVariability = maxCd_ - minCd_;
	manager_ = entity_->getEntityManager();
	fbPool_.init(manager_, physicsWorld_);
	nextShot_ = SDL_Game::instance()->getTime() + CONST(int,"FBGEN_INITIAL_OFFSET") 
		+ (rand() % maxCd_ + minCd_);

	particleEmitter_->setPositionCollider(col_);
	particleEmitter_->setDirection({ 0,1 });
	particleEmitter_->PlayStop();
	particleEmitter_->setGenerationOddsClamp(CONST(int, "FBGEN_MIN_PARTICLE_GEN_ODDS"), CONST(int, "FBGEN_MAX_PARTICLE_GEN_ODDS"));

	boilerViewer_->setOffset({ 50, 50 });
}

void FireBallGenerator::update() {
	//entity_->getEntityManager()->addEntity();
	uint actTime = SDL_Game::instance()->getTime();
	if (actTime > nextShot_) {
		int n = rand() % maxFireballs_ + minFireballs_;
		addFireball(n);
		nextShot_ = actTime + (rand() % maxCd_ + minCd_);
	}
}

void FireBallGenerator::addFireball(int n) {
	//fireballPool_->addFireBall(pos_);
	for (int i = 0; i < n; i++) {
		double radians = (rand() % 360)*(CONST(double, "PI")/180.0); //sientete orgulloso, Don Carlos
		b2Vec2 spawnDir = b2Vec2(cos(radians) * radius, sin(radians) * radius);
		b2Vec2 spawnPos = pos_ + spawnDir;
		//cout << radians << endl;
		//cout << "Spawned at " << spawnPos.x << "  " <<spawnPos.y;
		spawnDir.Normalize();
		spawnDir.x *= fireballSpeed_;
		spawnDir.y *= fireballSpeed_;
		fbPool_.addFireBall(spawnPos,spawnDir);
	}
}

void FireBallGenerator::onButtonAction(bool inc_dec) {

	if (inc_dec) particleEmitter_->modifyGenerationOdds(-particleGenOddsModifier_);
	else particleEmitter_->modifyGenerationOdds(particleGenOddsModifier_);

	if (inc_dec && minCd_ >= limitMinCd_) {
		maxCd_ -= cdTimeChange_;
		minCd_ -= cdTimeChange_;
		if (minCd_ < limitMinCd_) {
			minCd_ = limitMinCd_;
			maxCd_ = minCd_ + cdVariability;
		}
		cout << "Generation rate increased to [" << minCd_ << ", " << maxCd_ << "](ms)." << endl;
	}
	else if (!inc_dec && maxCd_ <= limitMaxCd_) {
		maxCd_ += cdTimeChange_;
		minCd_ += cdTimeChange_;
		if (maxCd_ > limitMaxCd_) {
			maxCd_ = limitMaxCd_;
			minCd_ = limitMaxCd_ - cdVariability;
		}
		cout << "Generation rate decreased to [" << minCd_ << ", " << maxCd_ << "](ms)." << endl;
	}
}