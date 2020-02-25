#include "SDL.h"
#include "box2d.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

//puede meterse en el gameManager o un wrapper de ventana con mas funcionalidades
// crea ventana y renderer
void createWindow() {

}

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("PCE",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		600,400,
		SDL_WINDOW_SHOWN);

	//descomentar para depurar
	//while (true) {};
	return 0;
}