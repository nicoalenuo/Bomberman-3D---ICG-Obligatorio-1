#pragma once

#ifndef OBJETO_H
#define OBJETO_H

#include "global.h"

class objeto { //abstracta
protected:
	global* global;
	GLfloat coord_x;
	GLfloat coord_z;
public:
	objeto(GLfloat x, GLfloat z): coord_x(x), coord_z(z), global((*global).getInstance()){}
	virtual float getCoordX();
	virtual float getCoordZ();
	virtual void setCoordX(float x);
	virtual void setCoordZ(float z);
	virtual void actualizar() = 0;
	virtual void dibujar() = 0;
};

#endif

