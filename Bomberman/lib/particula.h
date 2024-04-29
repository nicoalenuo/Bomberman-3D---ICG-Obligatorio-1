#pragma once

#ifndef PARTICULA_H
#define PARTICULA_H

#include <random>

#include "objeto.h"

class particula : public objeto{
protected:
	vector_3 velocidad;
	vector_3 aceleracion;
	vector_3 pos_inicial;

	GLfloat tiempoParticula;

	bool eliminar; //el controlador eliminara en cada frame las particulas con esta bandera en true

public:
	particula(vector_3 pos, vector_3 tam, vector_3 ac, vector_3 vel);

	bool getEliminar() const { return eliminar; };

	virtual void actualizar() = 0;
	virtual void dibujar() = 0;
};

#endif
