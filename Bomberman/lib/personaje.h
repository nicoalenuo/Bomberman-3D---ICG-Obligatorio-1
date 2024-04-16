#pragma once

#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <list>
#include "objeto.h"

using namespace std;

class bomba;

class personaje : public objeto { 
protected:
	
public:
	personaje(GLfloat x, GLfloat z);
	virtual void actualizar() = 0;
	virtual void dibujar() = 0;
};

#endif

