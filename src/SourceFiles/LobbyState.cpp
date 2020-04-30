#include "LobbyState.h"
#include "checkML.h"
#include "Resources.h"

LobbyState::~LobbyState()
{
	for (PlayerLobbyInfo p : joinedPlayers_) {
		delete p.inputBinder;
	}
}

void LobbyState::init()
{
	ih_ = SDL_Game::instance()->getInputHandler();
	for (int i = 0; i < maxPlayers_; i++) {
		joinedGamepads_[i] = false;
	}
	joinedKb_[1] = joinedKb_[2] = false;
	joinedMouse_ = false;

	playerTexture_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::TextureId::Body);
	voidTexture_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::TextureId::SpaceSuit);

	verticalIniPoint_ = CONST(int, "WINDOW_HEIGHT") / 2 - playerTexture_->getHeight() / 2;
	horizontalIniPoint_ = CONST(int, "WINDOW_WIDTH") / 2 - (maxPlayers_ * (playerTexture_->getWidth() + CONST(int, "LOBBY_OFFSET_X")) / 2);
	horizontalOffset_ = playerTexture_->getWidth() + CONST(int, "LOBBY_OFFSET_X");
	playerIdVerticalOffset_ = playerTexture_->getWidth() + CONST(int, "LOBBY_PLAYERID_OFFSET_Y");
}

void LobbyState::handleInput()
{
	GameState::handleInput();
	//comprueba si alguno de los mandos conectados
	//sin asignar se quiere unir o salir
	for (int i = 0; ih_->getNumControllers() && i < maxPlayers_; i++)
	{
		//Si se quiere unir
		if (!joinedGamepads_[i]) {
			if (ih_->isButtonDown(i, SDL_CONTROLLER_BUTTON_A)) {
				joinedGamepads_[i] = true;
				int newId = joinedPlayers_.size();
				joinedPlayers_.push_back(PlayerLobbyInfo(newId, new ControllerBinder(i)));
				joinedPlayers_[newId].ctrlId = i;
				// crea un nuevo jugador con id newId
				// lo mete en joinedPlayers
			}
		}
		//Si quiere salir
		else {
			if (ih_->isButtonDown(i, SDL_CONTROLLER_BUTTON_B)) {
				ctrlPlayerOut(i);
			}
		}
	}

	//comprueba si se puede unir un pureKeyboardPeasant
	if (!joinedMouse_)
	{
		if (!joinedKb_[0]) {
			// comprueba si se quiere unir un pureKeyboardPeasant (tonto)
			if (ih_->isKeyDown(SDLK_w))
			{
				joinedKb_[0] = true;
				int newId = joinedPlayers_.size();
				joinedPlayers_.push_back(PlayerLobbyInfo(newId, new PureKeyboardBinder(1)));
				joinedPlayers_[newId].kbId = 1;
			}
		}
		else if (ih_->isKeyDown(SDLK_ESCAPE)) {
			kbPlayerOut(0);
		}

		if (!joinedKb_[1]) {
			if (ih_->isKeyDown(SDLK_i))
			{
				joinedKb_[1] = true;
				int newId = joinedPlayers_.size();
				joinedPlayers_.push_back(PlayerLobbyInfo(newId, new PureKeyboardBinder(2)));
				joinedPlayers_[newId].kbId = 2;
			}
		}
		else if (ih_->isKeyDown(SDLK_7)) {
			kbPlayerOut(1);
		}
	}
	else {
		//comprueba si se quiere unir un jugador de teclado y raton
	}
}

void LobbyState::update()
{
	clear2();
	for (auto player : joinedPlayers_)
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
			cout << "unknown controller " << endl;
		}
	}
}

void LobbyState::render() {
	int i = 0;
	for (PlayerLobbyInfo& const player : joinedPlayers_) {
		renderPlayerLobbyInfo(&player, i);
		i++;
	}
	for (; i < maxPlayers_; i++)
		renderPlayerLobbyInfo(nullptr, i);
}


void LobbyState::renderPlayerLobbyInfo(PlayerLobbyInfo* playerInfo, int index) {

	SDL_Rect destRect = {
		horizontalIniPoint_ + index * horizontalOffset_,
		verticalIniPoint_,
		playerTexture_->getWidth(),
		playerTexture_->getHeight()
	};

	Texture* aux = ((playerInfo != nullptr) ? playerTexture_ : voidTexture_);
	aux->render(destRect);
	if (playerInfo != nullptr) {
		destRect.y += playerTexture_->getHeight() + playerIdVerticalOffset_;
		destRect.w /= 3; destRect.h /= 3;
		string playerNum = to_string(playerInfo->id);
		Texture playerNumTexture(SDL_Game::instance()->getRenderer(), playerNum,
			SDL_Game::instance()->getFontMngr()->getFont(Resources::NES_Chimera), { COLOR(0xffffffff) });
		playerNumTexture.render(destRect);
	}
}

void LobbyState::playerOut(std::vector<PlayerLobbyInfo>::iterator it)
{
	//it es el jugador que se quiere salir
	it = joinedPlayers_.erase(it);
	delete it->inputBinder;
	//it ahora apunta al siguiente elemento
	//ajustamos el resto de ids en funcion
	while (it != joinedPlayers_.end()) {
		it->id--;
		++it;
	}
}

void LobbyState::kbPlayerOut(int index) {
	joinedKb_[index] = false;
	auto it = joinedPlayers_.begin();
	while (it != joinedPlayers_.end() && it->kbId != index) ++it;
	playerOut(it);
}

void LobbyState::ctrlPlayerOut(int index) {
	joinedGamepads_[index] = false;
	auto it = joinedPlayers_.begin();
	while (it != joinedPlayers_.end() && it->ctrlId != index) ++it;
	playerOut(it);
}

void LobbyState::clear2()
{
	system("cls");
}