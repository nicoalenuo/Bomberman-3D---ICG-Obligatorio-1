#pragma once

#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "SDL.h"
#include "SDL_opengl.h"
#include "FreeImage.h"
#include <GL/glu.h>

#include <random>
#include <chrono>

#include "personaje.h"
#include "bomba.h"
#include "estructura.h"
#include "objeto.h"
#include "enemigo.h"
#include "bomberman.h"
#include "bonificador.h"
#include "puerta.h"

#include "ControladorCamara.h"
#include "ControladorObjetos.h"
#include "ControladorInterfaz.h"
#include "ControladorAudio.h"
#include "ControladorLuz.h"
#include "ControladorPoderes.h"

class Controlador {
private:
	Controlador();
	static Controlador* instancia;

	ControladorAudio* controlador_audio;
	ControladorCamara* controlador_camara;
	ControladorInterfaz* controlador_interfaz;
	ControladorLuz* controlador_luz;
	ControladorObjetos* controlador_objetos;
	ControladorPoderes* controlador_poderes;
	ControladorTexturas* controlador_texturas;

	SDL_Window* window;
	SDL_GLContext context;
	SDL_Event evento;

	int cantidad_enemigos_actual;
public:
	static Controlador* getInstance();
	~Controlador();

	void inicializar_juego();

	void manejarEventos();
	void actualizar();
	void dibujar();
};

#endif

