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
#include "bonificador.h"
#include "door.h"
#include "hud.h"

#include "ControladorCamara.h"
#include "ControladorObjetos.h"
#include "ControladorInterfaz.h"
#include "ControladorAudio.h"
#include "ControladorLuz.h"

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

	~Controlador();
};

#endif

