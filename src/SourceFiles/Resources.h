#pragma once

#include <SDL.h>
#include <string>
#include <vector>
#include "checkML.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

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
		Chancla,
		Extintor,
		Mancuerna,
		Pelota,
		Grapadora,
		Piedra,
		Body,
		Hands,
		PinkTinky,
		FlechaImpulso,
		ImpulsoBackground,
		Slider,
		SliderControl,
		SalaDeEstar,
		Negro,
		Router,
		Coin,
		EmptyProgressBar,
		ProgressBar,
		EmptyProgressBar2,
		ProgressBar2,
		Fireball,
		Boiler,

		// text
		PauseText,
		ResumeText,
		SoundText,
		ExitText
	};

	enum AudioId : std::size_t {
		// music
		MainTheme,
		Reveal,

		// sound effects

	};

	enum FontId : std::size_t {
		NES_Chimera
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
