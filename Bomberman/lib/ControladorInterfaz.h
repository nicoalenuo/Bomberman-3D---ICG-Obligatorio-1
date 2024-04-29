#pragma once

#ifndef CONTROLADORINTERFAZ_H
#define CONTROLADORINTERFAZ_H

#include <string>
#include <iostream>

#include "hud.h"
#include "global.h"
#include "bonificador.h"
#include "bomberman.h"

using namespace std;

class poder;

class hudPoder {
	public:
		hud* hud;
		tipo_poder poder;
};

class ControladorInterfaz {
	private:
		static TTF_Font* interfaz;
		static hud* hudPuntaje;
		static hud* hudTiempo;
		static hud* hudGameOver;
		static hud* hudCantBombas;
		static list<hudPoder> poderes;

		static void setMensajeEnComponente(string mensaje, TTF_Font* fuente, hud* componente);
	public:
		static void cargarInterfaz();
		static void dibujarComponenteHUD(hud* hud);
		static void dibujarComponenteHUDPoderes();
		static void dibujarHUD();
		static hud* getHud(int numero);
		static void setHud(int indice, hud* hud);
		static hud* getHudPoderes(int indice);
		static void setHudPoderes(int indice, hud* hud);
		static void setPuntaje(int puntos);
		static void setTiempo(int tiem);
		static void setFinJuego(bool finJuego);
		static void setCantBombas(int cant);
		static void setPoderes(list<poder> powerUp);
};

#endif

