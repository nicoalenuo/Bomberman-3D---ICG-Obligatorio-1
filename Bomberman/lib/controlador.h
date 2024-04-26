#pragma once

#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "SDL.h"
#include "SDL_opengl.h"
#include "FreeImage.h"
#include <GL/glu.h>
#include "al.h"

#include <random>

#include "personaje.h"
#include "bomba.h"
#include "estructura.h"
#include "objeto.h"
#include "enemigo.h"
#include "bomberman.h"
#include "hud.h"

#include "../lib/ControladorCamara.h"
#include "../lib/ControladorObjetos.h"
#include "../lib/ControladorInterfaz.h"
#include "../lib/ControladorAudio.h"
#include "../lib/ControladorLuz.h"

class Controlador {
private:
	Controlador();

	static Controlador* instancia;

	SDL_Window* window;
	SDL_GLContext context;
	SDL_Event evento;
	
public:
	static Controlador* getInstance();

	void manejarEventos();
	void actualizar();
	void dibujar();

	void toggle_pantallaCompleta(SDL_Window* Window);

	~Controlador();
};

#endif

