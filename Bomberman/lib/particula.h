#pragma once

#ifndef PARTICULA_H
#define PARTICULA_H

#include <random>

#include "objeto.h"

enum tipo_particula {
	PARTICULA_ESTRUCTURA_DESTRUCTIBLE,
	PARTICULA_FUEGO,
	PARTICULA_BONIFICADOR_IDLE
};

class particula : public objeto{
private:
	vector_3 velocidad;
	vector_3 aceleracion;
	vector_3 pos_inicial;

	tipo_particula tipo;
	GLuint textura; //si no tiene, es igual a 0
	GLfloat tiempoParticula;
	bool eliminar; //el controlador eliminara en cada frame las particulas con esta bandera en true

	//Caso particula de estructura destructible
	int tiempoEliminacion; //una vez alcancen la posicion 0, esperaran un poco antes de eliminarse
	
	//caso particula de fuego
	GLfloat color[3];

	//podria hacer esto con clases que hereden pero me da flojera (tal vez lo haga)(mentira)

public:
	particula(vector_3 pos, vector_3 tam, vector_3 ac, vector_3 vel, GLuint textura, tipo_particula tipo);

	bool getEliminar() const { return eliminar; };

	void actualizar();
	void dibujar();
};

#endif
