#include "LobbyState.h"
#include "checkML.h"

void LobbyState::init()
{
	ih_ = SDL_Game::instance()->getInputHandler();
	for (int i = 0; i < 4; i++) {
		joinedGamepads_[i] = false;
	}
}

void LobbyState::handleInput()
{
	GameState::handleInput();
	//comprueba si alguno de los mandos conectados
	//sin asignar se quiere unir o salir
	for (int i = 0; ih_->getNumControllers() && i<4; i++)
	{
		//Si se quiere unir
		if(!joinedGamepads_[i]){
			if(ih_->isButtonDown(i,SDL_CONTROLLER_BUTTON_A)){
				joinedGamepads_[i] = true;
				int newId = joinedPlayers_.size();
				joinedPlayers_.push_back(PlayerLobbyInfo(newId, new ControllerBinder(i)));
				joinedPlayers_[newId].ctrlId = i;
				// crea un nuevo jugador con id newId
				// lo mete en joinedPlayers
			}
		}
		//Si quiere salir
		else{
			if(ih_->isButtonDown(i,SDL_CONTROLLER_BUTTON_B)){
				joinedGamepads_[i] = false;
				int j = 0;
				auto it = joinedPlayers_.begin();
				while (it != joinedPlayers_.end() && it->ctrlId != i)
				{
					it++;
				}
				//joinedPlayers_[j] es el jugador que se quiere salir
				it = joinedPlayers_.erase(it);
				//it ahora apunta al siguiente elemento
				//ajustamos el resto de ids en funcion
				while (it != joinedPlayers_.end()) {
					it->id--;
					it++;
				}
			}
		}
	}
}

void LobbyState::update()
{
	clear();
	for (auto player: joinedPlayers_)
	{
		cout << "Player " << player.id << " using ";
		if (player.ctrlId != -1) {
			cout << "controller " << player.ctrlId << endl;
		}
		else if (player.kbId != -1) {
			cout << "pureKeyboard " << player.kbId << endl;
		}
		else if (player.kbmId != -1) {
			cout << "KBM " << player.kbmId << endl;
		}
		else {
			cout << "unkown controller " << endl;
		}
	}
}
