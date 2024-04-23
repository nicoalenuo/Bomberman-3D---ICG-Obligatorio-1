#pragma once

#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "objeto.h"

class personaje : public objeto { 
protected:
	GLfloat velocidad;
public:
	personaje(posicion pos, tamanio tam, GLfloat velocidad);

	GLfloat getVelocidad() const { return velocidad; };
	void setVelocidad(GLfloat vel) { velocidad = vel; };

	virtual void actualizar() = 0;
	virtual void dibujar() = 0;
};

#endif

