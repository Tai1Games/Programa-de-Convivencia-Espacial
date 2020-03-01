#pragma once
#include <SDL.h>
#include "Constants.h"
#include <memory>
#include <assert.h>
#include "EntityManager.h"
#include "SDLTexturesManager.h"
#include "SDLAudioManager.h"
#include "SDLFontsManager.h"
#include "Resources.h"
#include "SDL_macros.h"
#include "iostream"
#include "checkML.h"


using namespace std;
class PlayState;
//Interfaz entre el juego y el display
class SDL_Game
{
private:
	bool exit_;
	void initializeResources();
	void closeResources();
protected:

	//Fonts
	SDLFontsManager* fonts_ = nullptr;

	//Textures
	SDLTexturesManager* textures_ = nullptr;

	//Audio
	SDLAudioManager* audio_ = nullptr;

	//Rng

	SDL_Window* window_;
	SDL_Renderer* renderer_;
	PlayState* gameState_;

	static unique_ptr<SDL_Game> instance_;
public:
	void start();
	SDL_Game();
	virtual ~SDL_Game();

	SDL_Game(SDL_Game&) = delete;
	SDL_Game& operator=(SDL_Game&) = delete;

	//inline static SDL_Game* instance() {
	//	assert(instance_.get() != nullptr);
	//	return instance_.get();
	//	std::cout << "He sido llamado por singleton" << std::endl;
	//}

	static SDL_Game* instance() {
		if (instance_.get() == nullptr) {
			instance_.reset(new SDL_Game());
		}
		return instance_.get();
	}


	inline unsigned int getTime() {
		return SDL_GetTicks();
	}

	SDLTexturesManager* getTexturesMngr() { return textures_; }
	SDL_Renderer* getRenderer() { return  renderer_; }
};

