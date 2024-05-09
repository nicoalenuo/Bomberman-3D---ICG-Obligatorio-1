#pragma once

#ifndef CONTROLADORLUZ_H
#define CONTROLADORLUZ_H

#include <stack>

#include "SDL_opengl.h"
#include "global.h"

enum TIPO_LUZ_AMBIENTE { MANIANA, TARDE, NOCHE, SIN_LUZ_AMBIENTE };

struct luz{
	GLenum idLuz;
	vector_3 posicion;
	GLfloat color[4];
};

class ControladorLuz {
	private:
		static ControladorLuz* instancia;
		ControladorLuz();

		GLfloat light_position[4];
		GLfloat light_color[4];
		GLfloat material_ambient_diffuse_color[4];
		GLfloat material_specular_color[4];
		GLfloat light_offset_x;
		GLfloat light_offset_y;
		GLfloat light_offset_z;
		TIPO_LUZ_AMBIENTE colorLuzAmbiente;

		stack<GLenum> lucesDisponibles;
		stack<luz> lucesAMostrar;
	public:
		static ControladorLuz* getInstance();

		void pedirLuz(vector_3 pos, GLfloat color[4]);
		void colocarLuces(vector_3 pos);
		void quitarLuces();
		void cambiarColorLuzAmbiente();
		void moverCamara(vector_3 pos);

		~ControladorLuz();
};

#endif

