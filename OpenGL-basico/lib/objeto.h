#pragma once

#ifndef OBJETO_H
#define OBJETO_H

#include "global.h"

class Controlador;

class objeto { //abstracta
protected:
	global* global;
	float coord_x;
	float coord_z;
public:
	virtual float getCoordX();
	virtual float getCoordZ();
	virtual void setCoordX(float x);
	virtual void setCoordZ(float z);
	virtual void actualizar() = 0;
	virtual void dibujar() = 0;
};


#endif

