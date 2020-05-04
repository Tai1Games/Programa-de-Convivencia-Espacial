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

		// room backgrounds
		MainMenuRoom,
		BoilerRoom,
		GymRoom,
		LivingRoom,
		TutorialRoom,
		GardenRoom,

		// UI
		ActiveHealth,
		DisableHealth,

		Slider,
		SliderControl,

		CanvasTimerBackground,
		CoinUI,
		SkullUI,
		SuddenDeathCapitalismModeText,
		SuddenDeathTimeModeText,

		EmptyProgressBar,
		EmptyProgressBar2,
		ProgressBar,
		ProgressBar2,

		KeyboardIcon,
		MouseIcon,
		ControllerIcon,

		// Weapons and map items

		// Players

		// Map elements
		IncreasingFreqButton,
		DecreasingFreqButton,
		TSet_Kenney1bit,
		TSet_Dungeon,
		Slipper,
		Extinguisher,
		Mancuerna,
		Ball,
		Stapler,
		Stone,
		Body,
		Hands,
		SpaceSuit,
		ImpulseArrow,
		ImpulseBackground,
		Fireball,
		Boiler,
		PadSpriteSheet,
		Treadmill,
		TreadmillSpriteSheet,
		PipeHor,
		PipeVer,
		CarnivorousPlant,
		Smoke,
		Tomato,
		TomatoRing,
		TreadmillPanel,

		// Gamemode specific elements
		Coin,
		Router,
		RoombaSpriteSheet,
		Remote,

		// miscel�nea
		Debug,
		Negro,
		Tinky,
		Transparent,

		// text
		PauseText,
		ResumeText,
		SoundText,
		ExitText,

		//modes
		Capitalism,
		Controller,
		Stocks,
		WiFight,
		Timed,
		Tutorial,
		//exit
		Exit,
		//maps
		LivingRoomText,
		BoilerRoomText,
		GymRoomText,
		//players
		OnePlayer,
		TwoPlayers,
		ThreePlayers,
		FourPlayers,
		FivePlayers, //es solo para iterar

		//tutorial	
		Completed,
		Slash,
		Zero,
		One,
		Two,
		Three,
		Four,	
		MoveTutorial,
		HoldTutorial,
		GrabTutorial,
		ActionTutorial,
		ThrowTutorial,
		DeathTutorial,
		TutorialEnd
	};

	enum AudioId : std::size_t {
		// music
		MainMenuMusic = TextureId::MainMenuRoom,
		LivingRoomMusic = TextureId::LivingRoom,
		GymMusic = TextureId::GymRoom,
		BoilerRoomMusic = TextureId::BoilerRoom,
		TutorialMusic = TextureId::TutorialRoom,
		EntranceMusic

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
