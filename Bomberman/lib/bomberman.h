#pragma once

#ifndef BOMBERMAN_H
#define BOMBERMAN_H

#include "personaje.h"

class bomberman : public personaje {
private:
	int vida;
	int maxBomba;
	int cantActual;
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
	int getCantBomba();
	void setCantBomba(int cant);
	void aumentarCantBomba();
	void disminuirCantBomba();
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

