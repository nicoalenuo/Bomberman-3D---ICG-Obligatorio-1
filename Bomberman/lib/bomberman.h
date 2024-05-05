#pragma once

#ifndef BOMBERMAN_H
#define BOMBERMAN_H

#include <random>

#include "personaje.h"
#include "bonificador.h"
#include "particula_tierra.h"

class bomberman : public personaje {
private:
	int cantActual;
	bool moverBomba, balanceandoseDerecha;
	GLfloat pasos, rotacion_y_actual, rotacion_z_actual;
public:
	bomberman(vector_3 pos, vector_3 tam, GLfloat velocidad);

	int getCantBomba() const { return cantActual; };
	void setCantBomba(int cant) { cantActual = cant; };

	void aumentarCantBomba() { cantActual++; };
	void disminuirCantBomba() { cantActual--; };

	bool getMoverBomba() const { return moverBomba; };
	void setMoverBomba(bool mov) { moverBomba = mov; };

	bool bombaDisponible() const { return ControladorPoderes::getValor(AUMENTAR_CANTIDAD_BOMBAS) + 1 > cantActual; };

	void actualizar();
	void dibujar();
};


#endif

