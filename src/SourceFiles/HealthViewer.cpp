#include "HealthViewer.h"
#include "Entity.h"

HealthViewer::HealthViewer(int texActiveId, int texDisabledId, b2Vec2 pos) : Component(ComponentType::HealthViewer)
{
	pos_ = pos;		//Posicion desde la cual se pondrán las vidas ya que varia según para que jugador
	activeTextureId_ = texActiveId;
	disableTextureId_ = texDisabledId;
}

void HealthViewer::init()
{
	//Diria que no hace falta poner nada mas...
	he = GETCMP1_(Health);
	full = SDL_Game::instance()->getTexturesMngr()->getTexture(activeTextureId_);
	empty = SDL_Game::instance()->getTexturesMngr()->getTexture(disableTextureId_);
}
void HealthViewer::update()
{
	//Todo lo hace el draw, este no sirve ninguna función 
}
void HealthViewer::draw()
{
	for (int i = 1; i <= he->getHealthMax(); i++) {
		SDL_Rect dest = { pos_.x + (30*i), pos_.y, 40, 50 };

		if (i <= he->getHealth()) {		//Si tiene esas X vidas las muertra como llenas
			full->render(dest, 0, SDL_Rect{ 0, 0, 613,667 });
		}
		else {		//Si no las tiene, se dibujarán como vacias
			empty->render(dest, 0, SDL_Rect{ 0, 0, 613,667 });
		}
	}

}

void HealthViewer::handleInput() {

}