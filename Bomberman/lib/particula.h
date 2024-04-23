#pragma once

#ifndef PARTICULA_H
#define PARTICULA_H

#include "objeto.h"

class particula : public objeto{
private:
	int tiempoParticula;
	GLfloat pos_y_inicial;
	vector_3 vel;
	vector_3 ac;

public:
	particula(vector_3 pos, vector_3 tam, vector_3 ac, vector_3 vel);

	void actualizar();
	void dibujar();
};

#endif
