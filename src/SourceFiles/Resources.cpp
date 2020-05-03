#include "Resources.h"
#include "SDL_Macros.h"

vector<Resources::FontInfo> Resources::fonts_{
	//Fuentes {nombre_en_enum, ruta, tama�o}
	{NES_Chimera , resourcesPath+"fonts/NES-Chimera.ttf", 38},
	{Digits_Font , resourcesPath+"fonts/Digits_Font.ttf", 38}
};

vector<Resources::ImageInfo> Resources::images_{
	//Imágenes {nombre_en_enum, ruta}

	// room backgrounds
	{ BoilerRoom,resourcesPath + "textures/Background_BoilerRoom.png"},
	{ GymRoom,resourcesPath + "textures/Background_gym.png"},
	{ LivingRoom,resourcesPath + "textures/Background_LivingRoom.png"},
	{ TutorialRoom,resourcesPath + "textures/Background_TutorialRoom.png"},
	{ GardenRoom,resourcesPath + "textures/Background_garden.png"},

	// UI
	{ ActiveHealth, resourcesPath + "textures/VidaActiva.png" },
	{ DisableHealth, resourcesPath + "textures/VidaInactiva.png" },

	{ Slider, resourcesPath + "textures/Slider.png"},
	{ SliderControl, resourcesPath + "textures/SliderControl.png"},

	{ CanvasTimerBackground, resourcesPath + "textures/canvasTimerBackground.png"},
	{ CoinUI, resourcesPath + "textures/MonedaUI.png"},
	{ SkullUI, resourcesPath + "textures/SkullUI.png"},
	{ SuddenDeathCapitalismModeText, resourcesPath + "textures/suddenDeathCapitalismModeText.png"},
	{ SuddenDeathTimeModeText, resourcesPath + "textures/suddenDeathTimeModeText.png"},

	{ EmptyProgressBar, resourcesPath + "textures/EmptyProgressBar.png"},
	{ EmptyProgressBar2, resourcesPath + "textures/EmptyProgressBar2.png"},
	{ ProgressBar, resourcesPath + "textures/ProgressBar.png"},
	{ ProgressBar2, resourcesPath + "textures/ProgressBar2.png"},
	{ MouseIcon, resourcesPath + "textures/mouse_icon.png"},
	{ KeyboardIcon, resourcesPath + "textures/keyboard_icon.png"},
	{ ControllerIcon, resourcesPath + "textures/controller_icon.png"},

	// Weapons and map items
	{ Ball, resourcesPath + "textures/PelotaSaltarina.png" },
	{ Extinguisher, resourcesPath + "textures/Extintor.png" },
	{ Fireball,resourcesPath + "textures/fireball_placeholder.png"},
	{ Mancuerna, resourcesPath + "textures/Mancuerna.png" },
	{ Slipper, resourcesPath + "textures/Chancla.png" },
	{ Stapler, resourcesPath + "textures/Grapadora.png" },
	{ Stone, resourcesPath + "textures/Piedra.png" },
	{ Tomato, resourcesPath + "textures/Tomato-Sheet.png"},
	{ TomatoRing, resourcesPath + "textures/TomatoRing.png"},

	// Players
	{ Body, resourcesPath + "textures/bodyNeutral.png" },
	{ Hands, resourcesPath + "textures/hands.png" },
	{ ImpulseArrow, resourcesPath + "textures/FlechaImpulso.png"},
	{ ImpulseBackground, resourcesPath + "textures/ImpulsoBackground.png"},
	{ SpaceSuit, resourcesPath + "textures/PinkTinky.png"},	// dead body

	// Map elements
	{ Smoke, resourcesPath + "textures/SmokeParticles-Sheet.png" },
	{ Boiler,resourcesPath + "textures/CalderaPro.png"},
	{ DecreasingFreqButton,resourcesPath + "textures/DecreasingFrecButton.png"},
	{ IncreasingFreqButton,resourcesPath + "textures/InreasingFrecButton.png"},
	{ PadSpriteSheet,resourcesPath + "textures/ColchonetaSpriteSheet.png" },
	{ PipeHor,resourcesPath + "textures/TuberiasHor.png"},
	{ PipeVer,resourcesPath + "textures/TuberiasVer.png"},
	{ Treadmill , resourcesPath + "textures/Treadmill.png"},
	{ TreadmillSpriteSheet , resourcesPath + "textures/TreadmillSpriteSheet.png"},
	{ CarnivorousPlant , resourcesPath + "textures/PlantaCarnivora.png"},
	{ IncreasingFreqButton,resourcesPath + "textures/InreasingFrecButton.png"},
	{ DecreasingFreqButton,resourcesPath + "textures/DecreasingFrecButton.png"},
	{ PipeHor,resourcesPath + "textures/TuberiasHor.png"},
	{ PipeVer,resourcesPath + "textures/TuberiasVer.png"},
	{TreadmillPanel, resourcesPath + "textures/TreadmillPanel.png"},

	// Gamemode specific elements
	{ Coin, resourcesPath + "textures/Moneda.png" },
	{ Router,resourcesPath + "textures/Router2.png" },
	{ RoombaSpriteSheet, resourcesPath + "textures/Roomba.png"},
	{ Remote, resourcesPath + "textures/Mando.png"},

	// miscelánea
	{ Debug, resourcesPath + "textures/debug.png" },
	{ Negro ,resourcesPath + "textures/Negro.png"},
	{ Transparent ,resourcesPath + "textures/transparent.png"},
	{ Tinky, resourcesPath + "textures/Tinky.png" }
};

vector<Resources::TextMsgInfo> Resources::messages_{
	//Mensajes predeterminados {nombre_en_enum, texto, color, fuente}. Ejemplo abajo
	//{ HelloWorld, "Hello World", { COLOR(0xaaffffff) }, ARIAL16 }
	{ PauseText, "PAUSA", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ ResumeText, "Reanudar", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ SoundText, "Sonido", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ ExitText, "Salir", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },

	//Menu Provisional
	//gamemodes
	{ Capitalism, "Capitalism", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ Controller, "Controller", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ Stocks, "Stocks", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ WiFight, "WiFight", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ Timed, "Timed", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ Tutorial, "Tutorial", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	//exit
	{ Exit, "Exit Game", { COLOR(0xff0000ff) }, FontId::NES_Chimera },
	//maps
	{ LivingRoomText, "Living Room", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ BoilerRoomText, "Boiler Room", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ GymRoomText, "Gym Room", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	//players
	{ OnePlayer, "1 Player", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ TwoPlayers, "2 Players", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ ThreePlayers, "3 Players", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ FourPlayers, "4 Players", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },

	//Tutorial
	{ Completed, "Completed: ", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ Slash, "/", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ Zero, "0", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ One, "1", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ Two, "2", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ Three, "3", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ Four, "4", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ MoveTutorial, "Welcome to PCE! To move, hold and release the A button while pointing anywhere with the left joystick. The longer you hold, the greater the impulse! Everyone boost once to continue!", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ HoldTutorial, "It's hard to give yourself a good boost out of thin air, so press the left trigger to hold on a object, like a wall. This will stop you and let you build a greater impulse. To let loose, simply release the button. Everyone hold on to something to continue!", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ GrabTutorial, "Weapons will allow you to harm your oponents and sometimes even improve your mobility. Pick up weapons with the Y button. Everyone pick a weapon to continue!", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ ActionTutorial, "Some weapons can be activated with the X button, which will make them shoot, attack at melee range or something else entirely. Everyone use a weapon to continue!", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ ThrowTutorial, "All weapons can be thrown with the Y button, which can be used to cover great distances quickly. Everyone throw a weapon to continue!", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ DeathTutorial, "In many Game Modes enough damage will kill you, which will disarm you and make you respawn. You'll leave a body behind which can be held on to. Everyone die once to finish the tutorial!", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ TutorialEnd, "Congratulations! You know all the basics of PCE. Play around if you want or press Start to go to the menu and choose Salir to exit.", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
};

vector<Resources::MusicInfo> Resources::musics_{
	//Música {nombre_en_enum, ruta}
	{ MainMenuMusic , resourcesPath + "sound/mainMenu.mp3" },
	{ EntranceMusic , resourcesPath + "sound/entrance.mp3" },
	{ LivingRoomMusic , resourcesPath + "sound/livingRoom.mp3" },
	{ GymMusic , resourcesPath + "sound/gym.mp3" },
	{ BoilerRoomMusic, resourcesPath + "sound/boilerRoom.mp3" }
};

vector<Resources::SoundInfo> Resources::sounds_{
	//Efectos de sonido {nombre_en_enum, ruta}. Ejemplo abajo
	//{ Shoot, "../assets/game/sound/shoot.mp3" },
};

map<std::string, Resources::TextureId> Resources::tilesetTag_{

};
