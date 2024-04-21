#include "../lib/personaje.h"

personaje::personaje(posicion pos, tamanio tam, GLfloat velocidad) : objeto(pos, tam) {
	this->velocidad = velocidad;
}

GLfloat personaje::getVelocidad() {
	return velocidad;
}

void personaje::setVelocidad(GLfloat vel) {
	velocidad = vel;
}
