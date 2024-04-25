#pragma once

#ifndef PARTICULA_H
#define PARTICULA_H

#include "objeto.h"

class particula : public objeto{
private:
	bool eliminar;
	int tiempoEliminacion; //una vez alcancen la posicion 0, esperaran un poco antes de eliminarse
	int tiempoParticula;
	GLfloat pos_y_inicial;
	vector_3 vel;
	vector_3 ac;

	GLuint textura;

public:
	particula(vector_3 pos, vector_3 tam, vector_3 ac, vector_3 vel, GLuint textura);

	bool getEliminar() const { return eliminar; };

	void actualizar();
	void dibujar();
};

#endif
