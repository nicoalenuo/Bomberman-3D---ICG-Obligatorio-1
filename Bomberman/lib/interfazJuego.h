#pragma once

#ifndef interfazJuego_H
#define interfazJuego_H

#include "SDL.h"
#include "SDL_opengl.h"
#include <GL/glu.h>

#include "global.h"

using namespace std;

class interfazJuego {

private:
	interfazJuego();

	static interfazJuego* instancia;

	global* global;

	bool visible;

public:
	static interfazJuego* getInstance();

	//virtual void actualizar() = 0;

	bool getVisible();
	void setVisible(bool visible);
	void swapVisible();

	void dibujar();

	~interfazJuego();
};

#endif

