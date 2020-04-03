#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(Vector2D position, Vector2D direction, int textureId, float speed, Uint16 size, Uint16 lifeTime, float speedVariation, float emissionConeAngle) :
	Component(ComponentType::ParticleEmitter), position_(position), direction_(direction), textureId_(textureId), speed_(speed),
	size_(size), lifeTime_(lifeTime), speedVariation_(speedVariation), emissionConeAngle_(emissionConeAngle) {}

void ParticleEmitter::init() {
	texture_ = SDL_Game::instance()->getTexturesMngr()->getTexture(textureId_);
	msPerFrame = CONST(float, "MS_PER_FRAME");
}

void ParticleEmitter::update() {
	if (emitting_) {
		frame_++;
		if (lifeTime_ != 0) {
			timeEmitted_ += msPerFrame;
			if (timeEmitted_ > lifeTime_)
				emitting_ = false;
		}
	}
}

void ParticleEmitter::draw() const {

}