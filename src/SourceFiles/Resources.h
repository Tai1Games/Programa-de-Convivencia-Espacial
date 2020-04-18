#pragma once

#include <SDL.h>
#include <string>
#include <vector>
#include "checkML.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

static string resourcesPath = "assets/game/";

class Resources {
public:

	enum TextureId : std::size_t {
		// images
		Debug,
		Tinky,
		ActiveHealth,
		DisableHealth,
		TSet_Kenney1bit,
		TSet_Dungeon,
		Slipper,
		Extinguisher,
		Mancuerna,
		Pelota,
		Stapler,
		Piedra,
		Body,
		Hands,
		PinkTinky,
		ImpulseArrow,
		ImpulseBackground,
		Slider,
		SliderControl,
		LivingRoom,
		BoilerRoom,
		SalaGimnasio,
		Negro,
		Router,
		Coin,
		CoinUI,
		CanvasTimer,
		SuddenDeathText,
		EmptyProgressBar,
		ProgressBar,
		EmptyProgressBar2,
		ProgressBar2,
		Fireball,
		Boiler,
		PadSpriteSheet,
		Treadmill,
		TreadmillSpriteSheet,


		// text
		PauseText,
		ResumeText,
		SoundText,
		ExitText
	};

	enum AudioId : std::size_t {
		// music
		MainMenuMusic,
		EntranceMusic,
		LivingRoomMusic,
		GymMusic,
		RevealMusic,

		// sound effects

	};

	enum FontId : std::size_t {
		NES_Chimera,
		Digits_Font
	};

	struct FontInfo {
		FontId id;
		string fileName;
		int size;
	};

	struct ImageInfo {
		TextureId id;
		string fileName;
	};

	struct TextMsgInfo {
		TextureId id;
		string msg;
		SDL_Color color;
		FontId fontId;
	};

	struct MusicInfo {
		AudioId id;
		string fileName;
	};

	struct SoundInfo {
		AudioId id;
		string fileName;

	};

	static vector<FontInfo> fonts_; // initialized in .cpp
	static vector<ImageInfo> images_; // initialized in .cpp
	static vector<TextMsgInfo> messages_; // initialized in .cpp
	static vector<MusicInfo> musics_; // initialized in .cpp
	static vector<SoundInfo> sounds_; // initialized in .cpp
	static map<std::string, Resources::TextureId> tilesetTag_; // initialized in .cpp

};
