#pragma once

#ifndef CONTROLADORCAMARA_H
#define CONTROLADORCAMARA_H

#include "SDL.h"
#include "SDL_opengl.h"
#include "FreeImage.h"
#include <GL/glu.h>

#include "global.h"

#include <random>

enum tipo_camara {
	CAMARA_PRIMERA_PERSONA,
	CAMARA_TERCERA_PERSONA,
	CAMARA_ISOMETRICA
};

enum tipo_direccion {
	EJE_X,
	EJE_Z,
	EJE_MENOS_X,
	EJE_MENOS_Z
};

class ControladorCamara{
private:
	static ControladorCamara* instancia;
	ControladorCamara();

	tipo_camara camara_actual;
	int tiempoSacudirse;
public:
	static ControladorCamara* getInstance();

	void cambiarTipoCamara();
	void colocarCamara(vector_3 pos);
	void sacudir(int tiempo);
	bool camaraMiraHacia(tipo_direccion direccion);

	~ControladorCamara();
};

#endif
