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

	bool getPausa();
	void setPausa(bool pau);

	bool getNivel();
	void setNivel(int niv);

	bool getFin();
	void setFin(bool fin);

	void toggle_pausa(); 
	void aumentarNivel();

	~Controlador();
};


#endif

