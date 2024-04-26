#pragma once

#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "objeto.h"

class personaje : public objeto { 
protected:
	GLfloat velocidad;
public:
	personaje(vector_3 pos, vector_3 tam, GLfloat velocidad);

	GLfloat getVelocidad() const { return velocidad; };
	void setVelocidad(GLfloat vel) { velocidad = vel; };

	virtual bool posicion_valida(vector_3 pos, vector_3 tam);
	virtual void actualizar() = 0;
	virtual void dibujar() = 0;
};

#endif

