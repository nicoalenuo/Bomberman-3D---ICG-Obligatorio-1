#include "../lib/personaje.h"

personaje::personaje(posicion pos, tamanio tam, GLfloat velocidad) : objeto(pos, tam) {
	this->velocidad = velocidad;
}
