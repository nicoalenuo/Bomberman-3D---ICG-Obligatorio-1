#pragma once

#ifndef CONTROLADORINTERFAZ_H
#define CONTROLADORINTERFAZ_H

#include <string>
#include <iostream>

#include "hud.h"
#include "global.h"
#include "ControladorPoderes.h"
#include "bomberman.h"

using namespace std;

struct hudPoder {
	hud* hud;
	tipo_poder poder;
};

class ControladorInterfaz {
	private:
		static TTF_Font* interfaz;
		static hud* hudPuntaje;
		static hud* hudTiempo;
		static hud* hudGameOver;
		static list<hudPoder> poderes;

		static void setMensajeEnComponente(string mensaje, TTF_Font* fuente, hud* componente);
	public:
		static void cargarInterfaz();
		static void dibujarComponenteHUD(hud* hud);
		static void dibujarComponenteHUDPoderes();
		static void dibujarHUD();
		static hud* getHud(int numero);
		static void setHud(int indice, hud* hud);
		static hud* getHudPoderes(tipo_poder tipo);
		static void setHudPoderes(tipo_poder tipo, hud* hud);
		static void setPoderes(map<tipo_poder, int> powerUp);
		static void liberarInterfaz();
};

#endif

