#pragma once

#ifndef CONTROLADORINTERFAZ_H
#define CONTROLADORINTERFAZ_H

#include <string>
#include <iostream>
#include <sstream>

#include "SDL_ttf.h"

#include "global.h"
#include "ControladorPoderes.h"
#include "bomberman.h"

using namespace std;

enum class position {
	top_left,
	top_right,
	top_center,
	left,
	right,
	center,
	bottom_left,
	bottom_right,
	bottom_center
};

enum tipo_opcion {
	COMENZAR_JUEGO,
	CONFIGURACIONES,
	AYUDA,
	CERRAR_JUEGO,
	CAMBIAR_CAMARA,
	TOGGLE_WIREFRAME,
	TOGGLE_TEXTURAS,
	TOGGLE_TIPO_LUZ,
	TOGGLE_LUZ_AMBIENTE,
	TOGGLE_HUD,
	TOGGLE_VELOCIDAD_JUEGO,
	TOGGLE_INMORTAL,
	TOGGLE_PARAR_TIEMPO,
	TOGGLE_ATRAVESAR_PAREDES,
	TOGGLE_AUDIO,
	ATRAS,
};

struct hud {
	position posicion;
	SDL_Surface* mensajeSurface;
	SDL_Surface* colorSurface;
	int width;
	int height;
	GLuint idTextura;
	SDL_Color colorMensaje;
};

class ControladorInterfaz {
	private:
		static TTF_Font* interfaz;
		static hud* hudPuntaje;
		static hud* hudTiempo;
		static hud* hudGameOver;

		static map<tipo_poder, hud*> poderes;

		static map<tipo_opcion, hud*> opciones_actuales;
		static map<tipo_opcion, hud*> opciones_inicio;
		static map<tipo_opcion, hud*> opciones_configuracion;
		static tipo_opcion opcion_seleccionada;

		static void setMensajeEnComponente(string mensaje, TTF_Font* fuente, hud* componente);
	public:
		static void cargarInterfaz();
		static void dibujarComponenteHUD(hud* hud);
		static void dibujarComponenteHUDPoderes();
		static void dibujarMenu();
		static void dibujarHUD();
		static void setPoderes(map<tipo_poder, int> powerUp);
		static void liberarInterfaz();

		static void opcion_anterior();
		static void opcion_siguiente();
		static void seleccionar_opcion();
};

#endif

