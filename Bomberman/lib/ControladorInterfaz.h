#pragma once

#ifndef CONTROLADORINTERFAZ_H
#define CONTROLADORINTERFAZ_H

#include <string>
#include <iostream>
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_ttf.h"
#include <GL/glu.h>

#include "hud.h"

using namespace std;

class ControladorInterfaz {
	private:
		static TTF_Font* interfaz;
		static hud* puntaje;
		static hud* tiempo;
		static hud* gameOver;

		static void setMensajeEnComponente(string mensaje, TTF_Font* fuente, hud* componente);
	public:
		static void cargarInterfaz(int puntaje, int tiempoJuego, bool fin);
		static void actualizarInterfaz(int puntos, int tiemp, bool finJuego);
		static void dibujarCompomenteHUD(hud* hud);
		static void dibujarHUD();
		static hud* getHud(int numero);
		static void setHud(int indice, hud* hud);
		static void setPuntaje(int puntos);
		static void setTiempo(int tiem);
		static void setFinJuego(bool finJuego);
};

#endif

