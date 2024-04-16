#pragma once

#ifndef OBJETO_H
#define OBJETO_H

#include "global.h"

class objeto { //abstracta
protected:
	global* global;
	GLfloat coord_x;
	GLfloat coord_z;
	GLfloat ancho_x;
	GLfloat ancho_z;
	GLfloat altura;
public:
	objeto(GLfloat x, GLfloat z, GLfloat anchoX, GLfloat anchoZ, GLfloat alt):
		coord_x(x), coord_z(z), ancho_x(anchoX), ancho_z(anchoZ), altura(alt), global((*global).getInstance()){}
	virtual GLfloat getCoordX();
	virtual GLfloat getCoordZ();
	virtual void setCoordX(GLfloat x);
	virtual void setCoordZ(GLfloat z);
	virtual void actualizar() = 0;
	virtual void dibujar() = 0;
};

#endif

