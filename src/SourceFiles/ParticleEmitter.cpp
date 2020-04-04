#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(Vector2D position, Vector2D direction, int textureId, float speed, Uint16 particleLifetime, Uint16 size, Uint16 emittingTime, float speedVariation, float emissionConeAngle) :
	Component(ComponentType::ParticleEmitter), position_(position), direction_(direction), textureId_(textureId), speed_(speed),
	particleLifetime_(particleLifetime), size_(size), emittingTime_(emittingTime), speedVariation_(speedVariation), emissionConeAngle_(emissionConeAngle),
	msPerFrame_(0), maxParticles_(0){}

void ParticleEmitter::init() {

	texture_ = SDL_Game::instance()->getTexturesMngr()->getTexture(textureId_);
	msPerFrame_ = CONST(float, "MS_PER_FRAME");
	maxParticles_ = CONST(int, "MAX_PARTICLES_DEFAULT");
}

void ParticleEmitter::update() {
	if (emitting_) {
		if (emittingTime_ != 0) {
			timeEmitted_ += msPerFrame_;
			if (timeEmitted_ > emittingTime_)
				emitting_ = false;
		}
		if (particles_.size() < maxParticles_) {
			//Añadir rng
			//direction + angulo random
			//speed_ + variacion random
			particles_.push_back({ position_,direction_,0,speed_ });
		}
	}

	if (particles_.size() > 0){
		for (list<Particle>::iterator part = particles_.begin(); part != particles_.end(); part++) {
			part->lifeTime += msPerFrame_;
			if (part->lifeTime > particleLifetime_)
				particlesToDelete_.push(part);
			else
				part->position = part->position + part->direction * part->speed;
		}
		while (particlesToDelete_.size() > 0) {
			particles_.erase(particlesToDelete_.front());
			particlesToDelete_.pop();
		}
	}
}

void ParticleEmitter::draw() const {
	for (Particle part : particles_) {
		texture_->render({ (int)part.position.getX() - size_ / 2,(int)part.position.getY() - size_ / 2,size_,size_ });
	}
}