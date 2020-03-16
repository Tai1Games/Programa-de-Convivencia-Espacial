#include "Resources.h"
#include "SDL_Macros.h"

vector<Resources::FontInfo> Resources::fonts_ {
		//Fuentes {nombre_en_enum, ruta, tama�o}
		{NES_Chimera , "../../assets/game/fonts/NES-Chimera.ttf", 38}
};

vector<Resources::ImageInfo> Resources::images_ {
		//Im�genes {nombre_en_enum, ruta}
		{ Debug, "../../assets/game/textures/debug.png" },
		{ Tinky, "../../assets/game/textures/Tinky.png" },
		{ ActiveHealth, "../../assets/game/textures/VidaActiva.png" },
		{ DisableHealth, "../../assets/game/textures/VidaInactiva.png" },
		{ Chancla, "../../assets/game/textures/Chancla.png" },
		{ Grapadora, "../../assets/game/textures/Grapadora.png" },
		{ Extintor, "../../assets/game/textures/Extintor.png" },
		{ Piedra, "../../assets/game/textures/Piedra.png" },
		{ Pelota, "../../assets/game/textures/PelotaSaltarina.png" },
		{ Mancuerna, "../../assets/game/textures/Mancuerna.png" },
		{ Hands, "../../assets/game/textures/hands.png" },
		{ PinkTinky, "../../assets/game/textures/PinkTinky.png"},
		{ TSet_Kenney1bit , "../../assets/game/tilemaps/modded_colored.png"},
		{ TSet_Dungeon , "../../assets/game/tilemaps/dungeon_ts.png"}
};

vector<Resources::TextMsgInfo> Resources::messages_ {
		//Mensajes predeterminados {nombre_en_enum, texto, color, fuente}. Ejemplo abajo
		//{ HelloWorld, "Hello World", { COLOR(0xaaffffff) }, ARIAL16 }
		
};

vector<Resources::MusicInfo> Resources::musics_ {
		//M�sica {nombre_en_enum, ruta}
		{ MainTheme , "../../assets/game/sound/mainTheme.mp3" },
		{Reveal, "../../assets/game/sound/gotem.mp3"}
};

vector<Resources::SoundInfo> Resources::sounds_ {
		//Efectos de sonido {nombre_en_enum, ruta}. Ejemplo abajo
		//{ Shoot, "../assets/game/sound/shoot.mp3" },
};

map<std::string, Resources::TextureId> Resources::tilesetTag_{
	{"modded_colored",TextureId::TSet_Kenney1bit},
	{"dungeon_ts",TextureId::TSet_Dungeon}
};