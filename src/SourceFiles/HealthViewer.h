#pragma once
#include "Component.h"
#include "Resources.h"
#include "Texture.h"
#include "Health.h"
#include "box2d.h"

class HealthViewer : public Component {
private:
	Texture* full = nullptr;	//Textura que se muestra si tenemos ese "toque"
	Texture* empty = nullptr;	//Textura que indica que ya no disponemos de ese "toque"

	Health* he = nullptr;		//Actualizar la lista de Componentes :D
	b2Vec2 pos_;

	int activeTextureId_;
	int disableTextureId_;

public:
	//Punteros a las 2 texturas de la vida y la posición de origen
	HealthViewer(int texActiveId , int texDisabledId, b2Vec2 pos);

	virtual ~HealthViewer() { full = nullptr; empty = nullptr; };

	void init() override;
	void update()override;
	void draw() const override;
	void handleInput()override;

};