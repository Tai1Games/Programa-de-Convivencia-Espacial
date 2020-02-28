#include "SDL_Game.h"

unique_ptr<SDL_Game> SDL_Game::instance_;

SDL_Game::SDL_Game(){
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow(WINDOW_NAME.c_str(),SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH, WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

	initializeResources();
}

SDL_Game::~SDL_Game() {
	closeResources();

	SDL_DestroyRenderer(renderer_);
	renderer_ = nullptr;

	SDL_DestroyWindow(window_);
	window_ =  nullptr;
	
	SDL_Quit();
}

void SDL_Game::initializeResources() {
	textures_ = new SDLTexturesManager();
	textures_->init();

	for (auto& image : Resources::images_) {
		textures_->loadFromImg(image.id, renderer_, image.fileName);
	}
}

void SDL_Game::closeResources() {
	delete textures_;
}