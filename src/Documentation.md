# DOCUMENTACIÓN

## INPUTHANDLER
Cualquier input se recibe mediante esta clase, a la que podemos llamar desde SDL_Game::instance()->getInputHandler();
Tiene soporte para teclado, ratón y mando, a excepción de los D-Pad

### Mandos
Actualmente, la interfaz permite acceder a
- La posición actual de un stick **getStickDir()**
- La última posición no nula de un stick (que no sea 0,0) **getLastStickDir()**
- El estado actual de un botón (recién pulsado, recien soltado, pulsación mantenida, suelto)**isButton(Just)Up/Down()**

Todos estos métodos están separados del tratamiento de eventos y devuelven valores de m_joystickValues, m_triggerValues y m_buttonStates.

Estos vectores que guardan la información correspondiente a los mandos se actualiza utilizando la API de SDL2 con los metodos correspondientes en update()

### Mapeo de mandos

Para que SDL reconozca un mando y su esquema de controles es necesario que en src/config/gamecontrollerdb.txt aparezca una string de mapeo que podeis crear para vuestro mando. Cuando se carga esta string, el vínculo entre botones hardware y botones del enum SDL_GameControllerButton
 se guarda como parte de los GameController de m_gameControllers. cada vez que se pulsa un botón, **onJoyButtonChange()** busca el vínculo correspondiente para un botón de un determinado mando.


## TILEMAP
Tenemos código sólido, pero un poco tiquismiquis con los formatos
### El Tilemap

Es muy importante que el mapa tenga un formato específico para el parser Tileson

 - **El aspect ratio** tiene que ser igual en el archivo que editeis que el la versión final, porque si no hay huecos entre los tiles
 - **Hay que exportar en modo de compresión CSV** para que el JSON generado tenga un array "data"y se pueda parsear. Nada de Base64 sin comprimir, Phaser ha muerto.
 - **Los tileset necesitan un formato específico** . Al añadir un conjunto de patrones a Tiled es muy importante guardarlo como JSON. Al exportar el mapa, se exportan también los tilesets que usa. Es posible que en vez de sacaros los datos, el objeto JSON del tileset sólo os venga con "source":"tilemapdekenney.json". Tenéis que abrir ese json y copiar todos los datos para que tenga todas las variables necesarias (podéis consultarlas en /assets/game/tilemaps/TD_TilemapBitCSV.json).
 - **Ojo con los ID**. cada tileset tiene una variable firstgid y un tilecount, es muy importante que en el array de tilesets del json "firstgid" sea igual al firstgid + tilecount del anterior.

### Texturas de los tileset para SDL

A demás de cargar la textura como cualquier otra en Resources.h/cpp **también hay que añadirlo a la tabla map tilesetTag_** 
en Resources.cpp. Esto permite relacionar el nombre con su textura correspondiente y que todo el renderizado sea automático y bonito.


## Detección de colisiones

### Métodos de colisión

Cuando dos entidades chocan se llama al método virtual Component::onCollisionEnter(), que por defecto no hace nada y se pasa por parámetros los detalles de la colisión.
Su método homólogo Component::onCollisionExit() se llama cuando acaba la colisión. Queda declarado un método onCollisionStay por si fuese necesario refactorizar en un futuro las acciones que se gestionan en el update.
	
### Struct Collision

Contenedor de la información general relativa a las colisiones, su funcionalidad es tener cacheadas los punteros que se suelen pedir como la entidad con la que se ha chocado o el manager que ha detectado la colisión.

