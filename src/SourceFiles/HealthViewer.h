#pragma once
#include "Component.h"
#include "Resources.h"
#include "Texture.h"
#include "Health.h"
#include "box2d.h"

class PlayerData;
class HealthViewer : public Component {
private:
	Texture* full = nullptr;	//Textura que se muestra si tenemos ese "toque"
	Texture* empty = nullptr;	//Textura que indica que ya no disponemos de ese "toque"

	Health* he = nullptr;		//Actualizar la lista de Componentes :D
	PlayerData* playerData_ = nullptr;
	b2Vec2 pos_;

	int activeTextureId_;
	int disableTextureId_;

public:
	//Punteros a las 2 texturas de la vida y la posición de origen
	HealthViewer(int texActiveId , int texDisabledId);

	virtual ~HealthViewer() { full = nullptr; empty = nullptr; };

	void init() override;
	void update()override;
	void draw() const override;
	void handleInput()override;
	b2Vec2 getPos(){return pos_;};
	int getWidth() { return (he->getHealthMax() * (LIFE_DRAW_OFFSET + LIFE_WIDTH)); }
	void setPos(int player);
};