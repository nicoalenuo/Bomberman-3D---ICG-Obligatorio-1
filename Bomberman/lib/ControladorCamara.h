#pragma once

#ifndef CONTROLADORCAMARA_H
#define CONTROLADORCAMARA_H

#include "SDL_opengl.h"

#include "../lib/global.h"
#include "../lib/bomberman.h"

#include <random>

#include "../constantes/constantes.h"

enum tipo_camara {
	CAMARA_PRIMERA_PERSONA,
	CAMARA_TERCERA_PERSONA,
	CAMARA_ISOMETRICA,
	CAMARA_ORIGINAL
};

enum tipo_direccion {
	EJE_X,
	EJE_Z,
	EJE_MENOS_X,
	EJE_MENOS_Z
};

class ControladorCamara{
private:
	static tipo_camara camara_actual;
	static int tiempoSacudirse;
public:
	static void cambiarTipoCamara();
	static void colocarCamara();
	static void sacudir(int tiempo);
	static bool camaraMiraHacia(tipo_direccion direccion);
};

#endif
