#pragma once

#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "personaje.h"
#include "bomberman.h"

class enemigo : public personaje {
private:
	//orientacionX == true -> eje x
	//orientacionX == false -> eje z
	bool orientacionX;
	bool moverX;
	bool moverNX;
	bool moverZ;
	bool moverNZ;

	bool eliminar;

	double probCambiarPos;

public:
	enemigo(vector_3 pos, vector_3 tam);

	bool getOrientacionX();
	void setOrientacionX(bool orientacionX);

	bool getEliminar() const { return eliminar; };

	bool intersecta(bomberman* b);

	void actualizar();
	void dibujar();
};


#endif
