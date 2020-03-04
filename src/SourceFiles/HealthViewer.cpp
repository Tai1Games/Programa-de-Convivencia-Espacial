#include "HealthViewer.h"
#include "Entity.h"

HealthViewer::HealthViewer(Texture* f_, Texture* e_, Vector2D pos_) : Component(ComponentType::HealthViewer)
{
	full = f_;
	empty = e_;
	pos = pos_;		//Posicion desde la cual se pondrán las vidas ya que varia según para que jugador
}

void HealthViewer::init()
{
	//Diria que no hace falta poner nada mas...
	he = GETCMP1_(Health);
}
void HealthViewer::update()
{
	//Todo lo hace el draw, este no sirve ninguna función 
}
void HealthViewer::draw() const
{
	for (int i = 1; i <= he->getHealthMax(); i++) {
		SDL_Rect dest = { pos.getX()+ (30*i), pos.getY(), 40, 50 };

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