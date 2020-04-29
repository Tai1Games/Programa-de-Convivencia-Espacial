#include "LobbyState.h"

void LobbyState::init()
{
	ih_ = SDL_Game::instance()->getInputHandler();
}

void LobbyState::handleInput()
{
	//comprueba si alguno de los mandos conectados
	//sin asignar se quiere unir o salir
	for (int i = 0; ih_->getNumControllers() && i<4; i++)
	{
		//Si se quiere unir
		if(!joinedGamepads_[i]){
			if(ih_->isButtonJustDown(i,SDL_CONTROLLER_BUTTON_A)){
				joinedGamepads_[i] = true;
				int newId = joinedPlayers_.size();
				joinedPlayers_.push_back(PlayerInfo(newId, new ControllerBinder(i)));
				joinedPlayers_[newId].ctrlId = i;
				// crea un nuevo jugador con id newId
				// lo mete en joinedPlayers
			}
		}
		//Si quiere salir
		else{
			if(ih_->isButtonJustDown(i,SDL_CONTROLLER_BUTTON_B)){
				joinedGamepads_[i] = false;
				int j = 0;
				while (j < joinedPlayers_.size() && joinedPlayers_[j].ctrlId != i)
				{
					j++;
				}
				//joinedPlayers_[j] es el jugador que se quiere salir
				//cambiar el id de los siguientes
			}
		}
	}
}
