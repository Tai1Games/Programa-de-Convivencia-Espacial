#include "Resources.h"
#include "SDL_Macros.h"

vector<Resources::FontInfo> Resources::fonts_{
	//Fuentes {nombre_en_enum, ruta, tama�o}
	{NES_Chimera , "../../assets/game/fonts/NES-Chimera.ttf", 38},
	{Digits_Font , "../../assets/game/fonts/Digits_Font.ttf", 38}
};

vector<Resources::ImageInfo> Resources::images_{
	//Im�genes {nombre_en_enum, ruta}
	{ Debug, "../../assets/game/textures/debug.png" },
	{ Tinky, "../../assets/game/textures/Tinky.png" },
	{ ActiveHealth, "../../assets/game/textures/VidaActiva.png" },
	{ DisableHealth, "../../assets/game/textures/VidaInactiva.png" },
	{ Slipper, "../../assets/game/textures/Chancla.png" },
	{ Stapler, "../../assets/game/textures/Grapadora.png" },
	{ Extinguisher, "../../assets/game/textures/Extintor.png" },
	{ Piedra, "../../assets/game/textures/Piedra.png" },
	{ Pelota, "../../assets/game/textures/PelotaSaltarina.png" },
	{ Mancuerna, "../../assets/game/textures/Mancuerna.png" },
	{ Hands, "../../assets/game/textures/handsActualizadas.png" },
	{ Body, "../../assets/game/textures/bodyNeutral.png" },
	{ PinkTinky, "../../assets/game/textures/PinkTinky.png"},
	{ ImpulseArrow, "../../assets/game/textures/FlechaImpulso.png"},
	{ ImpulseBackground, "../../assets/game/textures/ImpulsoBackground.png"},
	{ Slider, "../../assets/game/textures/Slider.png"},
	{ SliderControl, "../../assets/game/textures/SliderControl.png"},
	{ SalaDeEstar,"../../assets/game/textures/SalaDeEstar.png"},
	{ SalaCaldera,"../../assets/game/textures/SalaCaldera720Des.png"},
	{ Negro ,"../../assets/game/textures/Negro.png"},
	{ Router,"../../assets/game/textures/Router.png" },
	{Router,"../../assets/game/textures/Router.png" },
	{ Coin, "../../assets/game/textures/DogeCoin.png" },
	{ CoinUI, "../../assets/game/textures/DogeCoinUI.png"},
	{ CanvasTimer, "../../assets/game/textures/COSO.png"},
	{ SuddenDeathText, "../../assets/game/textures/suddenDeathText.png"},
	{ EmptyProgressBar, "../../assets/game/textures/EmptyProgressBar.png"},
	{ ProgressBar, "../../assets/game/textures/ProgressBar.png"},
	{ EmptyProgressBar2, "../../assets/game/textures/EmptyProgressBar2.png"},
	{ ProgressBar2, "../../assets/game/textures/ProgressBar2.png"},
	{Fireball,"../../assets/game/textures/fireball_placeholder.png"},
	{Boiler,"../../assets/game/textures/boiler_placeholder.png"},
	{ PadSpriteSheet,"../../assets/game/textures/ColchonetaSpriteSheet.png" },

		{ TSet_Kenney1bit , "../../assets/game/tilemaps/modded_colored.png"},
		{ TSet_Dungeon , "../../assets/game/tilemaps/dungeon_ts.png"}
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
	{ MainTheme , "../../assets/game/sound/mainMenu.mp3" },
	{Reveal, "../../assets/game/sound/gotem.mp3"}
};

vector<Resources::SoundInfo> Resources::sounds_{
	//Efectos de sonido {nombre_en_enum, ruta}. Ejemplo abajo
	//{ Shoot, "../assets/game/sound/shoot.mp3" },
};

map<std::string, Resources::TextureId> Resources::tilesetTag_{
	{"modded_colored",TextureId::TSet_Kenney1bit},
	{"dungeon_ts",TextureId::TSet_Dungeon}
};
