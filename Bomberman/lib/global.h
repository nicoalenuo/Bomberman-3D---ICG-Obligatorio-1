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
public:

	bool moverArriba;
	bool moverIzquierda;
	bool moverDerecha;
	bool moverAbajo;

	int mouseX;

	static global* getInstance();
};


#endif