# Arquitectura del proyecto

Se han determinado los siguientes patrones de diseño a la hora de desarrollar PCE.
Hay libertad de escribir el código como sea más cómodo y escalable dentro de estos patrones.

## Patrones de diseño

* **Arquitectura por componentes:** Al igual que en TPV2 los estados de juego gestionarán una lista de entidades con componentes. Se pueden crear **componentes mediante herencia**, pero las entidades no tendrán subclases.

* **Singleton:** Habrá un único singleton, GameManager, que gestionará la comunicación entre objetos del juego. Cualquier otro "manager", encargado de texturas/sonido será únicamente accesible desde el GameManager para mantener el código limpio.

* **Máquina de estados:** Usaremos una pila al igual que en TPV1, usaremos una pila de estados para facilitar la vuelta al estado anterior. Se añadirán un estado de partida, 
  que dicta el modo en el que se suceden las rondas de juego y un PlayState, que recibirá por parámetro el tipo de juego y el mapa.

	
## Librerías

* **SDL2:** a pesar de la tentativa de Carlos León para usar Unreal.

* **Box2D:** como motor de físicas.

* **SDL2_TTF:** como librería de texto.

* **SDL2_Mixer:** como librería de audio.
