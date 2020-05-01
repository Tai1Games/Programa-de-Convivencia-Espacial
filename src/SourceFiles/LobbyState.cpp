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
	joinedKb_[0] = false;  joinedKb_[1] = false;
	joinedMouse_ = false;

	playerTexture_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::TextureId::Body);
	voidTexture_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::TextureId::SpaceSuit);
	ctrlTexture_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::TextureId::ControllerIcon);
	kbTexture_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::TextureId::KeyboardIcon);
	mouseTexture_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::TextureId::MouseIcon);


	verticalIniPoint_ = CONST(int, "WINDOW_HEIGHT") / 2 - playerTexture_->getHeight() / 2;
	horizontalIniPoint_ = CONST(int, "WINDOW_WIDTH") / 2 - (maxPlayers_ * (playerTexture_->getWidth() + CONST(int, "LOBBY_OFFSET_X")) / 2);
	horizontalOffset_ = playerTexture_->getWidth() + CONST(int, "LOBBY_OFFSET_X");
	playerIdVerticalOffset_ = playerTexture_->getWidth() + CONST(int, "LOBBY_PLAYERID_OFFSET_Y");
	iconHorizontalOffset_ = CONST(int, "LOBBY_ICON_OFFSET");
}

void LobbyState::handleInput()
{
	GameState::handleInput();
	handleJoinLeave();
	handleJoinedPlayers();
}

void LobbyState::update()
{
	outDebug();
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

bool LobbyState::ready()
{
	if (joinedPlayers_.size() > 0) {
		auto it = joinedPlayers_.begin();
		while (it != joinedPlayers_.end() && it->ready) ++it;
		//si hemos salido del vector, todos estan ready
		return it == joinedPlayers_.end();
	}
	return false;
}

void LobbyState::outDebug()
{
	clear();
	for (auto& player : joinedPlayers_)
	{
		cout << "Player " << player.id << " using ";
		if (player.ctrlId != -1) {
			cout << "controller " << player.ctrlId;
		}
		else if (player.kbId != -1) {
			cout << "pureKeyboard " << player.kbId;
		}
		else if (player.kbmId != -1) {
			cout << "KBM " << player.kbmId;
		}
		else {
			cout << "unknown controller ";
		}
		cout << " is ";
		if (!player.ready) cout << "NOT ";
		cout << "ready,		PlayerSkin: " << player.playerSkin;

		cout << endl;
	}
	if (ready())
		cout << "LETS A GOOOOOOO" << endl;
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
		destRect.x += iconHorizontalOffset_;
		if (playerInfo->ctrlId != -1) {
			ctrlTexture_->render(destRect);
		}
		else if (playerInfo->kbId != -1) {
			kbTexture_->render(destRect);			
		}
		else if (playerInfo->kbmId != -1) {
			mouseTexture_->render(destRect);
		}
	}
}

void LobbyState::playerOut(std::vector<PlayerLobbyInfo>::iterator it)
{
	if (it != joinedPlayers_.end())
	{
		//it es el jugador que se quiere salir
		delete it->inputBinder;
		it = joinedPlayers_.erase(it);
		//it ahora apunta al siguiente elemento
		//ajustamos el resto de ids en funcion
		while (it != joinedPlayers_.end()) {
			it->id--;
			++it;
		}
	}
}

void LobbyState::kbPlayerOut(int index) {
	joinedKb_[index] = false;
	auto it = joinedPlayers_.begin();
	while (it != joinedPlayers_.end() && it->kbId != index) ++it;
	playerOut(it);
}

void LobbyState::mousePlayerOut() {
	joinedMouse_ = false;
	auto it = joinedPlayers_.begin();
	while (it != joinedPlayers_.end() && it->kbmId != 0) ++it;
	playerOut(it);
}

void LobbyState::changeMouseToKb()
{
	joinedMouse_ = false;
	joinedKb_[0] = true;
	auto it = joinedPlayers_.begin();
	while (it->kbmId != 0 && it != joinedPlayers_.end())++it;
	it->kbId = 0;
	it->kbmId = -1;
	delete it->inputBinder;
	it->inputBinder = new PureKeyboardBinder(1);
}

void LobbyState::changeKbToMouse()
{
	joinedKb_[0] = false;
	joinedMouse_ = true;
	auto it = joinedPlayers_.begin();
	while (it->kbId != 0 && it != joinedPlayers_.end())++it;
	it->kbId = -1;
	it->kbmId = 0;
	delete it->inputBinder;
	it->inputBinder = new MouseKeyboardBinder(nullptr, 1);
}

void LobbyState::ctrlPlayerOut(int index) {
	joinedGamepads_[index] = false;
	auto it = joinedPlayers_.begin();
	while (it != joinedPlayers_.end() && it->ctrlId != index) ++it;
	playerOut(it);
}

void LobbyState::handleJoinLeave() {
	//comprueba si alguno de los mandos conectados
	//sin asignar se quiere unir o salir
	for (int i = 0; ih_->getNumControllers() && i < maxPlayers_; i++)
	{
		//Si se quiere unir
		if (!joinedGamepads_[i]) {
			if (ih_->isButtonDown(i, ctrJoinButton)) {
				joinedGamepads_[i] = true;
				int newId = joinedPlayers_.size();
				joinedPlayers_.push_back(PlayerLobbyInfo(newId, new ControllerBinder(i)));
				joinedPlayers_[newId].ctrlId = i;
				joinedPlayers_[newId].binderType = BinderType::ControllerB;
				// crea un nuevo jugador con id newId
				// lo mete en joinedPlayers
			}
		}
		////Si quiere salir
		//else {
		//	if (ih_->isButtonDown(i, ctrOutButton)) {
		//		ctrlPlayerOut(i);
		//	}
		//}
	}

	//comprueba si se puede unir un pureKeyboardPeasant
	if (!joinedMouse_)
	{
		for (int kb = 0; kb < maxKbPlayers_; kb++)
		{
			if (!joinedKb_[kb]) {
				// comprueba si se quiere unir un pureKeyboardPeasant (tonto)
				if (ih_->isKeyDown(joinKbKeys_[kb]))
				{
					joinedKb_[kb] = true;
					int newId = joinedPlayers_.size();
					joinedPlayers_.push_back(PlayerLobbyInfo(newId, new PureKeyboardBinder(kb + 1)));
					joinedPlayers_[newId].kbId = kb;
					joinedPlayers_[newId].binderType = KeyboardB;
				}
			}
			//else if (ih_->isKeyDown(dcKbKeys_[kb])) {
			//	kbPlayerOut(kb);
			//}
		}
		//comprueba si se quiere unir un jugador de teclado y raton
		if (ih_->isMouseButtonJustDown(InputHandler::LEFT))
		{
			int newId = joinedPlayers_.size();
			//comprobamos si hay un PureKeyboard que sobreescribir
			if (joinedKb_[0]) {
				// convierte al jugador 1
				changeKbToMouse();
				// saca al jugador 2
				if (joinedKb_[1])
					kbPlayerOut(1);
			}
			else {
				joinedMouse_ = true;
				joinedPlayers_.push_back(PlayerLobbyInfo(newId, new MouseKeyboardBinder(nullptr, 1)));
				joinedPlayers_[newId].kbmId = 0;
				joinedPlayers_[newId].binderType =MouseB;
			}
		}
	}
	else {
		// jugador de mouse se quiere convertir al patetismo
		if (ih_->isMouseButtonJustDown(InputHandler::RIGHT))
			changeMouseToKb();
		// jugador de mouse se quiere salir
		else if (ih_->isKeyDown(dcKbKeys_[0])) {}
			//mousePlayerOut();
		else if (!joinedKb_[1]) {
			// comprueba si se quiere unir un pureKeyboardPeasant (tonto)
			if (ih_->isKeyDown(joinKbKeys_[1])) {
				// convierte jugador de teclado en peasant
				changeMouseToKb();

				// se une jugador 2
				joinedKb_[1] = true;
				int newId = joinedPlayers_.size();
				joinedPlayers_.push_back(PlayerLobbyInfo(newId, new PureKeyboardBinder(2)));
				joinedPlayers_[newId].kbId = 1;
			}
		}
	}
}

void LobbyState::handleJoinedPlayers(){
	for(auto& player: joinedPlayers_){
		//cambiamos de skin
		if(player.inputBinder->menuMove(Dir::Left)){
			player.playerSkin -= 1;
			if(player.playerSkin < 0){
				player.playerSkin = MAX_SKINS_PLACEHOLDER-1;
			}
		}
		else if(player.inputBinder->menuMove(Dir::Right)){
			player.playerSkin = (++player.playerSkin) % (MAX_SKINS_PLACEHOLDER);
		}
		else if (player.inputBinder->menuForward()) {
			player.ready = true;
		}
		else if (player.inputBinder->menuBack()) {
			if(player.ready)
				player.ready = false;
			//desconexion mediante boton back
			else {
				switch (player.binderType)
				{
				case BinderType::ControllerB: {ctrlPlayerOut(player.ctrlId); }break;
				case BinderType::KeyboardB: {kbPlayerOut(player.kbId); } break;
				case BinderType::MouseB: {mousePlayerOut(); }break;
				default:
					break;
				}
			}
		}
	}
}

void LobbyState::clear2()
{
	system("cls");
}