#include "Resources.h"
#include "SDL_Macros.h"

vector<Resources::FontInfo> Resources::fonts_{
	//Fuentes {nombre_en_enum, ruta, tama�o}
	{NES_Chimera , resourcesPath + "fonts/NES-Chimera.ttf", 38},
	{Digits_Font , resourcesPath + "fonts/Digits_Font.ttf", 38}
};

vector<Resources::ImageInfo> Resources::images_{
	//Imágenes {nombre_en_enum, ruta}

	// room backgrounds
	{ BoilerRoom,resourcesPath + "textures/Background_BoilerRoom.png"},
	{ GymRoom,resourcesPath + "textures/Background_gym.png"},
	{ LivingRoom,resourcesPath + "textures/Background_LivingRoom.png"},
	{ RocketRoom ,resourcesPath + "textures/Background_RocketRoom.png"},
	{ TutorialRoom,resourcesPath + "textures/Background_TutorialRoom.png"},
	{ GardenRoom,resourcesPath + "textures/Background_garden.png"},
	{ MenuRoom, resourcesPath + "textures/Background_Menu.png"},
	{ CreditsRoom, resourcesPath + "textures/CreditsRoom.png"},
	{ SpaceBackground, resourcesPath + "textures/Background_SpaceMenus.png"},

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

	{ Rocket, resourcesPath + "textures/Rocket.png"},
	{ SpaceStation, resourcesPath + "textures/SpaceStation.png"},
	{ Token, resourcesPath + "textures/Marker.png"},
	{ RocketSpriteSheet,resourcesPath + "textures/rocketSpriteSheet.png", 8, 1},
	{ PlayerPlaceholder,resourcesPath + "textures/playerPlaceholder.png"},

	{Ready , resourcesPath + "textures/ready.png"},
	{PressReady , resourcesPath + "textures/pressready.png"},

	// Weapons and map items
	{ Ball, resourcesPath + "textures/PelotaSaltarina.png" },
	{ Extinguisher, resourcesPath + "textures/Extintor.png" },
	{ Fireball,resourcesPath + "textures/fireballSP.png", 6},
	{ Dumbbell, resourcesPath + "textures/Mancuerna.png" },
	{ Slipper, resourcesPath + "textures/Chancla.png" },
	{ Stapler, resourcesPath + "textures/Grapadora.png" },
	{ Stone, resourcesPath + "textures/Piedra.png" },
	{ Tomato, resourcesPath + "textures/Tomato-Sheet.png", 15},
	{ TomatoRing, resourcesPath + "textures/TomatoRing.png"},
	{ TreeTomato, resourcesPath + "textures/TreeTomato.png"},
	{ Banana, resourcesPath + "textures/Banana.png"},
	{ BananaSkin,resourcesPath + "textures/BananaSkin.png"},
	{ BananaNonSkin,resourcesPath + "textures/Banana!Skin.png"},
	{ Staple,resourcesPath + "textures/Staple.png"},
	{ Confetti,resourcesPath + "textures/ConfettiWeapon.png", 2},
	{ ConfettiParticles,resourcesPath + "textures/ConfettiParticles.png"},
	{ Lamp,resourcesPath + "textures/Lampara.png"},
	{ Table,resourcesPath + "textures/Mesa.png"},
	{ Sofa,resourcesPath + "textures/Sofa.png"},
	{ DeadBody,resourcesPath + "textures/cadaver.png"},

	// Players
	{ Body, resourcesPath + "textures/bodyNeutral.png" },
	{ PlayerAnimSheet, resourcesPath + "textures/playerAnim.png",19,10},
	{ Hands, resourcesPath + "textures/hands.png", 7, 11},
	{ ImpulseArrow, resourcesPath + "textures/FlechaImpulso.png"},
	{ ImpulseBackground, resourcesPath + "textures/ImpulsoBackground.png", 13},
	{ SpaceSuit, resourcesPath + "textures/PinkTinky.png"},	// dead body

	// Map elements
	{ Boiler,resourcesPath + "textures/Caldera.png", 16, 1},
	{ IncreasingFreqButton,resourcesPath + "textures/IncBoilerButtonDown.png", 3, 1},
	{ DecreasingFreqButton,resourcesPath + "textures/DecBoilerButtonDown.png", 3, 1},
	{ PadSpriteSheet,resourcesPath + "textures/ColchonetaSpriteSheet.png", 4},
	{ PipeHor,resourcesPath + "textures/TuberiasHor.png"},
	{ PipeVer,resourcesPath + "textures/TuberiasVer.png"},
	{ Treadmill , resourcesPath + "textures/Treadmill.png"},
	{ TreadmillPanel, resourcesPath + "textures/TreadmillPanel.png"},
	{ TreadmillSpriteSheet , resourcesPath + "textures/TreadmillSpriteSheet.png", 8},
	{ CarnivorousPlant , resourcesPath + "textures/PlantaCarnivora.png", 7, 1},
	{ TomatoTree, resourcesPath + "textures/TomatoTree.png"},
	{ BananaTree, resourcesPath + "textures/BananaTree.png"},
	{ TriggerButtonPlay , resourcesPath + "textures/PuertasMenu_Play.png", 13, 1},
	{ TriggerButtonExit , resourcesPath + "textures/PuertasMenu_Exit.png", 13, 1},
	{ TriggerButtonCredits , resourcesPath + "textures/PuertasMenu_Credits.png", 13, 1},
	{ TriggerButtonOptions , resourcesPath + "textures/PuertasMenu_Options.png", 13, 1},

	// Gamemode specific elements
	{ Coin, resourcesPath + "textures/Moneda.png" },
	{ Router,resourcesPath + "textures/Router2.png" },
	{ RoombaSpriteSheet, resourcesPath + "textures/Roomba.png", 5},
	{ Remote, resourcesPath + "textures/Mando.png"},

	// miscelánea
	{ Debug, resourcesPath + "textures/debug.png" },
	{ Negro ,resourcesPath + "textures/Negro.png"},
	{ Transparent ,resourcesPath + "textures/transparent.png"},
	{ Tinky, resourcesPath + "textures/Tinky.png" },

	// particles
	{ Smoke, resourcesPath + "textures/SmokeParticles-Sheet.png", 4},
	{ WiFiWave, resourcesPath + "textures/WiFiWave.png" },
	{ Foam, resourcesPath + "textures/foam_particles.png",4 },


	//badges
	{ badgeCapitalism,resourcesPath + "textures/MonedaUI.png" },
	{ badgeController,resourcesPath + "textures/Mando.png" },
	{ badgeStocks,resourcesPath + "textures/skullUI.png" },
	{ badgeWifi,resourcesPath + "textures/Router.png" },
	{ badgeTimed,resourcesPath + "textures/TreadmillPanel.png" },

	{medals,resourcesPath + "textures/medals.png",3}
};

vector<Resources::TextMsgInfo> Resources::messages_{
	//Mensajes predeterminados {nombre_en_enum, texto, color, fuente}. Ejemplo abajo
	//{ HelloWorld, "Hello World", { COLOR(0xaaffffff) }, ARIAL16 }
	{ PauseText, "PAUSE", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ ResumeText, "Resume", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ MusicText, "Music", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ EffectsText, "Effects", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ MainMenuText, "Main Menu", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },

	//OnlineMenu
	{ Local, "Local", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ Host, "Host", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ Join, "Join", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },

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
	{ GardenRoomText, "Garden Room", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },

	//Tutorial
	{ Completed, "Completed: ", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ Slash, "/", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ Zero, "0", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ One, "1", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ Two, "2", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ Three, "3", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ Four, "4", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ MoveTutorial, "Welcome to PCE! To move, hold and release the A button / Tab / F / Enter while pointing anywhere with the left joystick / WASD / IJKL. The longer you hold, the greater the impulse! Everyone boost once to continue!", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ HoldTutorial, "It's hard to give yourself a good boost out of thin air, so press the left trigger / Shift to hold on a object, like a wall. This will stop you and let you build a greater impulse. To let loose, simply release the button on controller, or press again on keyboard. Everyone hold on to something to continue!", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ GrabTutorial, "Weapons will allow you to harm your oponents and sometimes even improve your mobility. Pick up weapons with the Y button / Q / E / , / O. Everyone pick a weapon to continue!", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ ActionTutorial, "Some weapons can be activated with the X button / R / Z / . / P, which will make them shoot, attack at melee range or something else entirely. Everyone use a weapon to continue!", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ ThrowTutorial, "All weapons can be thrown with the same button as picking them up, which can be used to cover great distances quickly. Everyone throw a weapon to continue!", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ DeathTutorial, "In many Game Modes enough damage will kill you, which will disarm you and make you respawn. You'll leave a body behind which can be held on to. You can stand in this dangerous plant to take damage. Everyone die once to finish the tutorial!", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
	{ TutorialEnd, "Congratulations! You know all the basics of PCE. Play around if you want or press Start to go to the menu and choose Salir to exit.", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },

	//MidGame
	{ ContinueText, "Press any key/button to continue", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },

	//Countdown
	{ Go, "GO!", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },

	{NumZero,"0",{ COLOR(0xc32454ff) },FontId::NES_Chimera},
	{NumOne,"1",{ COLOR(0xc32454ff) },FontId::NES_Chimera},
	{NumTwo,"2",{ COLOR(0xc32454ff) },FontId::NES_Chimera},
	{NumThree,"3",{ COLOR(0xc32454ff) },FontId::NES_Chimera},
	{NumFour,"4",{ COLOR(0xc32454ff) },FontId::NES_Chimera},
	{NumFive,"5",{ COLOR(0xc32454ff) },FontId::NES_Chimera},
	{NumSix,"6",{ COLOR(0xc32454ff) },FontId::NES_Chimera},
	{NumSeven,"7",{ COLOR(0xc32454ff) },FontId::NES_Chimera},
	{NumEight,"8",{ COLOR(0xc32454ff) },FontId::NES_Chimera},
	{NumNine,"9",{ COLOR(0xc32454ff) },FontId::NES_Chimera},

	//timers
	{Colon,":",{ COLOR(0xc32454ff) },FontId::NES_Chimera},

	//winner msgs
	{winner1,"GANA EL JUGADOR 1",{COLOR(0xf79617ff)},FontId::NES_Chimera},
	{winner2,"GANA EL JUGADOR 2",{COLOR(0xf79617ff)},FontId::NES_Chimera},
	{winner3,"GANA EL JUGADOR 3",{COLOR(0xf79617ff)},FontId::NES_Chimera},
	{winner4,"GANA EL JUGADOR 4",{COLOR(0xf79617ff)},FontId::NES_Chimera},

	//Credits
	{ ReturnText, "Press any key/button to return", { COLOR(0xc7f2edff) }, FontId::NES_Chimera },
};

vector<Resources::MusicInfo> Resources::musics_{
	//Música {nombre_en_enum, ruta}
	{ MainMenuMusic , resourcesPath + "sound/mainMenu.mp3" },
	{ EntranceMusic , resourcesPath + "sound/entrance.mp3" },
	{ LivingRoomMusic , resourcesPath + "sound/livingRoom.mp3" },
	{ GymMusic , resourcesPath + "sound/gym.mp3" },
	{ TutorialMusic , resourcesPath + "sound/tutorial.mp3" },
	{ GardenMusic , resourcesPath + "sound/garden.mp3" },
	{ BoilerRoomMusic, resourcesPath + "sound/boilerRoom.mp3" }
};

vector<Resources::SoundInfo> Resources::sounds_{
	//Efectos de sonido {nombre_en_enum, ruta}. Ejemplo abajo
	//{ Shoot, "../assets/game/sound/shoot.mp3" },

	// UI
	{ StartGame, resourcesPath + "sound/effects/UI/enterGame.mp3" },
	{ ThreeTwoOneSound, resourcesPath + "sound/effects/UI/321.wav" },
	{ GoSound, resourcesPath + "sound/effects/UI/go.wav" },

	//Menu
	{MenuMove, resourcesPath + "sound/effects/UI/menuMove.wav"},
	{MenuForward, resourcesPath + "sound/effects/UI/menuSelection.wav"},
	{MenuBackward, resourcesPath + "sound/effects/UI/menuBack.wav"},

	// specific to a map sounds
	{ PadSound, resourcesPath + "sound/effects/padSound.wav" },

	// specific to a mode sounds
	{ CoinSound, resourcesPath + "sound/effects/coinSound.wav" },

	// boiler
	{ BoilerShootSound, resourcesPath + "sound/effects/boilerShoot.wav" },
	{ BoilerButtonSlowSound, resourcesPath + "sound/effects/boilerSlow.wav" },
	{ BoilerButtonFastSound, resourcesPath + "sound/effects/boilerFast.wav" },

	{ CarnivorousPlantSound, resourcesPath + "sound/effects/carnivorousPlant.wav" },

	// Weapons
	{ BananaShootSound, resourcesPath + "sound/effects/bananaShoot.wav"},
	{ ExtinguisherSound, resourcesPath + "sound/effects/extinguisherSound.wav" },
	{ PickSound, resourcesPath + "sound/effects/pick.wav"},
	{ TomatoExplosionSound, resourcesPath + "sound/effects/tomatoExplosionSound.wav"},
	{ ConfettiSound, resourcesPath + "sound/effects/confettiSound.wav"},

	//Player
	{ RespawnSound, resourcesPath + "sound/effects/RespawnSound.wav"},
	{ DeathSound, resourcesPath + "sound/effects/DeathSound.wav" },
	{ EliminatedSound, resourcesPath + "sound/effects/EliminatedSound.wav" },
	{ ImpulseFromAirSound, resourcesPath + "sound/effects/impulsoAire.wav" },
	{ ImpulseAttachedSound, resourcesPath + "sound/effects/impulsoPared.wav" }
};

map<std::string, Resources::TextureId> Resources::tilesetTag_{
};
