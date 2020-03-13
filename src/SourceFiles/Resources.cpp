#include "Resources.h"
#include "SDL_Macros.h"

vector<Resources::FontInfo> Resources::fonts_ {
		//Fuentes {nombre_en_enum, ruta, tamaño}
		{NES_Chimera, "../../assets/game/fonts/NES-Chimera.ttf", 38}
};

vector<Resources::ImageInfo> Resources::images_ {
		//Imágenes {nombre_en_enum, ruta}
		{ Debug, "../../assets/game/textures/debug.png" },
		{ Tinky, "../../assets/game/textures/Tinky.png" },
		{ ActiveHealth, "../../assets/game/textures/VidaActiva.png" },
		{ DisableHealth, "../../assets/game/textures/VidaInactiva.png" },
		{ DebugTilemap , "../../assets/game/tilemaps/modded_colored.png"}
};

vector<Resources::TextMsgInfo> Resources::messages_ {
		//Mensajes predeterminados {nombre_en_enum, texto, color, fuente}. Ejemplo abajo
		//{ HelloWorld, "Hello World", { COLOR(0xaaffffff) }, ARIAL16 }
		
};

vector<Resources::MusicInfo> Resources::musics_ {
		//Música {nombre_en_enum, ruta}
		{ MainTheme, "../../assets/game/sound/mainTheme.mp3" }
};

vector<Resources::SoundInfo> Resources::sounds_ {
		//Efectos de sonido {nombre_en_enum, ruta}. Ejemplo abajo
		//{ Shoot, "../assets/game/sound/shoot.mp3" },
};

