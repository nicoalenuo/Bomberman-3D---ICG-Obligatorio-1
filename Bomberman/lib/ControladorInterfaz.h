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
		static ControladorInterfaz* instancia;
		ControladorInterfaz();

		TTF_Font* interfaz;
		hud* hudPuntaje;
		hud* hudTiempo;
		hud* hudGameOver;

		map<tipo_poder, hud*> poderes;

		map<tipo_opcion, hud*> opciones_actuales;
		map<tipo_opcion, hud*> opciones_inicio;
		map<tipo_opcion, hud*> opciones_configuracion;
		tipo_opcion opcion_seleccionada;

		void setMensajeEnComponente(string mensaje, TTF_Font* fuente, hud* componente);
	public:
		static ControladorInterfaz* getInstance();

		void dibujarComponenteHUD(hud* hud);
		void dibujarComponenteHUDPoderes();
		void dibujarMenu();
		void dibujarHUD();
		void setPoderes(map<tipo_poder, int> powerUp);

		void opcion_anterior();
		void opcion_siguiente();
		void seleccionar_opcion();

		~ControladorInterfaz();
};

#endif

