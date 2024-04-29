#pragma once

#ifndef CONTROLADORTEXTURAS_H
#define CONTROLADORTEXTURAS_H

#include "SDL_opengl.h"
#include "FreeImage.h"
#include <GL/glu.h>

#include "../constantes/constantes.h"

enum tipo_textura { //agregar aca en caso de agregar mas texturas, y luego en el switch case del cpp
	ESTRUCTURA_DESTRUCTIBLE,
	ESTRUCTURA_NO_DESTRUCTIBLE,
	PLAYER,
	TEXTURA_BOMBA,
	TEXTURA_PUERTA
};

class ControladorTexturas{
private:
	static GLuint texturaEstructuraDestructible;
	static GLuint texturaEstructuraNoDestructible;
	static GLuint texturaPlayer;
	static GLuint texturaBomba;
	static GLuint texturaPuerta;
public:
	static void cargarTexturas();
	static GLuint getTextura(tipo_textura tipo);
};

#endif
