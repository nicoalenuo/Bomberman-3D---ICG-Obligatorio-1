#pragma once

#ifndef PARTICULA_FUEGO_H
#define PARTICULA_FUEGO_H

#include "particula.h"

enum tipo_color { //dependiendo del color, se comportan de formas distintas
	FUEGO_ROJO,
	FUEGO_AMARILLO
};

class particula_fuego : public particula{
private:
	GLfloat color[3];
	tipo_color tipoColor;
public:
	particula_fuego(vector_3 pos, vector_3 tam, vector_3 ac, vector_3 vel);

	void actualizar();
	void dibujar();
};

#endif

