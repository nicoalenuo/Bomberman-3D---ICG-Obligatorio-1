#pragma once

#include "personajes.h"

class bomba;
class estructura;
class objeto;
class enemigo;
class bomberman;

using namespace std;

class Controlador {
	private:
		static Controlador* instancia;
		bool pausa;
		int nivel;
		int largoTablero = 6;
		int anchoTablero = 6;
		objeto*** tablero = new objeto **[largoTablero];
		list<estructura*> estructuraDestructible = list<estructura*>(); //aqui van las estructuras destructibles
		list<bomba*> bombas = list<bomba*>(); //lista de todas las bombas, ordenadas de tiempo de menor a mayor
		list<enemigo*> enemigos = list<enemigo*>();
		bomberman* jugador; //en principio solo hay un jugador
	public:
		static Controlador* getInstance() {
			if (instancia == nullptr) {
				instancia = new Controlador();
			}
			return instancia;
		}
		Controlador();
		bool getPausa();
		void setPausa(bool pau);
		bool getNivel();
		void setNivel(int niv);
		void pausar(); //pausa o despausa
		void aumentarNivel();
		void crearBomba(int x, int z, personajes* pers);
		void ponerBomba(int x, int z, personajes* pers);
};

