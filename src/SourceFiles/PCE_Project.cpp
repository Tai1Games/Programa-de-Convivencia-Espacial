#include "SDL_Game.h"
#include "checkML.h"
#include "json.hpp"
#include "SDL_net.h"
#include <fstream>
#include <iomanip>

using json = nlohmann::json;


//puede meterse en el gameManager o un wrapper de ventana con mas funcionalidades
// crea ventana y renderer
void createWindow() {

}

int main(int argc, char* argv[]) {
	//Colocar antes del constructor de SDL_Game
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	/*if (SDLNet_Init() < 0) {
		throw;
	}

	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, nullptr, 2000) < 0) {
		throw;
	}
	TCPsocket masterSocket = SDLNet_TCP_Open(&ip);

	if (!masterSocket) {
		throw;
	}*/

	cout << sizeof(SpritePacket) << endl;

	SDL_Game::instance()->start();

	//descomentar para depurar
	//while (true) {};
	return 0;
}
