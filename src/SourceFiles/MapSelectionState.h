#pragma once
#include "GameState.h"
#include "checkML.h"
#include "Entity.h"
#include "Resources.h"

enum Maps {
	LivingRoom = 0,
	Boiler,
	Gym,
	Garden
};

enum coor {
	x = 0,
	y,
	gamemodeScreen
};

class InputBinder;
class UIViewer;
class MapSelectionState :
	public GameState
{
private:

	int menuPointer_ = 0; //En que screen del menu esta (1 escogiendo mapa, 0 escogiendo modo)
	int pointers_[3] = { 0,0, 0 }; //Que seleccion dentro de la screen esta (las dos primeras son coordenadas de la imagen)
	bool holdingY_ = false;
	bool holdingX_ = false;
	int ownerPlayerID_ = 0;
	InputBinder* ownerPlayerBinder_ = nullptr;

	vector<pair<GamemodeID, string>>* roundsVector_ = new vector<pair<GamemodeID, string>>();  //vector de rondas

	UIViewer* mapSelCursor_ = nullptr;
	UIViewer* gamemodeCursor_ = nullptr;

	int maxNumberOfRounds_ = 5;

	std::vector<Entity*> imagesMaps_;
	std::vector<b2Vec2> coordsImages_;
	std::vector<pair<Entity*, GamemodeID>> iconsMaps_[4];

	std::vector<Entity*> iconsGamemodes_;
	std::vector<Entity*> textsGamemodes_;

	Texture* backgroundTex_ = nullptr;
	Entity* choseMapText_;
	Entity* choseModeText_;
	Entity* pressEnterText_;

#pragma region constantes de tamanos


	b2Vec2 gmOffsetText_;
	b2Vec2 gmOffsetIcons_;
	b2Vec2 gmMarginText_;

	float gmIconsSize_;

	int gmTextSize_;
	float gmTextScale_;

	b2Vec2 mapCursorOffset_;
	float mapScale_;
	int mapMargin_;
	int mapIconMargin_;
	b2Vec2 mapIconsOffset_;
	int mapIconsScale_;

	b2Vec2 sizeImg;
	b2Vec2 sizeScreen;

#pragma endregion constantes de tamanos



	std::map<int, string> maps_ = { //anadir aqui los mapas que se vayan haciendo, tutorial no
		{ 0, "LivingRoom"},
		{ 1, "BoilerRoom"},
		{ 2, "GymRoom"},
		{ 3, "GardenRoom"}
	};

	std::map<int, int> texturesMaps_ = { //anadir aqui los mapas que se vayan haciendo, tutorial no
	{ 0, Resources::LivingRoom},
	{ 1, Resources::BoilerRoom},
	{ 2, Resources::GymRoom},
	{ 3, Resources::GardenRoom}
	};

	std::map<int, int> texturesTexts_ = {
	{ 0, Resources::Capitalism},
	{ 1, Resources::Controller},
	{ 2, Resources::Stocks},
	{ 3, Resources::WiFight},
	{ 4, Resources::Timed}
	};

	//hay dos por que va uno a cada lado
	std::map<int, int> texturesIcons_ = {
	{ 0, Resources::CapitalismIcon},
	{ 1, Resources::ControllerModeIcon},
	{ 2, Resources::StocksIcon},
	{ 3, Resources::WiFightIcon},
	{ 4, Resources::TimedIcon},
	};

	void updatePointer(int n, int coor);
	void loadConst();
	void createImages();
	void createTexts();
	void createIcons();
	void updateMenu();
	void addRound(GamemodeID gMode, string map);
	void removeRound(string map);

public:
	MapSelectionState(int playerID) : GameState(), ownerPlayerID_(playerID) {};
	virtual ~MapSelectionState() {
		delete roundsVector_;
	};

	virtual void init() override;
	virtual void onLoaded() override;
	virtual void render() override;
	virtual void handleInput() override;
};
