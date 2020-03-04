#pragma once
#include "Component.h"
#include "Texture.h"
#include "Health.h"
#include "Vector2D.h"

class HealthViewer : public Component {
private:
	Texture* full = nullptr;	//Textura que se muestra si tenemos ese "toque"
	Texture* empty = nullptr;	//Textura que indica que ya no disponemos de ese "toque"

	Health* he = nullptr;		//Actualizar la lista de Componentes :D
	Vector2D pos;

public:
	//Punteros a las 2 texturas de la vida y la posición de origen
	HealthViewer(Texture* f_, Texture* e_, Vector2D pos_);

	virtual ~HealthViewer() { full = nullptr; empty = nullptr; };

	void init() override;
	void update()override;
	void draw() const override;
	void handleInput()override;

};