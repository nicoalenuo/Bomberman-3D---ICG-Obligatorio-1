#include "../lib/personaje.h"

personaje::personaje(GLfloat x, GLfloat z, GLfloat anchoX, GLfloat anchoZ, GLfloat alt, GLfloat velocidad) : objeto(x,z, anchoX, anchoZ, alt) {
	this->velocidad = velocidad;
}
