#pragma once

#ifndef OBJETO_H
#define OBJETO_H

#include "global.h"
#include "../constantes/constantes.h"

#include "ControladorObjetos.h"
#include "ControladorTexturas.h"

struct posicion {
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

struct tamanio {
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

class objeto {
protected:
	posicion pos;
	tamanio tam;
public:
	objeto(posicion pos, tamanio tam) : pos(pos), tam(tam) {}

	posicion getPosicion();
	tamanio getTamanio();

	void setPosicionX(GLfloat x);
	void setPosicionY(GLfloat y);
	void setPosicionZ(GLfloat z);

	void setTamanioX(GLfloat x);
	void setTamanioY(GLfloat y);
	void setTamanioZ(GLfloat z);

	virtual void actualizar() = 0;
	virtual void dibujar() = 0;
};

#endif

