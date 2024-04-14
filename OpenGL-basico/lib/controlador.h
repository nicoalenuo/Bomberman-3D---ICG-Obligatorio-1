#pragma once

#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "personaje.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include <GL/glu.h>

#include <stdio.h>
#include <iostream>

#include "global.h"
#include "bomba.h"
#include "estructura.h"
#include "objeto.h"
#include "enemigo.h"
#include "bomberman.h"

using namespace std;

class Controlador {
private:
	Controlador();

	static Controlador* instancia;

	SDL_Window* window;
	SDL_GLContext context;
	SDL_Event evento;

	global* global;

	bool pausa;
	int nivel;
	int largoTablero = 6;
	int anchoTablero = 6;

	bool fin;

	objeto*** tablero = new objeto * *[largoTablero];
	list<estructura*> estructuraDestructible = list<estructura*>(); 
	list<bomba*> bombas = list<bomba*>(); 
	list<enemigo*> enemigos = list<enemigo*>();

	objeto* jugador; 
public:
	static Controlador* getInstance();

	void manejarEventos();
	void actualizar();
	void dibujar();

	void limpiar();

	bool getPausa();
	void setPausa(bool pau);

	bool getNivel();
	void setNivel(int niv);

	bool getFin();
	void setFin(bool fin);

	void pausar(); //pausa o despausa
	void aumentarNivel();
	void crearBomba(int x, int z, bomberman* pers);
	void ponerBomba(int x, int z, bomberman* pers);

	~Controlador();
};


#endif

