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

		GLfloat posicionLuz[4];
		GLfloat colorLuz[4];
		GLfloat colorDiffuse[4];
		GLfloat colorSpecular[4];
		GLfloat* shininess;
		vector_3 desplazamiento_luz;
		TIPO_LUZ_AMBIENTE colorLuzAmbiente;

		stack<GLenum> lucesDisponibles;
		stack<luz> lucesAMostrar;
	public:
		static ControladorLuz* getInstance();

		void pedirLuz(vector_3 pos, GLfloat color[4]);
		void colocarLuces(vector_3 pos);
		void quitarLuces();
		void cambiarColorLuzAmbiente();
		void moverLuzAmbiente(vector_3 pos);

		~ControladorLuz();
};

#endif

