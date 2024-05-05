#pragma once

#ifndef PARTICULA_ESTRUCTURA_H
#define PARTICULA_ESTRUCTURA_H

#include "particula.h"

class particula_estructura : public particula{
private:
	GLuint textura;
	int tiempoEliminacion;
	GLfloat color_alpha;
public:
	particula_estructura(vector_3 pos, vector_3 tam, vector_3 ac, vector_3 vel, GLuint textura);

	void actualizar();
	void dibujar();

};

#endif

