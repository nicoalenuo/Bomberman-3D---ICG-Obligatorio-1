#pragma once

#ifndef BOMBA_H
#define BOMBA_H

#include "objeto.h"


class personaje;

class bomba : public objeto {
private:
	float tiempoBomba;
	int largoBomba;
	personaje* jugador;
public:
	bomba(GLfloat x, GLfloat z, float tiempo, int largo);
	float getTiempoBomba();
	void setTiempoBomba(float tiempo);
	int getLargoBomba();
	void setLargoBomba(int largo);
	personaje* getJugador();
	void setJugador(personaje* jug);
	void restarTiempo(int tiempo);
	void actualizar();
	void dibujar();
};


#endif

