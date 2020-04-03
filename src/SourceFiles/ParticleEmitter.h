#pragma once
#include "Component.h"
#include "Vector2D.h"
#include "checkML.h"

class ParticleEmitter :
	public Component
{
protected:
	ComponentType::CmpId id_;

	Vector2D position_;
	Vector2D direction_;

	//Velocidad con las que salen las particulas
	float speed_;

	//Aleatoridad de la velocidad de las particulas
	float speedVariation_ = 0;

	//Maximo angulo de aleatoridad segun el vector direccion
	//Valores entre [0,180]
	float emissionConeAngle_ = 10.0;

	//Tiempo que pasa emitiendo en milisegundos
	//valor 0 para infinito
	//default 1000 milisegundos
	Uint16 lifeTime_ = 1000;
	Uint16 timeEmitted_ = 0;
	Uint8 msPerFrame;

	int frame_ = 0;

	bool emitting_ = false;

	//Tamaño de la particula en cuadrado
	Uint16 size_ = 100;

	int textureId_;
	Texture* texture_;
public:
	ParticleEmitter(Vector2D position, Vector2D direction, int textureId, float speed, Uint16 size, Uint16 lifeTime, float speedVariation, float emissionConeAngle);
	virtual ~ParticleEmitter() { Component::~Component(); };

	virtual void init() override;
	virtual void update() override;
	virtual void draw() const override;

	//Devuelve si se ha detenido o empezado
	bool PlayStop() { timeEmitted_ = 0; return emitting_ = !emitting_; };

	void setSize(Uint16 size) { size_ = size; };
	void setLifeTime(Uint16 time) { lifeTime_ = time; };
};

