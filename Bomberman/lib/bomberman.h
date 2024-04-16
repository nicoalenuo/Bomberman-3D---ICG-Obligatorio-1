#pragma once

#ifndef BOMBERMAN_H
#define BOMBERMAN_H

#include "personaje.h"

class bomberman : public personaje {
private:
	int vida;
	int maxBomba;
	bool moverBomba;
	float tiempoBomba;
	int largoBomba;
	GLfloat velocidad;
public:
	bomberman(GLfloat x, GLfloat z);

	int getVida();
	void setVida(int vid);
	int getMaxBomba();
	void setMaxBomba(int max);
	bool getMoverBomba();
	void setMoverBomba(bool mov);
	float getTiempoBomba();
	void setTiempoBomba(float tiempo);
	int getLargoBomba();
	void setLargoBomba(int largo);
	float getVelocidad();
	void setVelocidad(float vel);
	bool bombaDisponible();
	void actualizar();
	void dibujar();
};


#endif

