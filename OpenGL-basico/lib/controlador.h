#include "personajes.h"
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

#ifndef CONTROLADOR_H
#define CONTROLADOR_H
#endif

using namespace std;

class bomba;
class estructura;
class objeto;
class enemigo;
class bomberman;

using namespace std;

class Controlador {
private:
	Controlador();

	static Controlador* instancia;

	SDL_Window* window;
	SDL_GLContext context;
	SDL_Event evento;

	bool moverArriba;
	bool moverIzquierda;
	bool moverDerecha;
	bool moverAbajo;

	int mouseX;

	bool pausa;
	int nivel;
	int largoTablero = 6;
	int anchoTablero = 6;

	bool fin;

	objeto*** tablero = new objeto * *[largoTablero];
	list<estructura*> estructuraDestructible = list<estructura*>(); //aqui van las estructuras destructibles
	list<bomba*> bombas = list<bomba*>(); //lista de todas las bombas, ordenadas de tiempo de menor a mayor
	list<enemigo*> enemigos = list<enemigo*>();
	bomberman* jugador; //en principio solo hay un jugador
public:
	static Controlador* getInstance();

	void inicializar();

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

	bool getMoverArriba();
	bool getMoverAbajo();
	bool getMoverDerecha();
	bool getMoverIzquierda();

	void setMoverArriba(bool moverArriba);
	void setMoverDerecha(bool moverDerecha);
	void setMoverIzquierda(bool moverIzquierda);
	void setMoverAbajo(bool moverAbajo);

	int getMouseX();
	void setMouseX(int mouseX);

	void pausar(); //pausa o despausa
	void aumentarNivel();
	void crearBomba(int x, int z, personajes* pers);
	void ponerBomba(int x, int z, personajes* pers);

	~Controlador();
};


