#pragma once

#ifndef CONTROLADORTEXTURAS_H
#define CONTROLADORTEXTURAS_H

#include "SDL.h"
#include "SDL_opengl.h"
#include "FreeImage.h"
#include <GL/glu.h>

enum tipo_textura { //agregar aca en caso de agregar mas texturas, y luego en el switch case del cpp
	ESTRUCTURA_DESTRUCTIBLE,
	ESTRUCTURA_NO_DESTRUCTIBLE
};

class ControladorTexturas{
private:
	static GLuint texturaEstructuraDestructible;
	static GLuint texturaEstructuraNoDestructible;
public:
	static void cargarTexturas();
	static GLuint getTextura(tipo_textura tipo);
};

#endif
