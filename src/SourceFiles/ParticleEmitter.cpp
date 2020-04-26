#include "ParticleEmitter.h"
#include "Entity.h"
#include "Collider.h"

ParticleEmitter::ParticleEmitter(Vector2D direction, int textureId, float speed, int numTextures, Uint16 particleLifetime, Uint16 size, Uint16 emittingTime, int speedVariation, int emissionConeAngle) :
	Component(ComponentType::ParticleEmitter), direction_(direction), textureId_(textureId), speed_(speed), numTextures_(numTextures),
	particleLifetime_(particleLifetime), size_(size), emittingTime_(emittingTime), speedVariation_(speedVariation), emissionConeAngle_(emissionConeAngle),
	msPerFrame_(0), maxParticles_(0), PI(0){}

void ParticleEmitter::init() {
	collider_ = GETCMP1_(Collider);
	texture_ = SDL_Game::instance()->getTexturesMngr()->getTexture(textureId_);
	msPerFrame_ = CONST(float, "MS_PER_FRAME");
	maxParticles_ = CONST(int, "MAX_PARTICLES_DEFAULT");
	PI = CONST(double, "PI");
	textureSize_ = texture_->getHeight(); //Asumimos que si es un spritesheet, están organizados en vertical.
}

void ParticleEmitter::update() {
	if (emitting_) {
		timeEmitted_ += msPerFrame_;
		if (emittingTime_ != 0) {
			if (timeEmitted_ > emittingTime_)
				emitting_ = false;
		}
		if (particles_.size() < maxParticles_ && timeEmitted_ % 5 == 0) {
			SDL_Rect colliderRect = collider_->getRectRender();
			//direction + angulo random
			int angle = rand() % int(emissionConeAngle_ * 2) - emissionConeAngle_;
			Vector2D direction = direction_.rotate(angle);
			//speed_ + variacion random
			float speed = (speedVariation_ != 0) ? speed_ - speedVariation_ + rand() % int(speedVariation_ * 2) : speed_;
			particles_.push_back({ Vector2D((double)colliderRect.x + colliderRect.w / 2.0,(double)colliderRect.y + colliderRect.h / 2.0),direction,0,speed });
		}
	}

	if (particles_.size() > 0) {
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
		int randTexture = 0;
		if (numTextures_ > 1) {
			randTexture = rand() % numTextures_;
		}
		texture_->render({ (int)part.position.getX() - size_ / 2,(int)part.position.getY() - size_ / 2,size_,size_ }, 0, { randTexture * textureSize_, 0, textureSize_, textureSize_ });
	}
}