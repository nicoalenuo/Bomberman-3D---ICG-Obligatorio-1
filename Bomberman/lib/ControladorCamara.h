#pragma once

#ifndef CONTROLADORCAMARA_H
#define CONTROLADORCAMARA_H

#include "SDL_opengl.h"

#include "global.h"
#include "bomberman.h"

#include <random>

#include "../constantes/constantes.h"

enum tipo_camara {
	CAMARA_TERCERA_PERSONA,
	CAMARA_ISOMETRICA,
	CAMARA_ORIGINAL
};

class ControladorCamara{
private:
	static tipo_camara camara_actual;
	static int tiempoSacudirse;
public:
	static void cambiarTipoCamara(tipo_camara camara);
	static void colocarCamara();
	static void sacudir(int tiempo);
};

#endif
