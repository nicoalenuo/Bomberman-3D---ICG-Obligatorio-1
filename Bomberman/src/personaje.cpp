#include "../lib/personaje.h"

personaje::personaje(vector_3 pos, vector_3 tam, GLfloat velocidad) : objeto(pos, tam) {
	this->velocidad = velocidad;
}
