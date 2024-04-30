#pragma once

#ifndef OBJETO_H
#define OBJETO_H

#include "global.h"
#include "SDL.h"
#include "SDL_opengl.h"

#include "../constantes/constantes.h"

#include "ControladorObjetos.h"
#include "ControladorTexturas.h"
#include "ControladorAudio.h"
#include "ControladorPoderes.h"

struct vector_3 {
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

class objeto {
protected:
	vector_3 pos;
	vector_3 tam;
public:
	objeto(vector_3 pos, vector_3 tam) : pos(pos), tam(tam) {}

	vector_3 getPosicion() const { return pos; };
	vector_3 getTamanio() const { return tam; };

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

