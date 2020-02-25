#pragma once
#include <SDL.h>
#include "Constants.h"

//Interfaz entre el juego y el display
class SDL_Game
{
private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;
protected:
public:
	SDL_Game();
	~SDL_Game();
};

