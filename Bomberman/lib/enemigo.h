#pragma once

#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "personaje.h"
#include "bomberman.h"

#include "particula_enemigo_derrotado.h"

enum color_enemigo {
	ROJO,
	AZUL,
	VERDE
};

class enemigo : public personaje {
private:
	bool orientacionX, moverX, moverNX, moverZ, moverNZ;

	bool eliminar;

	color_enemigo color;

	double probCambiarPos;

	bool balanceandoseDerecha;
	GLfloat rotacion_y_actual, rotacion_z_actual;

public:
	enemigo(vector_3 pos, vector_3 tam, bool orientacionX, color_enemigo color);

	bool getOrientacionX();
	void setOrientacionX(bool orientacionX);

	bool getEliminar() const { return eliminar; };

	bool intersecta(bomberman* b);

	void actualizar();
	void dibujar();

	enemigo::~enemigo();
};

#endif
