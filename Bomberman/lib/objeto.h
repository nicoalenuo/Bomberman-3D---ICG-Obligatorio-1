#pragma once

#ifndef OBJETO_H
#define OBJETO_H

#include "global.h"
#include "../constantes/constantes.h"

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
	global* global;
	posicion pos;
	tamanio tam;
public:
	objeto(posicion pos, tamanio tam):
		pos(pos), tam(tam), global((*global).getInstance()) {}
	virtual posicion getPosicion();
	virtual tamanio getTamanio();
	virtual void setPosicionX(GLfloat x);
	virtual void setPosicionY(GLfloat y);
	virtual void setPosicionZ(GLfloat z);
	virtual void setTamanioX(GLfloat x);
	virtual void setTamanioY(GLfloat y);
	virtual void setTamanioZ(GLfloat z);

	virtual void actualizar() = 0;
	virtual void dibujar() = 0;
};

#endif

