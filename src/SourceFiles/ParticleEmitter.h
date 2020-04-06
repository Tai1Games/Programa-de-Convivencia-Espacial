#pragma once
#include "Component.h"
#include "Vector2D.h"
#include <queue>
#include "checkML.h"

class Collider;

class ParticleEmitter :
	public Component
{
protected:
	Collider* collider_ = nullptr;

	Vector2D direction_;

	bool emitting_ = false;

	int textureId_;
	Texture* texture_ = nullptr;

	//Velocidad con las que salen las particulas
	float speed_;

	//Aleatoridad de la velocidad de las particulas
	int speedVariation_;

	//Maximo angulo de aleatoridad segun el vector direccion
	//Valores entre [0,180]
	int emissionConeAngle_;
	double PI;

	//Tamaño de la particula en cuadrado
	Uint16 size_;

	//Tiempo que pasa viva la particula en milisegundos
	//default 1000 milisegundos
	Uint16 particleLifetime_;

	//Tiempo que pasa emitiendo en milisegundos
	//valor 0 para infinito
	//default 1000 milisegundos
	Uint16 emittingTime_;
	Uint16 timeEmitted_ = 0;
	Uint8 msPerFrame_ = 0;
	Uint8 maxParticles_;

	struct Particle {
		Vector2D position;
		Vector2D direction;
		Uint16 lifeTime;
		float speed;
	};

	std::list<Particle> particles_;
	std::queue<list<Particle>::iterator> particlesToDelete_;
public:
	ParticleEmitter(Vector2D direction, int textureId, float speed, Uint16 particleLifetime=1000, Uint16 size = 20, Uint16 emittingTime = 1000, int speedVariation = 0, int emissionConeAngle = 10.0);
	virtual ~ParticleEmitter() { Component::~Component(); };

	virtual void init() override;
	virtual void update() override;
	virtual void draw() const override;

	//Devuelve si se ha detenido o empezado
	bool PlayStop() { timeEmitted_ = 0; return emitting_ = !emitting_; };

	void setSize(Uint16 size) { size_ = size; };
	void setLifeTime(Uint16 time) { emittingTime_ = time; };
	void setMaxParticles(Uint8 max) { maxParticles_ = max; };
};

