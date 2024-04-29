#pragma once

#ifndef BOMBERMAN_H
#define BOMBERMAN_H

#include "personaje.h"
#include "bonificador.h"

class poder {
	public:
		float cantidad; //pueden ser segundos
		tipo_poder powerUp;
		poder(float cant, tipo_poder power);
		void setCantidad(float cant);
};

class bomberman : public personaje {
private:
	int vida, maxBomba, cantActual, largoBomba, tiempoBomba, rotacion_y_actual, rotacion_z_actual;
	bool moverBomba, balanceandoseDerecha;
	list<poder> poderes = list<poder>();
public:
	bomberman(vector_3 pos, vector_3 tam, GLfloat velocidad);

	int getVida() const { return vida; };
	void setVida(int vid) { vida = vid; };

	int getMaxBomba() const { return maxBomba; };
	void setMaxBomba(int max) { maxBomba = max; };

	int getCantBomba() const { return cantActual; };
	void setCantBomba(int cant) { cantActual = cant; };

	void aumentarCantBomba() { cantActual++; };
	void disminuirCantBomba() { cantActual--; };

	bool getMoverBomba() const { return moverBomba; };
	void setMoverBomba(bool mov) { moverBomba = mov; };

	int getTiempoBomba() const { return tiempoBomba; };
	void setTiempoBomba(int tiempo) { tiempoBomba = tiempo; };

	int getLargoBomba() const { return largoBomba; };
	void setLargoBomba(int largo) { largoBomba = largo; };

	list<poder> getPoderes() const { return poderes; };
	void agregarPoder(poder powerUp);

	bool bombaDisponible() const { return maxBomba > cantActual; };

	void actualizar();
	void dibujar();
};


#endif

