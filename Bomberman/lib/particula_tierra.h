#pragma once

#ifndef PARTICULA_TIERRA_H
#define PARTICULA_TIERRA_H

#include "particula.h"

class particula_tierra : public particula {
private:
	GLuint textura;
public:
	particula_tierra(vector_3 pos, vector_3 tam, vector_3 ac, vector_3 vel, GLuint textura);

	void actualizar();
	void dibujar();
};

#endif

