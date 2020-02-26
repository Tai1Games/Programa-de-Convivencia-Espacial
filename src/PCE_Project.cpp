#include "SDL_Game.h"
#include "json/single_include/nlohmann/json.hpp"
#include <fstream>
#include <iomanip>

using json = nlohmann::json;

//puede meterse en el gameManager o un wrapper de ventana con mas funcionalidades
// crea ventana y renderer
void createWindow() {

}

int main(int argc, char* argv[]) {
	json windowConfig;
	windowConfig["width"] = 1280;
	windowConfig["heigth"] = 720;
	windowConfig["name"] = "El loco juego de Tai1 Games";

	std::ofstream out("windowConfig.json");
	out << std::setw(4) << windowConfig << std::endl;
	out.close();

	SDL_Game PCE = SDL_Game();


	//descomentar para depurar
	//while (true) {};
	return 0;
}