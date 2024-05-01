#pragma once

#ifndef CONTROLADORLUZ_H
#define CONTROLADORLUZ_H

#include <stack>

#include "SDL_opengl.h"
#include "global.h"
#include "bomberman.h"
#include "../constantes/constantes.h"

enum TIPO_LUZ_AMBIENTE { MANIANA, TARDE, NOCHE, SIN_LUZ_AMBIENTE };
enum TIPO_LUZ_BONIFICADOR {AMARILLO, CELESTE ,VIOLETA, SIN_LUZ_BONIFICADOR };

class ControladorLuz {
	private:
		static GLfloat light_position[4];
		static GLfloat light_color[4];
		static GLfloat material_ambient_diffuse_color[4];
		static GLfloat material_specular_color[4];
		static GLfloat light_offset_x;
		static GLfloat light_offset_y;
		static GLfloat light_offset_z;
		static TIPO_LUZ_AMBIENTE colorLuzAmbiente;
		static TIPO_LUZ_BONIFICADOR colorLuzBonificador;
	public:
		static void colocarLuces();
		static void cambiarColorLuzAmbiente();
		static void cambiarColorLuzBonificador();
};

#endif

