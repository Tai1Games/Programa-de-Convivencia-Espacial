#include "Resources.h"
#include "SDL_Macros.h"

vector<Resources::FontInfo> Resources::fonts_{
	//Fuentes {nombre_en_enum, ruta, tama�o}
	{NES_Chimera , resourcesPath+"fonts/NES-Chimera.ttf", 38},
	{Digits_Font , resourcesPath+"fonts/Digits_Font.ttf", 38}
};

vector<Resources::ImageInfo> Resources::images_{
	//Im�genes {nombre_en_enum, ruta}

	{ Debug, resourcesPath + "textures/debug.png" },
	{ Tinky, resourcesPath + "textures/Tinky.png" },
	{ ActiveHealth, resourcesPath + "textures/VidaActiva.png" },
	{ DisableHealth, resourcesPath + "textures/VidaInactiva.png" },
	{ Slipper, resourcesPath + "textures/Chancla.png" },
	{ Stapler, resourcesPath + "textures/Grapadora.png" },
	{ Extinguisher, resourcesPath + "textures/Extintor.png" },
	{ Piedra, resourcesPath + "textures/Piedra.png" },
	{ Pelota, resourcesPath + "textures/PelotaSaltarina.png" },
	{ Mancuerna, resourcesPath + "textures/Mancuerna.png" },
	{ Hands, resourcesPath + "textures/handsActualizadas.png" },
	{ Body, resourcesPath + "textures/bodyNeutral.png" },
	{ PinkTinky, resourcesPath + "textures/PinkTinky.png"},
	{ ImpulseArrow, resourcesPath + "textures/FlechaImpulso.png"},
	{ ImpulseBackground, resourcesPath + "textures/ImpulsoBackground.png"},
	{ Slider, resourcesPath + "textures/Slider.png"},
	{ SliderControl, resourcesPath + "textures/SliderControl.png"},
	{ LivingRoom,resourcesPath + "textures/SalaDeEstar.png"},
	{ BoilerRoom,resourcesPath + "textures/SalaCaldera.png"},
	{ SalaGimnasio,resourcesPath + "textures/gimnasio.png"},
	{ Negro ,resourcesPath + "textures/Negro.png"},
	{ Router,resourcesPath + "textures/Router.png" },
	{ Router,resourcesPath + "textures/Router.png" },
	{ Coin, resourcesPath + "textures/DogeCoin.png" },
	{ CoinUI, resourcesPath + "textures/DogeCoinUI.png"},
	{ CanvasTimer, resourcesPath + "textures/COSO.png"},
	{ SuddenDeathText, resourcesPath + "textures/suddenDeathText.png"},
	{ EmptyProgressBar, resourcesPath + "textures/EmptyProgressBar.png"},
	{ ProgressBar, resourcesPath + "textures/ProgressBar.png"},
	{ EmptyProgressBar2, resourcesPath + "textures/EmptyProgressBar2.png"},
	{ ProgressBar2, resourcesPath + "textures/ProgressBar2.png"},
	{ Fireball,resourcesPath + "textures/fireball_placeholder.png"},
	{ Boiler,resourcesPath + "textures/boiler_placeholder.png"},
	{ PadSpriteSheet,resourcesPath + "textures/ColchonetaSpriteSheet.png" },
	{ TSet_Kenney1bit , resourcesPath+"tilemaps/modded_colored.png"},
	{ TSet_Dungeon , resourcesPath+"tilemaps/dungeon_ts.png"},
	{IncreasingFreqButton,resourcesPath + "textures/InreasingFrecButton.png"},
	{DecreasingFreqButton,resourcesPath + "textures/DecreasingFrecButton.png"}
};

vector<Resources::TextMsgInfo> Resources::messages_{
	//Mensajes predeterminados {nombre_en_enum, texto, color, fuente}. Ejemplo abajo
	//{ HelloWorld, "Hello World", { COLOR(0xaaffffff) }, ARIAL16 }
	{ PauseText, "PAUSA", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ ResumeText, "Reanudar", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ SoundText, "Sonido", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ ExitText, "Salir", { COLOR(0xc7f2edff) }, FontId::NES_Chimera }

};

vector<Resources::MusicInfo> Resources::musics_{
	//M�sica {nombre_en_enum, ruta}
	{ MainMenuMusic , resourcesPath + "sound/mainMenu.mp3" },
	{ EntranceMusic , resourcesPath + "sound/entrance.mp3" },
	{ LivingRoomMusic , resourcesPath + "sound/livingRoom.mp3" },
	{ GymMusic , resourcesPath + "sound/gym.mp3" },
	{ RevealMusic, resourcesPath + "sound/gotem.mp3" }
};

vector<Resources::SoundInfo> Resources::sounds_{
	//Efectos de sonido {nombre_en_enum, ruta}. Ejemplo abajo
	//{ Shoot, "../assets/game/sound/shoot.mp3" },
};

map<std::string, Resources::TextureId> Resources::tilesetTag_{
	{"modded_colored",TextureId::TSet_Kenney1bit},
	{"dungeon_ts",TextureId::TSet_Dungeon}
};
