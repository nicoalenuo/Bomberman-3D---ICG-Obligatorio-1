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
public:
	bomberman(GLfloat x, GLfloat z, GLfloat anchoX, GLfloat anchoZ, GLfloat alt);

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

	bool posicion_valida(GLfloat coord_x, GLfloat ancho_x, GLfloat coord_z, GLfloat ancho_z, int largoTablero, int anchoTablero, objeto*** tablero);
	void actualizar();
	void dibujar();
};


#endif

