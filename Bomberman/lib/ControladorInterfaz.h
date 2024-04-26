#pragma once

#ifndef CONTROLADORINTERFAZ_H
#define CONTROLADORINTERFAZ_H

#include <string>
#include <iostream>
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_ttf.h"
#include <GL/glu.h>

#include "../lib/hud.h"
#include "../lib/global.h"

using namespace std;

class ControladorInterfaz {
	private:
		static TTF_Font* interfaz;
		static hud* hudPuntaje;
		static hud* hudTiempo;
		static hud* hudGameOver;

		static void setMensajeEnComponente(string mensaje, TTF_Font* fuente, hud* componente);
	public:
		static void cargarInterfaz();
		static void actualizarInterfaz();
		static void dibujarCompomenteHUD(hud* hud);
		static void dibujarHUD();
		static hud* getHud(int numero);
		static void setHud(int indice, hud* hud);
		static void setPuntaje(int puntos);
		static void setTiempo(int tiem);
		static void setFinJuego(bool finJuego);
};

#endif

