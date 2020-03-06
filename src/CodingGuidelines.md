# Coding Guidelines PCE Tai1 Games

## Codigo en general

**Todo el código es en inglés, por facilidad de compatibilidad con las librerias**

Configurad Visual para que funcione con tabs en vez de espacios

No se pueden usar emojis/emoticonos/caritas en el codigo 

Constantes EN_MAYUSCULAS_CON_BARRABAJAS_(SNAKE_CASE), variables y metodos en camelCase empiezanConMinuscula

Todos los métodos `virtual` se ponen otra vez `virtual` de forma explícita para evitar confusiones 

## Dentro de una clase

**Qué va en el header:**
* Getters y Setters
* Métodos vacios (p.e: void update() {})
* La constructora si no hace falta rellenar los corchetes
* Todo lo demás va en el cpp

Variables privadas siguen el esquema: nombre_

**Órden en el header**
1. Protegido
1. Privado
1. Publico
1. Constructora
1. Destructora
1. Todo lo demás

Comentar antes de cada método en el header (no setters y getters) lo que hace
	Se comenta con `/*` para que salga cuando llamas al método

### Pivotal y Github

**El que haga un commit al master muere**

Todas las historias han de ir en ramas distintas

Es buena práctica hacer merge de master a tu rama antes de hacer pull para resolver todos los posibles conflictos y confirmar que funciona

Hay que compilar en 'Debug' y en 'Release' **antes** de pedir pull, asegurándose de que funciona en los dos modos

Liveshare para visual si quereis hacer pair programming

Los nombres de los commits han de ser descriptivos y útiles

### Epilogo

Este documento está sujeto a edición, romper los guidelines aquí descritos puede suponer reject de la historia y obligación a editar el codigo