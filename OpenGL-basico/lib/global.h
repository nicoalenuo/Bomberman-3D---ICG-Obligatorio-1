#pragma once

#ifndef GLOBAL_H
#define GLOBAL_H

#include <list>

#include "SDL.h"
#include "SDL_opengl.h"
#include <GL/glu.h>


#include <stdio.h>
#include <iostream>

using namespace std;


class global { 
private:
	static global* instancia;
	global();

	bool moverArriba;
	bool moverIzquierda;
	bool moverDerecha;
	bool moverAbajo;

	int mouseX;

public:
	static global* getInstance();

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
};


#endif