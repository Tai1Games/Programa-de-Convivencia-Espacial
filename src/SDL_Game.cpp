#include "SDL_Game.h"

SDL_Game::SDL_Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow(WINDOW_NAME.c_str(),SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH, WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Game::~SDL_Game() {
	window_ =  nullptr;
	renderer_ =  nullptr;
	SDL_Quit();
}