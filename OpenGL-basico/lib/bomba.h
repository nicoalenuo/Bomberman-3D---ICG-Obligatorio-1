#pragma once
#include "objeto.h"

#ifndef BOMBA_H
#define BOMBA_H
#endif

class personajes;

class bomba : public objeto {
private:
	float tiempoBomba;
	int largoBomba;
	personajes* jugador; //tiene una referencia del mamaguevazo que la puso
public:
	bomba(int x, int z, float tiempo, int largo);
	float getTiempoBomba();
	void setTiempoBomba(float tiempo);
	int getLargoBomba();
	void setLargoBomba(int largo);
	personajes* getJugador();
	void setJugador(personajes* jug);
};

