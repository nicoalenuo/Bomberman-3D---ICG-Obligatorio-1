#pragma once

#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "SDL.h"
#include "SDL_opengl.h"
#include "FreeImage.h"
#include <GL/glu.h>


#include <stdio.h>
#include <iostream>
#include <random>

#include "global.h"
#include "personaje.h"
#include "bomba.h"
#include "estructura.h"
#include "objeto.h"
#include "enemigo.h"
#include "bomberman.h"
#include "personaje.h"
#include "ControladorTexturas.h"

using namespace std;

class Controlador {
private:
	Controlador();

	static Controlador* instancia;

	SDL_Window* window;
	SDL_GLContext context;
	SDL_Event evento;

	global* global;
	
	bool texturas_habilitadas;
	bool pausa;
	int nivel;
	int largoTablero = 29;
	int anchoTablero = 11;
	int tiempoJuego; //segundos
	int puntaje;
	bool fin;

	objeto*** tablero = new objeto **[largoTablero];
	list<estructura*> estructuraDestructible = list<estructura*>(); 
	list<bomba*> bombas = list<bomba*>(); 
	list<enemigo*> enemigos = list<enemigo*>();

	bomberman* jugador; 
public:
	static Controlador* getInstance();

	void manejarEventos();
	void actualizar();
	void dibujar();

	SDL_Window* getWindow();

	bool getTexturasHabilitadas();
	void setTexturasHabilitadas(bool text);

	bool getPausa();
	void setPausa(bool pau);

	bool getNivel();
	void setNivel(int niv);

	bool getFin();
	void setFin(bool fin);

	int getLargoTablero();
	void setLargoTablero(int largo);

	int getAnchoTablero();
	void setAnchoTablero(int ancho);

	bomberman* getBomberman();

	void aumentarPuntaje(int punt);

	objeto*** getTablero();

	void toggle_pausa(); 
	void aumentarNivel();
	void ponerBomba(int x, int z);

	~Controlador();
};


#endif

