#pragma once

#ifndef CONTROLADORLUZ_H
#define CONTROLADORLUZ_H

#include <stack>

#include "SDL_opengl.h"
#include "global.h"

enum TIPO_LUZ_AMBIENTE { MANIANA, TARDE, NOCHE, SIN_LUZ_AMBIENTE };
enum TIPO_LUZ_BONIFICADOR {AMARILLO, CELESTE ,VIOLETA, SIN_LUZ_BONIFICADOR };

struct luz{
	GLenum idLuz;
	vector_3 posicion;
	GLfloat color[4];
};

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

		static stack<GLenum> lucesDisponibles;
		static stack<luz> lucesAMostrar;
	public:
		static void cargarLuces();
		static void pedirLuz(vector_3 pos, GLfloat color[4]);
		static void colocarLuces(vector_3 pos);
		static void quitarLuces();
		static void cambiarColorLuzAmbiente();
		static void moverCamara(vector_3 pos);
};

#endif

