#pragma once

#ifndef CONTROLADORLUZ_H
#define CONTROLADORLUZ_H

#include "SDL_opengl.h"
#include "global.h"
#include "../constantes/constantes.h"

class ControladorLuz {
	private:
		static GLfloat light_position[4];
		static GLfloat light_color[4];
		static GLfloat material_ambient_diffuse_color[4];
		static GLfloat material_specular_color[4];
		static GLfloat light_offset_x;
		static GLfloat light_offset_y;
		static GLfloat light_offset_z;
		static int colorLuzAmbiente;
		static int colorLuzBonificador;
	public:
		static void colocarLuces();
		static void cambiarColorLuzAmbiente();
		static void cambiarColorLuzBonificador();
};

#endif

