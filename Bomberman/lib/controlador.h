#pragma once

#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "SDL.h"
#include "SDL_opengl.h"
#include "FreeImage.h"
#include <GL/glu.h>

#include <stdio.h>
#include <iostream>

#include "global.h"
#include "personaje.h"
#include "bomba.h"
#include "estructura.h"
#include "objeto.h"
#include "enemigo.h"
#include "bomberman.h"
#include "personaje.h"

using namespace std;

class Controlador {
private:
	Controlador();

	static Controlador* instancia;

	SDL_Window* window;
	SDL_GLContext context;
	SDL_Event evento;

	global* global;
	
	bool textura;
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
	
	GLuint textura1;
	GLuint textura2;
public:
	static Controlador* getInstance();

	void manejarEventos();
	void actualizar();
	void dibujar();

	void limpiar();

	bool getTextura();
	void setTextura(bool text);

	GLuint getTextura1();
	void setTextura1(GLuint text);

	GLuint getTextura2();
	void setTextura2(GLuint text);

	void cargarTextura();

	bool getPausa();
	void setPausa(bool pau);

	bool getNivel();
	void setNivel(int niv);

	bool getFin();
	void setFin(bool fin);

	void toggle_pausa(); 
	void aumentarNivel();
	void explotarBomba(bomba* bomb);
	void ponerBomba(int x, int z);

	~Controlador();
};


#endif

