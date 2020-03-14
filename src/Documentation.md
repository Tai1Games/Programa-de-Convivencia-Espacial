# Cómo usar Tiled con SDL y no morir en el intento 
Tenemos código sólido, pero un poco tiquismiquis con los formatos
## El Tilemap

Es muy importante que el mapa tenga un formato específico para el parser Tileson

 - **El aspect ratio** tiene que ser igual en el archivo que editeis que el la versión final, porque si no hay huecos entre los tiles
 - **Hay que exportar en modo de compresión CSV** para que el JSON generado tenga un array "data"y se pueda parsear. Nada de Base64 sin comprimir, Phaser ha muerto.
 - **Los tileset necesitan un formato específico** . Al añadir un conjunto de patrones a Tiled es muy importante guardarlo como JSON. Al exportar el mapa, se exportan también los tilesets que usa. Es posible que en vez de sacaros los datos, el objeto JSON del tileset sólo os venga con "source":"tilemapdekenney.json". Tenéis que abrir ese json y copiar todos los datos para que tenga todas las variables necesarias (podéis consultarlas en /assets/game/tilemaps/TD_TilemapBitCSV.json).
 - **Ojo con los ID**. cada tileset tiene una variable firstgid y un tilecount, es muy importante que en el array de tilesets del json "firstgid" sea igual al firstgid + tilecount del anterior.

## Texturas de los tileset para SDL

A demás de cargar la textura como cualquier otra en Resources.h/cpp **también hay que añadirlo a la tabla map tilesetTag_** 
en Resources.cpp. Esto permite relacionar el nombre con su textura correspondiente y que todo el renderizado sea automático y bonito.
```