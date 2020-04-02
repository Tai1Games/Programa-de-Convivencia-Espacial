#include "SDL_Game.h"
#include "Resources.h"
#include "InputHandler.h"
#include "PlayState.h"

unique_ptr<SDL_Game> SDL_Game::instance_;

SDL_Game::SDL_Game() {
	constants_ = Constants("../config/constants.json");
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow(constants_.getConstant<string>("WINDOW_NAME").c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, constants_.getConstant<int>("WINDOW_WIDTH"),
		constants_.getConstant<int>("WINDOW_HEIGHT"), SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

	initializeResources();

	//Prueba multimedia
	textures_->getTexture(Resources::Tinky)->render({ constants_.getConstant<int>("WINDOW_WIDTH") / 2 - 70,constants_.getConstant<int>("WINDOW_HEIGHT") / 2 - 135,140,200 });

	Texture introText(renderer_,
		"PROGRAMA DE CONVIVENCIA ESPACIAL",
		fonts_->getFont(Resources::NES_Chimera),
		{ COLOR(0xc7f2edff) });
	introText.render(
		constants_.getConstant<int>("WINDOW_WIDTH") / 2 - introText.getWidth() / 2, constants_.getConstant<int>("WINDOW_HEIGHT") - 250);
	SDL_RenderPresent(renderer_);


	audio_->setMusicVolume(constants_.getConstant<int>("MAX_MUSIC_VOLUME"));
	audio_->playMusic(Resources::MainTheme, -1);
	inputHandler_ = new InputHandler();
	inputHandler_->initialiseGamepads();

}

SDL_Game::~SDL_Game() {
	closeResources();

	SDL_DestroyRenderer(renderer_);
	renderer_ = nullptr;

	SDL_DestroyWindow(window_);
	window_ = nullptr;

	SDL_Quit();
}

void SDL_Game::initializeResources() {
	/*random_ = new SRandBasedGenerator();
	random_->init();*/

	textures_ = new SDLTexturesManager();
	textures_->init();

	fonts_ = new SDLFontsManager();
	fonts_->init();

	audio_ = new SDLAudioManager();
	audio_->init();

	gamestateMachine_ = new GameStateMachine();

	for (auto& image : Resources::images_) {
		textures_->loadFromImg(image.id, renderer_, image.fileName);
	}

	for (auto& font : Resources::fonts_) {
		fonts_->loadFont(font.id, font.fileName, font.size);
	}

	for (auto& txtmsg : Resources::messages_) {
		textures_->loadFromText(txtmsg.id, renderer_, txtmsg.msg,
			fonts_->getFont(txtmsg.fontId), txtmsg.color);
	}

	for (auto& sound : Resources::sounds_) {
		audio_->loadSound(sound.id, sound.fileName);
	}

	for (auto& music : Resources::musics_) {
		audio_->loadMusic(music.id, music.fileName);
	}
}

void SDL_Game::closeResources() {
	delete textures_;
	textures_ = nullptr;
	delete fonts_;
	fonts_ = nullptr;
	delete audio_;
	audio_ = nullptr;
	delete gamestateMachine_;
	gamestateMachine_ = nullptr;
}

void SDL_Game::start() {
	exit_ = false;
	gamestateMachine_->changeToState(States::play);

	if (inputHandler_->getNumControllers() > 0) {
		while (!exit_) {
			Uint32 startTime = getTime();
			gamestateMachine_->handleInput();
			gamestateMachine_->update();
			gamestateMachine_->render();
			Uint32 frameTime = getTime() - startTime;
			if (frameTime < CONST(double, "MS_PER_FRAME"))
				SDL_Delay(CONST(double, "MS_PER_FRAME") - frameTime);
			if (SDL_Game::instance()->getInputHandler()->isExit()) exit_ = true;
		}
	}
	else std::cout << "Que tal si pones un manso eh? genio\n\n\n";
}
