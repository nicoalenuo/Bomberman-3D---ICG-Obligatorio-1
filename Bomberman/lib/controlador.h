#pragma once

#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "SDL.h"
#include "SDL_opengl.h"
#include "FreeImage.h"
#include <GL/glu.h>

#include <random>

#include "personaje.h"
#include "bomba.h"
#include "estructura.h"
#include "objeto.h"
#include "enemigo.h"
#include "bomberman.h"
#include "personaje.h"

#include "../lib/ControladorCamara.h"


class Controlador {
private:
	Controlador();

	static Controlador* instancia;

	SDL_Window* window;
	SDL_GLContext context;
	SDL_Event evento;
	
	bool pausa, fin;
	int nivel, tiempoJuego; //segundos
public:
	static Controlador* getInstance();

	void manejarEventos();
	void actualizar();
	void dibujar();

	bool getPausa() const { return pausa; };
	void setPausa(bool pau) { pausa = pau; };

	bool getNivel() const { return nivel; };
	void setNivel(int niv) { nivel = niv;};

	bool getFin() const { return fin; };
	void setFin(bool f) { fin = f; };

	void toggle_pausa() { pausa = !pausa; };
	void aumentarNivel() { nivel++; };

	~Controlador();
};


#endif

