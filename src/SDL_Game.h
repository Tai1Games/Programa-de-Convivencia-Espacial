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

using namespace std;
//Interfaz entre el juego y el display
class SDL_Game
{
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

	static unique_ptr<SDL_Game> instance_;
private:
	void initializeResources();
	void closeResources();
public:
	SDL_Game();
	virtual ~SDL_Game();

	SDL_Game(SDL_Game&) = delete;
	SDL_Game& operator=(SDL_Game&) = delete;

	inline static SDL_Game* instance() {
		assert(instance_.get() != nullptr);
		return instance_.get();
	}

	inline unsigned int getTime() {
		return SDL_GetTicks();
	}

	SDLTexturesManager* getTexturesMngr() { return textures_; }
};

