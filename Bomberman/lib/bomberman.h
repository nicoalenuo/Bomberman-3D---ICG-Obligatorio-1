#pragma once

#ifndef BOMBERMAN_H
#define BOMBERMAN_H

#include "personaje.h"

class bomberman : public personaje {
private:
	int vida, maxBomba, cantActual, largoBomba, tiempoBomba, rotacion_y_actual, rotacion_z_actual;
	bool moverBomba, balanceandoseDerecha;

	vector<char>  player_commands;
	vector<vector<float>> player_data;
public:
	bomberman(posicion pos, tamanio tam, GLfloat velocidad);

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

	bool bombaDisponible() const { return maxBomba > cantActual; };

	void actualizar();
	void dibujar();
};


#endif

