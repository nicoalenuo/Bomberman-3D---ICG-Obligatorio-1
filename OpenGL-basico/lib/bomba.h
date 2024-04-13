#pragma once

#ifndef BOMBA_H
#define BOMBA_H

#include "objeto.h"


class personajes;

class bomba : public objeto {
private:
	float tiempoBomba;
	int largoBomba;
	personajes* jugador;
public:
	bomba(int x, int z, float tiempo, int largo);
	float getTiempoBomba();
	void setTiempoBomba(float tiempo);
	int getLargoBomba();
	void setLargoBomba(int largo);
	personajes* getJugador();
	void setJugador(personajes* jug);
	void actualizar();
	void dibujar();
};


#endif

