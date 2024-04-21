#pragma once

#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "objeto.h"

class personaje : public objeto { 
protected:
	GLfloat velocidad;
public:
	personaje(posicion pos, tamanio tam, GLfloat velocidad);
	virtual void actualizar() = 0;
	virtual void dibujar() = 0;
};

#endif

