#pragma once

#ifndef PARTICULA_H
#define PARTICULA_H

#include "objeto.h"

struct velocidad {
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

struct aceleracion {
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

class particula : public objeto{
private:
	int tiempoParticula;
	GLfloat pos_y_inicial;
	velocidad vel;
	aceleracion ac;

public:
	particula(posicion pos, tamanio tam, aceleracion ac, velocidad vel);

	void actualizar();
	void dibujar();
};

#endif
