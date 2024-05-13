#pragma once

#ifndef CONTROLADORTEXTURAS_H
#define CONTROLADORTEXTURAS_H

#include <map>

#include "SDL_opengl.h"
#include "FreeImage.h"
#include <GL/glu.h>

#include "global.h"
#include "ControladorPoderes.h"

using namespace std;

enum tipo_textura { //agregar aca en caso de agregar mas texturas, y la direccion en el cpp
	ESTRUCTURA_DESTRUCTIBLE,
	ESTRUCTURA_NO_DESTRUCTIBLE,
	PLAYER,
	TEXTURA_BOMBA,
	TEXTURA_PUERTA,
	TEXTURA_AUMENTAR_ALCANCE_BOMBA,
	TEXTURA_AUMENTAR_CANTIDAD_BOMBA,
	TEXTURA_AUMENTAR_VELOCIDAD,
	TEXTURA_BOMBAS_ATRAVIESAN_ESTRUCTURAS,
	TEXTURA_INMORTALIDAD,
	TEXTURA_SUELO,
	TEXTURA_FALLIDA,
	TEXTURA_ENEMY_ROJO,
	TEXTURA_ENEMY_AZUL,
	TEXTURA_ENEMY_VERDE,
	TEXTURA_LOGO,
	TEXTURA_PASTO,
	TEXTURA_CANT_ENEMIGOS,
	TEXTURA_AYUDA,
	TEXTURA_SOMBRA
};

class ControladorTexturas{
private:
	static ControladorTexturas* instancia;
	ControladorTexturas();

	map<tipo_textura, char*> direcciones_texturas;
	map<tipo_textura, GLuint> texturas;
public:
	static ControladorTexturas* getInstance();
	
	GLuint getTextura(tipo_textura tipo) { return texturas[tipo]; };
	tipo_textura getTipoTexturaPoder(tipo_poder tipo);

	~ControladorTexturas();
};

#endif
