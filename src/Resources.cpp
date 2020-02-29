#include "Resources.h"
#include "SDL_Macros.h"

vector<Resources::FontInfo> Resources::fonts_ {
		//Fuentes {nombre_en_enum, ruta, tamaño}
		{NES_Chimera, "resources/fonts/NES-Chimera.ttf", 38}
};

vector<Resources::ImageInfo> Resources::images_ {
		//Imágenes {nombre_en_enum, ruta}
		{ Tinky, "resources/textures/Tinky.png" }
};

vector<Resources::TextMsgInfo> Resources::messages_ {
		//Mensajes predeterminados {nombre_en_enum, texto, color, fuente}. Ejemplo abajo
		//{ HelloWorld, "Hello World", { COLOR(0xaaffffff) }, ARIAL16 }
		
};

vector<Resources::MusicInfo> Resources::musics_ {
		//Música {nombre_en_enum, ruta}
		{ MainTheme, "resources/sound/mainTheme.mp3" }
};

vector<Resources::SoundInfo> Resources::sounds_ {
		//Efectos de sonido {nombre_en_enum, ruta}. Ejemplo abajo
		//{ Shoot, "resources/sound/shoot.mp3" },
};

