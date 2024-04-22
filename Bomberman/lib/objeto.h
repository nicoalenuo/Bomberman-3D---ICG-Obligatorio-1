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

	posicion getPosicion() const { return pos; };
	tamanio getTamanio() const { return tam; };

	void setPosicionX(GLfloat x) { pos.x = x; };
	void setPosicionY(GLfloat y) { pos.y = y; };
	void setPosicionZ(GLfloat z) { pos.z = z; };

	void setTamanioX(GLfloat x) { tam.x = x; };
	void setTamanioY(GLfloat y) { tam.y = y; };
	void setTamanioZ(GLfloat z) { tam.z = z; };

	virtual void actualizar() = 0;
	virtual void dibujar() = 0;
};

#endif

